// fs_indexed.c
// implements file system functions 

#include <fs_indexed.h>
#include <stdio.h>
#include <stdlib.h>

// inialize file system (mount operation)
void initFS(void){
    // initialize volume control block, metadata
    fs.totalBlocks = MAX_BLOCKS;
    fs.blockSize = BLOCK_SIZE;

    // initialize FIB table (directory)
    fs.fileCount = 0; // empty to start

    // initialize free block list. OS knows which disk blocks availabile, in allcation order
    int index = 0;
    for(int i=0; i<MAX_BLOCKS; i++){
        fs.freeBlocks[index] = i;
        index++;
    }
    fs.freeBlockCount = index; // set counter

    // print success message
    printf("File system mounted successfully\n");
    printf("Total blocks: %d, block size %d", fs.totalBlocks, fs.blockSize);
}

// file operations. mimic system calls
int createFile(char* filename, int size){
    
    // compute required blocks
    int dataBlocks = (size + BLOCK_SIZE-1)/BLOCK_SIZE; // need to add block size to avoid truncating down (ceiling division). for partial blocks
    int totalBlocks = 2 + dataBlocks; // also need 1 for FIB and 1 for index block

    // check file limit
    if(fs.fileCount >= MAX_FILES){ // check that metadata can be stored
        printf("Error: max file limit reached.\n"); 
        return;
    }

    if(totalBlocks > fs.freeBlockCount == 0){ // check that disk has enough space
        printf("Error: not enough free blocks.\n");
        return;
    }

    // allocate FIB first, it's needed to point to the index block (pointer chain FIB > index block > data blocks)
    int fibBlock = allocateFreeBlock();
    if(fibBlock == -1){
        printf("Error allocating FIB block\n");
        return;
    }

    // allocate index block (file map)
    int indexBlock = allocateFreeBlock();
    if(indexBlock == -1){
        printf("Error allocating index block.\n");
        return;
    }
    
    // allocate data blocks
    int dataBlock;

    for(int i=0; i< dataBlocks; i++){ // sequential file layout
        dataBlock = allocateFreeBlock();
        if(dataBlock == -1){
            printf("Error allocating data block\n");
            return;
        }
        // store pointers in index block array. indexBlock[i] = disk block number
        fs.indexBlock[indexBlock][i] = dataBlock;
    }


    // update directory
}

int deleteFile(char* filename);
void listFiles(void);

// free block operations
// remove a block from free block list and return it
int allocateFreeBlock(void){
    // fs.freeBlocks[] is list of available blocks
    // fs.freeBlockCount is number of free blocks

    // check if no free blocks available
    if(fs.freeBlockCount == 0){
        return -1;
    }
    // get a block from end of free block list. constant time allocation without shifting (stack)
    int block = fs.freeBlocks[fs.freeBlockCount-1];
    // update free block count
    fs.freeBlockCount--;
    // return allocated block
    return block;
}

void returnFreeBlock(int block){
    // return to end of free block list (stack implementation)
    fs.freeBlockList[fs.freeBlockCount] = block;
    // increment free block counter
    fs.freeBlockCount++;
}

// utility
void printFreeBlocks(void);

