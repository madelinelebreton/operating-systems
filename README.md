# Operating Systems in C

Three systems-programming projects implementing core OS mechanisms from scratch in C: virtual memory management (TLB + paging + page faults), an indexed file system, and low-level address translation with memory-mapped I/O. Originally coursework for McMaster's SFWRENG 3SH3 (Operating Systems), cleaned up here to show the implementations on their own.

No OS-provided abstractions — memory, addresses, and file structures are all modeled and managed by hand.

## Projects

| Project | What it does | Core concepts |
|---|---|---|
| [Virtual Memory Manager](assignments/assignment3-virtual-memory/) | Translates 16-bit logical addresses to physical addresses through a TLB and page table, handling page faults by paging in from a simulated disk backing store | TLB, paging, FIFO page replacement, `mmap()` |
| [Indexed File System](assignments/assignment4-indexed-filesystem/) | Simulates file creation/deletion on a 64-block disk using per-file index blocks and a linked free-block list | Indexed allocation, free-space management, file system data structures |
| [Address Translation & Memory-Mapped I/O](labs/lab3-address-translation/) | Smaller exercises: splitting a logical address into page number + offset with bitmasking, and mapping a binary file directly into memory | Bitwise addressing, `mmap()` |

## Build & run

Each project is a small, self-contained C program — no external dependencies beyond a C compiler. Build instructions are in each project's own README; in short:

```bash
gcc <file>.c -o <name> && ./<name>
```

The indexed file system also has a Makefile (`make && make run`).

## Skills demonstrated

Systems programming in C · memory management · pointer/struct manipulation · file I/O and binary data handling · bitwise operations · Makefiles · debugging with sample I/O validation

## Author

Madeline LeBreton
