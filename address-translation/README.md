# Address Translation & Memory-Mapped I/O

Two small exercises on how a CPU talks to memory: splitting a logical address into a page number and offset by hand, and mapping a file directly into memory instead of reading it byte by byte.

## Files

- **`lab3a.c`** — takes a 16-bit logical address, extracts the page number (upper bits) and offset (lower 12 bits via bitmask), and looks up the physical frame in a page table. Reads addresses from `labaddr.txt`.
- **`lab3b.c`** — uses `mmap()` to map `numbers.bin` directly into memory, then reads and sums integers straight out of the mapped region rather than using `fread()`.

## Build & run

```bash
gcc lab3a.c -o lab3a && ./lab3a
gcc lab3b.c -o lab3b && ./lab3b
```

## Sample output

```
# lab3a
Virtual addr is 19986: Page# = 4 & Offset = 3602. Physical addr: 3602
Virtual addr is 16916: Page# = 4 & Offset = 532. Physical addr: 532
...

# lab3b
Sum for loop 0: 16
Sum for loop 1: 30
...
```
