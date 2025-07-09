# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files
SRC = main.cpp fs_shell.cpp fs_utils.cpp fs_commands.cpp

# Output binary
OUT = filesystem

# Default target
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

#clean command to remove compiled binary
clean:
	rm -f $(OUT)