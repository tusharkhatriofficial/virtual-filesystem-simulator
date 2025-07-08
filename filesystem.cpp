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
char disk[MAX_BLOCKS][BLOCK_SIZE];
bool blockUsed[MAX_BLOCKS];

struct File{
    string name;
    bool isDirectory;
    int size;
    vector<int> blocks;
    vector<File*> children;
    string createdAt;
};


vector<int> allocateBlocks(int numBlocksNeeded){
    vector<int> allocated;
    //allocating block if it is less than max blocks limit
    for(int i = 0; i<MAX_BLOCKS && allocated.size()<numBlocksNeeded;){
        if(!blockUsed[i]){
            blockUsed[i] = true;
            allocated.push_back(i);
        }
    }

    //if we need 4 blocks but only 3 were allocated i.e (no more free were available) we will set back all blockUsed to false
    if(allocated.size()<numBlocksNeeded){
        for(int i: allocated){
            blockUsed[i] = false;
        }
        //returning empty array because enough blocks were not available to allocate
        return {};
    }
    return allocated;
}

void freeBlocks(vector<int>& blocks){
    for(int blockNum: blocks){
        blockUsed[blockNum] = false;
    }
    blocks.clear();
}


void writeContentToBlocks(string& content, const vector<int>& blocks){
    int contentIndex = 0;
    for (int b: blocks){
        for(int i = 0; i< BLOCK_SIZE && contentIndex < content.size(); i++){
            disk[b][i] = content[contentIndex++];
        }
    }
}

string readContentFromBlocks(vector<int>& blocks, int fileSize){
    string result;
    int readBytes = 0;

    for(int b: blocks){
        for(int i = 0; i<BLOCK_SIZE && readBytes < fileSize; i++){
            result += disk[b][i];
            readBytes++;
        }
    }
    return result;
}