// lab3/lab3b.c
// Memory mapping files in C
// Maps binary file numbers.bin to memory region using mmap()
// Author: Madeline LeBreton
// Date: 11.03.2026

// compilation command
// gcc lab3b.c -o lab3b

// execution
// ./lab3b

// header files
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h> // for mmap() function
#include <string.h> // for memcpu() function
#include <fcntl.h> // for file descriptors
#include <stdlib.h> // for file descriptors

// macros
#define INT_COUNT 10 // number of integers in numbers.bin
#define INT_SIZE 4 // size of integer in bytes

// global variables
int memory_size = INT_SIZE * INT_COUNT; // total size for memory mapping
int intArray[INT_COUNT]; // integer array to store values read from memory region
signed char *mmapfptr; // signed character pointer to store starting address of memory mapped file

int main(){
  
  int mmapfile_fd = open("numbers.bin", O_RDONLY); // open numbers.bin file
  mmapfptr = mmap(0, memory_size, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0); // use system call to memory map the file
  
  for(int i=0; i<INT_COUNT; i++){ // loop through each number in numbers.bin
    memcpy(intArray + i, mmapfptr + 4*i, INT_SIZE); // retrieve contents of mapped file using loop and store in integer array
  }
  
  munmap(mmapfptr, memory_size); // unmap the memory mapped file using syst call
  
  int sum = 0; // stores sum of numbers
  for(int i=0; i<INT_COUNT; i++){
    sum += intArray[i];
    printf("Sum for loop %d: %d\n", i, sum);
  }
  
  printf("\n\nTOTAL SUM OF NUMBERS: %d\n\n", sum);
  
  return 0;
}
