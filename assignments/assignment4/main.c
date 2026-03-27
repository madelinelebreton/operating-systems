// main.c
// tests implementation of indexed file system

#include "fs_indexed.h"

int main(void){
    // initialize file system
    initFS();

    // create files to match desired sample output
    createFile('alpha.txt', 3072); // this should require 3 blocks
    createFile('beta.txt', 5120); // this should require 5 blocks

    // list files and free blocks
    listFiles();
    printFreeBlocks();

    // delete alpha
    deleteFile('alpha.txt');
    listFiles();
    printFreeBlocks();

    // create more files
    createFile('gamma.txt', 4096); // this should require 4 blocks
    createFile('delta.txt', 8192); // this should require 8 blocks

    listFiles();
    printFreeBlocks();

    // delete all
    deleteFile('beta.txt');
    deleteFile('gamma.txt');
    deleteFile('delta.txt');

    listFiles();
    printFreeBlocks();

}




