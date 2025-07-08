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
    File* parent;             
    string createdAt;
};

string getCurrentTime(){
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}


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



//command line shell code starts from here
//letting user interact with the file system using basic commands like
//mkdir /tusharkhatri/docs
//write /tusharkhatri/docs/intro.txt Hi I am tushar
//ls /tusharkhatri/docs/
//read /tusharkhatri/docs/intro.txt
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



void mkdir(File* root, const string& path){
    vector<string> folders = splitPath(path);
    File* current = root;

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
        }
        
    }
    cout<<"Directory created at: "<<path<<endl;
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

pair<string, string> splitFilePath(const string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == string::npos)
        return {"", path};  // no slash at all

    string dirPath = (pos == 0) ? "/" : path.substr(0, pos);
    string fileName = path.substr(pos + 1);
    return {dirPath, fileName};
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
    cout<<"File" <<fileName<<" created with "<<blocks.size()<<" blocks."<<endl;


}




void processCommand(File* root, const string& input){
    stringstream ss(input);
    string command;
    ss>>command;
    if(command == "mkdir"){
        string path;
        ss>>path;
        mkdir(root, path);
    }else if(command == "ls"){
        string path;
        ss>>path;
        ls(root, path);
    }else if(command == "write"){
        string path;
        ss>>path;
        string content;
        getline(ss, content);
        content = content.substr(1);
        writeFile(root, path, content);
    // }else if (command == "read") {
    //     string path;
    //     ss >> path;
    //     readFile(root, path);
    // } else if (command == "stat") {
    //     string path;
    //     ss >> path;
    //     statFile(root, path);
    } else {
        cout << "Unknown command: " << command << std::endl;
    }
}


void shell(File* root){
    string input;
    while(true){
        cout<<">";
        getline(cin, input);
        if(input == "exit"){
            break;
        }
        processCommand(root, input);
    }
}



//entry point
int main(){
    File* root = new File();
    root->name = "/";
    root->size = 0;
    root->parent = nullptr;
    root->createdAt = getCurrentTime();

    shell(root);
    return 0;
}