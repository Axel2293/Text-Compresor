#dirs
CC = gcc
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

#source files list
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

BINS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

TARGET = src/huffman

# Rule to build the executable
$(TARGET): $(BINS)
	$(CC) $^ -o $@ 
	cd src && ./huffman.exe

# Rule to compile source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

#test:
# 	gcc src/main.c -o bin/test.exe
# 	cd bin && ./test.exe

clean:
	rm -f $(TARGET).exe
	rm -f $(BINS)