#ifndef PROCESS_H
#define PROCESS_H

#include "lib/types.h"

#define MAX_PROCESSES 8

#define PROCESS_UNUSED 0
#define PROCESS_RUNNING 1

struct task {
    int pid;
    int state;
    vaddr_t sp;
    uint8_t stack[8192];
};

extern struct task processes[MAX_PROCESSES];

__attribute__((naked)) void switch_context(uint32_t *prev_sp,
                                           uint32_t *next_sp);

struct task *create_process(uint32_t pc);

#endif /* PROCESS_H */
