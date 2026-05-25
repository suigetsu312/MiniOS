#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "kernel/process.h"

// Global scheduler state is defined in scheduler.c and declared here.
extern struct task *current_process;
extern struct task *idle_process;

// since we aren't ready to implement a scheduler, we'll simply implement a function to switch the process A and process B, and we'll call this function in the timer interrupt handler to switch between two processes
void schedule();

#endif
