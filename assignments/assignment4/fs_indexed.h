// fs_indexed.h
// file system simulator header file
// contains struct definitions, constants, and function prototypes


// index block, integer array of all data block numbers. the file uses multiple data blocks
int indexBlock[MAX_BLOCKS_PER_FILE];


// File Information Block stores file attributes, permissions, and location of file
typedef struct {
  char filename[50];
  int fileSize; 
  
  int fibID; // file identifier
  int indexBlock; // single pointer to block holding index list
  int numBlocks; // number of data blocks used
} FIB;

// GLOBAL file system, kernel memory structure for OS mapping
typedef struct {
  FIB directory[MAX_FILES]; // in-memory directory structure storing all FIBs (flat, single-level)
  int fileCount; // number of directory entries in use
  
  int freeBlocks; // free block list
  int freeBlockCount; 
  
  int totalBlocks; 
  int blockSize;
} FileSystem;


  
