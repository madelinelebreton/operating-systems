# <span style="color: lightgreen;">Indexed File System Simulator</span>

## <span style="color: lightgreen;">Overview</span>

This project is a simulation of an **indexed file system implemented in C**.  
It demonstrates how an operating system can manage files using **blocks, indexing, and free space management**.

Each file is stored using:
- <span style="color: lightcoral;">One index block (FIB)</span>
- <span style="color: lightcoral;">Multiple data blocks</span>
- <span style="color: lightcoral;">A free block linked list for allocation and deallocation</span>


## <span style="color: lightgreen;">Specifications</span>

- Fixed-size block storage system  
- Indexed file allocation (1 index block per file points to N data blocks)
- File creation with block allocation
- File deletion with block deallocation
- Root directory listing with formatted output
- Free blocks managed dynamically using a linked list


# <span style="color: lightgreen;">Core Components</span>

![Diagram](file_system_diagram.jpg)


### <span style="color: lightblue;">File Index Block (FIB)</span>

Each file has a FIB that stores:
- Filename
- File size in bytes
- Number of data blocks used
- List of allocated block indices
- Unique FIB ID


### <span style="color: lightblue;">Free Block List</span>

- Implemented as a **singly linked list**
- Tracks all available blocks
- Updated on allocation and deallocation


### <span style="color: lightblue;">File System Structure</span>

- Directory of FIB entries, stored as an array
- Free block head pointer
- File count



## Build Instructions

Compile the project using the provided Makefile:
** make **

## Run Instructions
Run the simulator:
**./fs_sim**
or 
** make run **

## Clean Build Files
** make clean **

# Example Output

# Project Structure
.
├── main.c
├── fs_indexed.c
├── fs_indexed.h
├── Makefile
├── file_system_diagram.jpg
└── README.md

# Author
Madeline LeBreton
