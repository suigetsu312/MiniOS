#ifndef CONSOLE_H
#define CONSOLE_H

#include "platform/sbi.h"

void putchar(char ch);
long getchar(void);
void kprintf(const char *fmt, ...);

#endif /* CONSOLE_H */
