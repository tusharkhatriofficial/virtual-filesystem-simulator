# Custom File System Simulator (tushell)

This project is a **custom file system simulator** written in modern C++. It emulates a FAT-style block-based file system with a command-line shell interface called `tushell`.

Designed with low-level systems programming in mind, this project showcases practical understanding of:

- Memory and block allocation
- Directory hierarchies
- File metadata and simulation
- Shell-style command processing
- Core OS concepts like paging, hierarchy traversal, and content persistence

---

## 🔧 Features

- 📁 Create deeply nested directories using `mkdir`
- 📝 Create files with content using `write`
- 📂 Traverse and inspect directories with `ls`
- 📖 Read file contents with `read`
- 📊 View file/directory metadata with `stat`
- 🧼 Block allocation simulation for file storage
- ✅ Prevent duplicate file creation
- 🚫 Error handling for invalid paths
- 🧠 Time-stamping for file creation

---

## 🚀 Example Usage (via `tushell`)

```bash
> mkdir /users/tusharkhatri/docs
Directory created at: /users/tusharkhatri/docs

> write /users/tusharkhatri/docs/oop.java public class HelloWorld {}

> ls /users/tusharkhatri/docs
[FILE] oop.java

> read /users/tusharkhatri/docs/oop.java
======oop.java======
public class HelloWorld {}

> stat /users/tusharkhatri/docs/oop.java
File: oop.java
Type: File
Size: 31 bytes
Created At: Mon Jul 07 01:32:15 2025
Blocks Used: 1
Block Numbers: [0]
```

## Project structure
├── main.cpp                 # Entry point, shell loop<br>
├── fs_core.h / fs_core.cpp # File system logic (blocks, files, metadata)<br>
├── fs_commands.h/.cpp      # All shell commands (mkdir, write, read, ls, stat)<br>
├── Makefile                # Build automation<br>
├── README.md               # You're reading it<br>


## 🔄 How to Build and Run

### 🧑‍💻 Prerequisites

- C++17 or above
- A Unix-like terminal (macOS/Linux)
- `g++` or `clang++` installed

---

### 🏗️ Build (with Make)

```bash
make
```

### ▶️ Run the shell

```bash
./filesystem
```
### 🔚 Exit the shell

```bash
exit
```

### 📦 Portability

The entire shell runs as a **single executable**, with no external dependencies.

It can be extended to support:

- ✅ **Windows builds** using WSL, MinGW, or Visual Studio
- 🌐 **Cross-platform support** via CMake
- 🕸️ **Browser-based simulation** via WebAssembly (WASM)
