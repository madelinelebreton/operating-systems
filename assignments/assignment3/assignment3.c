// assignment3/assignment3.c
// Simulates memory management unit, with TLB and page fault handler
// Author: Madeline LeBreton
// Date: 12.03.2026

// header files
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open(), to get file descriptor for mmap()
#include <sys/mman.h> // for mmap() memory mapping and munmap()
#include <unistd.h> // for open() and close()
#include <string.h> // for memcpy(), copying page data

// parameters
#define PAGE_SIZE 256 // page size 256 bytes
#define NUM_PT_ENTRIES (1<<8) // one entry per page, with 16 bit VA - 8 bits for offset = 8 bits to rep. pages
#define FRAME_COUNT (1<<7) // 15 bit PA, with 8 bit offset leaves 7 bits for frames
#define TLB_SIZE (1<<4); // transfer lookaside buffer

// tlb structure, simulates cache for page table
typedef struct {
    int page;
    int frame;
} TLB_Struct;

// global structures
TLB_Struct tlb[TLB_SIZE]; // transfer lookaside buffer
int tlb_index = 0;

int pt[NUM_PT_ENTRIES]; // page table, -1 means not in memory
int frame_table[FRAME_COUNT]; // track which page is in which frame

signed char physical_memory[FRAME_COUNT][PAGE_SIZE]; // need enough memory for 256 byte page x 2^8 pages. each index rep. 1 byte
int fifo_ptr = 0; 
int tlb_hits = 0; 
int page_faults = 0; // counters for validation
int num_addresses = 0;



// tlb functions
int search_tlb(int page){ // search tlb for referenced page number
  for(int i=0; i<TLB_SIZE; i++){
    if(tlb[i].page == page)
      return tlb[i].frame; // return corresponding frame number
  } return -1; // if the page isn't found, return -1
}

// add to tlb using first in, first out replacement policy
void add_TLB(int page, int frame){
  tlb[tlb_index].page = page;
  tlb[tlb_index].frame = frame;
  
  // increment index for next time, in circular fashion
  tlb_index = (tlb_index + 1) % TLB_SIZE;
}

// update tlb when page is replaced
void update_tlb(int page, int frame){
  for(int i=0; i<TLB_SIZE; i++){
    if(tlb[i].page == page){
      tlb[i].frame = frame;
    }
  }
}
      


// main
int main(){
    
    // initialize page table
    for(int i=0; i<NUM_PT_ENTRIES; i++){
        pt[i] = -1; // initialize to -1 for "invalid", page not yet in memory
    }
    
    // initialize tlb
    for(int i=0; i<TLB_SIZE; i++){
      frame_table[i] = -1; // initialize values to -1
    }

    // open backing store. mmap() only works with a file descriptor so we use open() with O_RDONLY
    int backing_fd = open("BACKING_STORE.bin", O_RDONLY); // get file descriptor
    if(backing_fd == -1){
        perror("Error opening BACKING_STORE.bin");
        return 1; // error flag
    }

    // memory map the backing store
    signed char *backing_store = mmap(NULL, NUM_PT_ENTRIES * PAGE_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0);
    if(backing_store == MAP_FAILED){
        perror("Error mapping backing store");
        return 1;
    }
    
    // read addresses from file
    FILE *address_file; // pointer to addresses.txt
    address_file = fopen("addresses.txt", "r"); // open the text file with read permissions
    if(address_file == NULL){ // file open failure returns NULL
        printf("Error opening address.txt\n");
        return 1; // error flag
    }
    
    int la; // logical address, will be a 16 bit binary number
    
    // MAIN LOOP
    // extract page number and offset from addresses
    while(fscanf(address_file, "%d", &la) != EOF){ // EOF end of file macro from <stdio.h>
        int page_num = la >> 8; // shift right to capture 8 MSB, then mask with binary 11111111 to only keep those bits
        int offset = la & 0xFF; // mask MSB to capture 8 LSB

        // handling a logical address: lookup in tlb, if miss then page table, if page not in memory handle page fault
        int frame_number = search_TLB(page);

        if(frame_number == !-1){ // valid, tlb HIT!
            tlb_hits++;
        }
        else{
          // page table lookup
          frame = pt[page];
          
          // page fault if invalid
          if(frame == -1){
            int victim_frame = fifo_ptr;
            fifo_ptr
            ************** start coding here
          
          
            // copy page from backing store to physical memory
            frame_number = next_free_frame; // the faulted page will reside in the next available frame
            next_free_frame = (next_free_frame +1) % FRAME_COUNT; // increment so the oldest frame is always replaced

            // copy the 256 byte page from backing store to physical memory
            memcpy(&physical_memory[frame_number * PAGE_SIZE], &backing_store[page_num * PAGE_SIZE], PAGE_SIZE);

            pt[page_num] = frame_number; // record where the faulted page now lives 
        }

        // compute physical address and retrieve value
        int pa = frame_number*PAGE_SIZE + offset;
        signed char value = physical_memory[pa]; // values can be negative, so represent as -128 to 127

        printf("Virtual address: %d  Physical address: %d  Value: %d    num %d \n", la, pa, value, num_addresses); // uses integer promotion to print value
        num_addresses ++;
    }

    fclose(address_file); // close the text file
    close(backing_fd); // close the backing file
    munmap(backing_store, NUM_PT_ENTRIES*PAGE_SIZE); 

    printf("Total addresses = %d\n", num_addresses);
    printf("Page_faults = %d\n", page_faults);
    printf("TLB hits = %d\n", tlb_hits);

    return 0;
}
