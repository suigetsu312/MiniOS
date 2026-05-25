#ifndef PROCESS_TEST_H
#define PROCESS_TEST_H

#include "kernel/process.h"

extern struct task *proc_a;
extern struct task *proc_b;

void delay(void);
void proc_a_entry(void);
void proc_b_entry(void);

#endif /* PROCESS_TEST_H */
