#ifndef FS_UTILS_H
#define FS_UTILS_H

#include "fs_types.h"

vector<int> allocateBlocks(int numBlocksNeeded);
void freeBlocks(vector<int>& blocks);
void writeContentToBlocks(const string& content, const vector<int>& blocks);
string readContentFromBlocks(vector<int>& blocks, int fileSize);

string getCurrentTime();
vector<string> split(const string& s, char delimiter);
vector<string> splitPath(const string& path);
pair<string, string> splitFilePath(const string& path);

#endif