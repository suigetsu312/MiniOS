#ifndef KERNEL_H
#define KERNEL_H
#include "lib/console.h"
#include "lib/string.h"
#include "lib/types.h"
#include "mm/page.h"
#define PANIC(fmt, ...)                                                        \
    do {                                                                       \
        kprintf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);  \
        while (1) {}                                                           \
    } while (0)

struct trap_frame {
    uint32_t ra;   // x1  return address
    uint32_t gp;   // x3  global pointer
    uint32_t tp;   // x4  thread pointer

    uint32_t t0;   // x5  temporary register, caller-saved
    uint32_t t1;   // x6  temporary register, caller-saved
    uint32_t t2;   // x7  temporary register, caller-saved
    uint32_t t3;   // x28 temporary register, caller-saved
    uint32_t t4;   // x29 temporary register, caller-saved
    uint32_t t5;   // x30 temporary register, caller-saved
    uint32_t t6;   // x31 temporary register, caller-saved

    uint32_t a0;   // x10 argument 0 / return value 0
    uint32_t a1;   // x11 argument 1 / return value 1
    uint32_t a2;   // x12 argument 2
    uint32_t a3;   // x13 argument 3
    uint32_t a4;   // x14 argument 4
    uint32_t a5;   // x15 argument 5
    uint32_t a6;   // x16 argument 6
    uint32_t a7;   // x17 argument 7 / syscall number

    uint32_t s0;   // x8  saved register / frame pointer, callee-saved
    uint32_t s1;   // x9  saved register, callee-saved
    uint32_t s2;   // x18 saved register, callee-saved
    uint32_t s3;   // x19 saved register, callee-saved
    uint32_t s4;   // x20 saved register, callee-saved
    uint32_t s5;   // x21 saved register, callee-saved
    uint32_t s6;   // x22 saved register, callee-saved
    uint32_t s7;   // x23 saved register, callee-saved
    uint32_t s8;   // x24 saved register, callee-saved
    uint32_t s9;   // x25 saved register, callee-saved
    uint32_t s10;  // x26 saved register, callee-saved
    uint32_t s11;  // x27 saved register, callee-saved

    uint32_t sp;   // x2  stack pointer before trap

    uint32_t pad;  // padding, keeps sizeof(trap_frame) == 128 bytes
} __attribute__((packed));

#define READ_CSR(reg)                                                          \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp));                  \
        __tmp;                                                                 \
    })

#define WRITE_CSR(reg, value)                                                  \
    do {                                                                       \
        uint32_t __tmp = (value);                                              \
        __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp));                \
    } while (0)


__attribute__((naked)) void user_entry(void);
void handle_syscall(struct trap_frame *f);
#endif /* KERNEL_H */