#include "kernel/scheduler.h"
#include "mm/page.h"
struct task *current_process;
struct task *idle_process;

void schedule()
{
    // find the next runnable process
    struct task *next = idle_process; 
    for (int i = 0; i < MAX_PROCESSES; i++) {
        struct task *proc = &processes[(current_process->pid + i + 1) % MAX_PROCESSES];
        if (proc->state == PROCESS_RUNNING && proc->pid > 0) {
            next = proc;
            break;
        }
    }

    // if there is no other runnable process, we will just switch to the idle process
    if(next == current_process)
        return;

    /*
     * Update sscratch to the next task's kernel stack top. The trap entry code
     * uses sscratch to switch to the correct kernel stack on trap entry.
     */
    __asm__ __volatile__( 
        "sfence.vma\n"
        "csrw satp, %[satp]\n"
        "sfence.vma\n"
        "csrw sscratch, %[sscratch]\n"
        :
        : [satp] "r" (SATP_SV32 | ((uint32_t) next->page_table / PAGE_SIZE)),
          [sscratch] "r" ((uint32_t) &next->stack[sizeof(next->stack)])
    );

    // switch to the next process
    struct task *prev = current_process;
    current_process = next;
    switch_context(&prev->sp, &current_process->sp);
}
