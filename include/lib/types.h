#ifndef TYPES_H
#define TYPES_H
// The base virtual address of an application image. This needs to match the
// starting address defined in `user.ld`.
#define USER_BASE 0x1000000

typedef int bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint32_t size_t;
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

typedef unsigned int uintptr_t;

extern char _binary_build_apps_shell_bin_start[];
extern char _binary_build_apps_shell_bin_size[];
#define SSTATUS_SPIE (1 << 5)

#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg

#define true  1
#define false 0
#define NULL  ((void *) 0)
#define align_up(value, align)   __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)
#define offsetof(type, member)   __builtin_offsetof(type, member)

#define SCAUSE_ECALL 8

#define SYS_PUTCHAR 1
#define SYS_GETCHAR 2
#define SYS_EXIT    3

#define PROC_EXITED   2

#endif /* TYPES_H */