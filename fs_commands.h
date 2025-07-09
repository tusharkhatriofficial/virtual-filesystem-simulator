#ifndef FS_COMMANDS_H
#define FS_COMMANDS_H

#include "fs_types.h"

File* traversePath(File* root, const string& path);
void mkdir(File* root, const string& path);
void writeFile(File* root, const string& path, const string& content);
void ls(File* root, const string& path);
void readFile(File* root, const string& path);

File* resolvePathToAny(File* root, const string& path);
void statFile(File* root, const string& path);

#endif
