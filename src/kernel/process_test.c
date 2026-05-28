#include "kernel/process.h"
#include "kernel/process_test.h"
#include "lib/console.h"
#include "lib/types.h"
#include "kernel/scheduler.h"

extern char __bss[], __bss_end[], __stack_top[];

void delay(void) {
    for (int i = 0; i < 30000000; i++)
        __asm__ __volatile__("nop"); // do nothing
}

struct task *proc_a;
struct task *proc_b;

void proc_a_entry(void) {
    kprintf("starting process A\n");
    while (1) {
        // putchar('A');
        schedule();
    }
}

void proc_b_entry(void) {
    kprintf("starting process B\n");
    while (1) {
        // putchar('B');
        schedule();
    }
}
