#include "fs_shell.h"
#include "fs_types.h"
#include "fs_utils.h"

int main(){
    File* root = new File();
    root->name = "/";
    root->size = 0;
    root->parent = nullptr;
    root->createdAt = getCurrentTime();

    shell(root);
    return 0;
}