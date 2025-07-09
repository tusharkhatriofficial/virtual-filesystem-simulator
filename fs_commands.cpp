#include "fs_utils.h"
#include "fs_commands.h"

void mkdir(File* root, const string& path){
    vector<string> folders = splitPath(path);
    File* current = root;
    bool createdSomething = false;

    for(const string& folder: folders){
        bool found = false;

        //checking if folder exists
        for(File* child : current-> children){
            if(child->isDirectory && child->name == folder){
                current = child;
                found = true;
                break;
            }
        }

        //creating folder if it does not exixt
        if(!found){
            File* newFolder = new File();
            newFolder->name = folder;
            newFolder->size = 0;
            newFolder->parent = current;
            newFolder->isDirectory = true;
            newFolder->createdAt = getCurrentTime();
            current->children.push_back(newFolder);
            current = newFolder;
            createdSomething = true;
        }
        
    }

    if(createdSomething){
        cout<<"Directory created at: "<<path<<endl;
    }else{
        cout<<"Directory already exists: "<<path<<endl;
    }
}

File* traversePath(File* root, const string& path){
    if(path=="/") return root;

    vector<string> folders = splitPath(path);
    File* current = root;

    for(const string& folder : folders){
        bool found = false;
        for(File* child: current->children){
         if(child->name == folder && child->isDirectory){
            current = child;
            found = true;
            break;
         }
       }
       if(!found) return nullptr; 
    }
    return current;
}

void ls(File* root, const string& path){
    File* target = traversePath(root, path);
    
    if(target == nullptr){
        cout<<"Error: Directory not found -> "<<path<<endl;
        return;
    }

    if(!target->isDirectory){
        cout<<"Error: path is not a directory -> "<<path<<endl;
        return;
    }

    if(target->children.empty()){
        cout<<"(empty)"<<endl;
        return;
    }

    for(File* child: target->children){
        if(child->isDirectory){
            cout<<"[DIR] "<< child->name<<endl;
        }else{
            cout<<"[FILE] "<<child->name<<endl;
        }
    }

}



void writeFile(File* root, const string& path, const string& content){
    auto [dirPath, fileName] = splitFilePath(path);
    File* dir = traversePath(root, dirPath);

    if(!dir || !dir->isDirectory){
        cout<<"Error: parent directory doesn't exist -> " <<dirPath <<endl;
        return;
    }

    //checking if the file already exixts to prevent over writing
    for(File* child : dir -> children){
        if(!child->isDirectory && child->name == fileName){
            cout<<"Erro: file already exists: "<< fileName<<endl;
            return;
        }
    }

    int size = content.size();
    int blocksNeeded = (size + BLOCK_SIZE -1) / BLOCK_SIZE;

    vector<int> blocks = allocateBlocks(blocksNeeded);

    if(blocks.empty()){
        cout<<"Error: not enough space on the disk."<<endl;
        return;
    }

    writeContentToBlocks(content, blocks);

    File* newFile = new File();
    newFile->name = fileName;
    newFile->isDirectory = false;
    newFile->size = size;
    newFile->blocks = blocks;
    newFile->parent = dir;

    dir->children.push_back(newFile);
    cout<<"File " <<fileName<<" created with "<<blocks.size()<<" blocks."<<endl;


}



void readFile(File* root, const string& path){

    //getting the file with path
    auto [dirPath, fileName] = splitFilePath(path);
    File* dir = traversePath(root, dirPath); 

    //if no such directory exists show error
    if(!dir || !dir->isDirectory){
        cout<<"Error: no such directory exists"<<dirPath<<endl;
        return;
    }
    

    //find the file in the existing directory
    //loop through the children of current directory
    //extract the one with sanme fileName and isDirectory to false;
    File* tragetFile = nullptr;
    for(File* child : dir->children){
        if(child->name == fileName && !child->isDirectory){
            tragetFile = child;
            break;
        }
    }

    //if not fond
    if(!tragetFile){
        cout<<"Error: File not found"<<endl;
        return;
    }

    //read content from the target file
    vector<int> blocks = tragetFile->blocks;
    int fileSize = tragetFile->size;
    string content = readContentFromBlocks(blocks, fileSize);
    cout<<"======"<<tragetFile->name<<"======"<<endl;
    cout<<content<<endl;
    
}

