# Virtual Memory Manager

A simulation of a virtual memory management unit: translating 16-bit logical addresses into physical addresses through a TLB and page table, and resolving page faults by paging in from a simulated disk.

## How it works

- Logical addresses are split into an 8-bit page number and an 8-bit offset.
- Each lookup checks the **TLB** first (16 entries, FIFO replacement).
- On a TLB miss, it falls back to the **page table** (256 entries).
- On a page fault (page not yet in memory), the manager `mmap()`s the backing store file and copies the needed page into one of 128 physical frames, evicting the oldest frame (FIFO) if memory is full.
- The TLB is updated after every resolved address so future lookups can hit.

## Build & run

```bash
gcc assignment3.c -o vm_sim
./vm_sim
```

Reads logical addresses from `addresses.txt` and pages from `BACKING_STORE.bin` (both included, both required for the program to run).

## Sample output

```
Virtual address: 16916 Physical address = 20 Value=0
Virtual address: 62493 Physical address = 285 Value=0
Virtual address: 30198 Physical address = 758 Value=29
...
Total addresses = 1000
Page_faults = 538
TLB hits = 54
```

## Files

- `assignment3.c` — the simulation (TLB, page table, page fault handler)
- `addresses.txt` — input: logical addresses to translate
- `BACKING_STORE.bin` — simulated disk backing store the pages are read from
