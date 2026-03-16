// assignment3/assignment3.c
// Simulates memory management unit, with TLB and page fault handler
// Author: Madeline LeBreton
// Date: 12.03.2026

// header files
#include <stdio.h>
#include <stdlib.h>
// parameters
#define PAGE_SIZE 256 // page size 256 bytes
#define NUM_PT_ENTRIES (1<<8) // one entry per page, with 16 bit VA - 8 bits for offset = 8 bits to rep. pages
#define FRAME_COUNT (1<<7) // 15 bit PA, with 8 bit offset leaves 7 bits for frames

// global variables
int pt[NUM_PT_ENTRIES]; // page table

// main
int main(){
    FILE *address_file; // pointer to addresses.txt
    int la; // logical address, will be a 16 bit binary number

    address_file = fopen("/Users/madelinelebreton/Documents/github/operating-systems/assignments/assignment3/addresses.txt", "r"); // open the text file with read permissions

    if(address_file == NULL){ // file open failure returns NULL
        printf("Error opening address.txt\n");
        return 1; // error flag
    }

    while(fscanf(address_file, "%d", &la) != EOF){ // EOF end of file macro from <stdio.h>
        int page_num = la >> 8 & 0xFF; // shift right to capture 8 MSB, then mask with binary 11111111 to only keep those bits
        int offset = la & 0xFF; // mask MSB to capture 8 LSB

        printf("Logical address: %d   page number: %d   offset %d\n", la, page_num, offset); // print results
    }
    fclose(address_file); // close the text file

    return 0;
}