# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Object files (replace .cpp with .o)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
EXEC = $(OBJ_DIR)/tp2.exe

# Compiler and flags
CXX = g++
CXXFLAGS = -I$(INC_DIR) -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

.PHONY: all clean
