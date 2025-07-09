#include "fs_utils.h"

char disk[MAX_BLOCKS][BLOCK_SIZE];
bool blockUsed[MAX_BLOCKS];

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


void writeContentToBlocks(const string& content, const vector<int>& blocks){
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


string getCurrentTime(){
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

vector<string> split(const string& s, char delimiter){
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while(getline(ss, token, delimiter)){
        if(!token.empty()){
            tokens.push_back(token);
        }
    }
    return tokens;
}

vector<string> splitPath(const string& path) {
    return split(path, '/');
}

pair<string, string> splitFilePath(const string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == string::npos)
        return {"", path};  // no slash at all

    string dirPath = (pos == 0) ? "/" : path.substr(0, pos);
    string fileName = path.substr(pos + 1);
    return {dirPath, fileName};
}

