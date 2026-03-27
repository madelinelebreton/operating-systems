// fs_indexed.h
// file system simulator header file
// contains struct definitions, constants, and function prototypes

// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // needed for ceil() with division


// system constants
#define MAX_FILES 10
#define MAX_BLOCKS 64
#define MAX_BLOCKS_PER_FILE 8
#define BLOCK_SIZE 2^10


// global file system instance. simulates single kernel instance
extern FileSystem fs;

// index block, integer array of all data blocks allocated to the file
int indexBlock[MAX_BLOCKS_PER_FILE];


// Block represents a fixed-size portion of the disk
typedef struct Block{
    unsigned char data[BLOCK_SIZE];
    int blockNumber;
} Block;

// node of free block linked list 
typedef struct FreeBlockNode{
    int node;
    struct FreeBlockNode* next;
} FreeBlockNode;

// File Information Block stores file attributes, permissions, and location of file. one per file
typedef struct FIB{
  char filename[50];
  int fileSize; 
  
  int fibID; // file identifier
  int indexBlock; // single pointer to block holding index list
  int numBlocks; // number of data blocks used
} FIB;



// GLOBAL file system, kernel memory structure for OS mapping
typedef struct FileSystem{
    Block blocks[MAX_BLOCKS]; // array of all blocks on disk
    FIB directory[MAX_FILES]; // in-memory directory structure storing all FIBs (flat, single-level)
    FreeBlockNode* freeList; // linked list of all free blocks for efficient insert/remove
    int fileCount; // number of directory entries in use
} FileSystem;


// FUNCTION PROTOTYPES
// inialize file system (mount operation)
void initFS(void);

// file operations. mimic system calls
int createFile(char* filename, int size); // returns success/failure indicator
int deleteFile(char* filename);
void listFiles(void);

// free block operations
int allocateFreeBlock(void);
void returnFreeBlock(int block);

// utility
void printFreeBlocks(void);