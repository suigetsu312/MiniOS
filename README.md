# MiniOS

This project aims to learn low-level OS mechanisms through the book [*Operating System in 1,000 Lines*](https://operating-system-in-1000-lines.vercel.app/en/).

The goal is to build a simple OS for the 32-bit RISC-V platform.

## Roadmap

- [x] Boot a minimal kernel on QEMU
- [x] Set up basic console input/output through SBI
- [x] Understand the linker script and kernel memory layout
- [x] Set up basic trap entry and register save/restore
- [x] Implement simple single-core process creation and cooperative context switching
- [x] Add a minimal physical page allocator
- [x] Build page tables and switch address spaces with `satp`
- [x] Load and run a user application in user mode
- [x] Add basic syscalls: `putchar`, `getchar`, and `exit`
- [x] Add basic virtio block device I/O
- [ ] Add a richer shell or more user applications
- [ ] Build a filesystem layer on top of block I/O
