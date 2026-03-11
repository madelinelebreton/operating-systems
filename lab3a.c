/**
 * lab3a.c
 * Address translation and memory mapping
 * a) Read from a file
 * Author: Madeline LeBreton
 * Date: 3.10.2026
 * SFWRENG 3SH3
 */


// compilation command
// gcc lab3a.c -o lab3a

// execution
// ./lab3a


// header files
#include <stdio.h>
#include <stdlib.h>

// define constants
#define BUFFER_SIZE 10
#define PAGE_SIZE 1<<12 // 4Kb
#define OFFSET_BITS 12 // 12 bits needed to store 1 page/frame
#define MASK (1<<12)-1 // want mask to be 0000...000111111111111 to isolate the offset value
#define NUM_PAGES 8

// global variables
int page_table[NUM_PAGES] = {6, 4, 3, 7, 0, 1, 2, 5};
char buf[BUFFER_SIZE]; // buffer to store read values

int main(){
  FILE *fptr = fopen("labaddr.txt", "r"); // open the text file with read permissions
  if(fptr == NULL){
    printf("Error opening file.\n");
    return 1;
  }

  while(fgets(buf, BUFFER_SIZE, fptr) != NULL){
    int va = atoi(buf); // virtual address
    // for each VA in the text file, convert to PA and print the result
    int page_num = va >> OFFSET_BITS;
    int offset = va & MASK;
    int frame_num = page_table[page_num];
    int pa = (frame_num << OFFSET_BITS) | offset; // bitwise OR operator to combine the frame number and offset
    printf("Virtual addr is %d: Page# = %d & Offset = %d. Physical addr: %d\n", va, page_num, offset, pa);
  }
  


    
  
  fclose(fptr); // close file pointer
  
  return 0;
}


  



