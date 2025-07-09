#include "fs_utils.h"
#include "fs_commands.h"
#include "fs_shell.h"

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
    }else if (command == "read") {
        string path;
        ss >> path;
        readFile(root, path);
    } else if (command == "stat") {
        string path;
        ss >> path;
        statFile(root, path);
    }else if(command == "help"){
        help();
    } else {
        cout << "Unknown command: " << command << std::endl;
    }
}


void shell(File* root){
    string input;
    while(true){
        cout<<"tushell>>>";
        getline(cin, input);
        if(input == "exit"){
            break;
        }
        processCommand(root, input);
    }
}
