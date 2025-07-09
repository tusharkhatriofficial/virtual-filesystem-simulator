#ifndef FS_SHELL_H
#define FS_SHELL_H

#include "fs_types.h"

void processCommand(File* root, const string& input);
void shell(File* root);

#endif