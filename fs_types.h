#ifndef FS_TYPES_H
#define FS_TYPES_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

//creating constants 
#define BLOCK_SIZE 512
#define MAX_BLOCKS 1024

//gobal vars
extern char disk[MAX_BLOCKS][BLOCK_SIZE];
extern bool blockUsed[MAX_BLOCKS];

struct File{
    string name;
    bool isDirectory;
    int size;
    vector<int> blocks;
    vector<File*> children;
    File* parent;             
    string createdAt;
};

#endif