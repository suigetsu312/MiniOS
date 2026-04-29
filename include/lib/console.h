#ifndef CONSOLE_H
#define CONSOLE_H

#include "platform/sbi.h"

void putchar(char ch);
void printf(const char *fmt, ...);

#endif /* CONSOLE_H */
