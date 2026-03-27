// fs_indexed.c
// implements indexed file system functions 

#include "fs_indexed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for ceil
#include <string.h> // for strcmp

// global variables
FileSystem fs; // file system global instance


// inialize file system (mount operation)
void initFS(void){

    // initialize FIB table (directory)
    fs.fileCount = 0; // empty to start

    // initialize FIB status list
    for(int i=0; i<MAX_FILES; i++){
        fs.fibStatus[i]=0; // initialize to 0=free
    }

    // create free block list
    fs.freeList = NULL;
    for(int i=MAX_BLOCKS-1; i>=0; i--){
        FreeBlockNode* node = (FreeBlockNode*)malloc(sizeof(FreeBlockNode)); // dynamic memory allocation
        node-> nodeNum = i; // set block number 
        node-> next = fs.freeList; // point to current head of free list
        fs.freeList = node; // update head of free list to new node

    }

    // print success message
    printf("File system mounted successfully\n");
    printf("Total blocks: %d, block size %d bytes\n", MAX_BLOCKS, BLOCK_SIZE);
}

// file operations. mimic system calls
int createFile(char* filename, int size){
    // compute number of blocks needed
    int blocksNeeded = (int)ceil((double)size / BLOCK_SIZE);

    // check limits
    if(fs.fileCount >= MAX_FILES) {
        printf("Error: max files reached");
        return -1;
    }
    if(blocksNeeded > MAX_BLOCKS_PER_FILE){
        printf("Error: file too large");
        return -1;
    }

    // allocate FIB spot by finding a free entry
    int fibID = -1;
    for(int i=0; i< MAX_FILES; i++){
        if(fs.fibStatus[i] == 0){ // free block found
            fibID = i; // allocate this block
            fs.fibStatus[i] = 1; // flag this block as used
            break;
        }
    }

    if(fibID == -1) return -1; // no free entries found

    // allocate index block
    int indexBlock = allocateFreeBlock();
    if(indexBlock == -1) return -1;

    // allocate data blocks, storing in a temporary array first
    int dataBlocks[MAX_BLOCKS_PER_FILE];
    for(int i=0; i<blocksNeeded; i++){
        int b = allocateFreeBlock();
        if(b==-1) return -1; // error 
        dataBlocks[i] = b;
    }

    for(int i=0; i< blocksNeeded; i++){
        fs.blocks[indexBlock].data[i] = dataBlocks[i];
    }

    // write index block
    FIB* f = &fs.directory[fibID]; // points to address of FIB

    // update directory
    strcpy(f->filename, filename); // copy filename into FIB
    f->fileSize = size;
    f->fibID = fibID;
    f->indexBlock = indexBlock;
    f->numBlocks = blocksNeeded;

    fs.fileCount++; // increment counter

    printf("File %s created (FIBID=%d)\n", filename, fibID);

    return 0; // success
}

int deleteFile(char* filename){
    // locate file FIB
    int fibID = -1;
    for(int i=0; i<MAX_FILES; i++){
        if(fs.fibStatus[i] == 1 && strcmp(fs.directory[i].filename, filename) == 0){
            fibID = i;
            break;
        }
    }
    // error message if file not found
    if(fibID == -1){
        printf("Error: file note found\n");
        return -1;
    }

    // get the file pointer
    FIB* f = &fs.directory[fibID];

    int indexBlock = f->indexBlock;

    // get data stored in index block
    unsigned char* data = fs.blocks[indexBlock].data;

    // return all blocks used by the file, including index block, to the free block list
    for(int i=0; i<f->numBlocks; i++){
        int blockNum = data[i]; // block numbers are stored in the index block's data
        returnFreeBlock(blockNum);
    }
    returnFreeBlock(indexBlock); // return index block

    // return FIB ID to file system, and update available FIBs
    fs.fibStatus[fibID] = 0; // mark FIB as free

    fs.fileCount--; // decrement counter because we deleted a file

    // print success message
    printf("File '%s' deleted", filename);

    return 0; // success

}

void listFiles(void){
    printf("\nRoot directory listing (%d files)\n", fs.fileCount);
    for(int i=0; i<MAX_FILES; i++){
        if(fs.fibStatus[i] == 1){ // if there is FIB entry
            FIB* f = &fs.directory[i]; // f points to directory address
            printf(" %s  |  %d bytes  |  %d data blocks |  FIBID=%d\n", f-> filename, f->fileSize, f->numBlocks, f->fibID);
        }
    }
}

// free block operations
// remove a block from free block list and return it
int allocateFreeBlock(void){
    // check if no free blocks available
    if(fs.freeList == NULL){
        return -1; // no space in disk
    }

    FreeBlockNode* temp = fs.freeList; // store head of free block list
    int blockNum = temp->nodeNum; // get block number to allocate
    fs.freeList = fs.freeList->next; // update head of free block list to next node
    free(temp); // free memory of allocated node

    return blockNum; // return allocated block number
}

void returnFreeBlock(int block){
    FreeBlockNode* node = (FreeBlockNode*)malloc(sizeof(FreeBlockNode));
    node->nodeNum = block; // assign block to this node's number
    node->next = NULL; // next pointer is null because it's at the end

    // if the list is empty, place this node at the head
    if(fs.freeList == NULL){
        fs.freeList = node;
        return;
    }
    // otherwise, traverse list until the end is reached
    FreeBlockNode* temp = fs.freeList; // point to the head
    while(temp->next != NULL){
        temp = temp-> next; // move to next node
    }

    // add block to end of free block list
    temp->next = node;
}

// utility
void printFreeBlocks(void){
    // traverse and count
    int count = 0;
    FreeBlockNode* temp = fs.freeList;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    printf("\nFree blocks (%d): ", count); // print header
    // traverse again and print values
    temp = fs.freeList;
    while(temp != NULL){
        printf("[%d] -> ", temp->nodeNum);
        temp = temp->next;
    }
    printf("NULL\n"); // reached end of free list
}

