CC = gcc
BUILD_DIR = ./build
BIN_DIR ?= $(BUILD_DIR)/bin
OBJ_DIR ?= $(BUILD_DIR)/obj
TARGET ?= $(BIN_DIR)/brainfuck-interpreter
SRC_DIRS ?= ./src
INC_DIR ?= ./include

SRCS := $(shell find $(SRC_DIRS) -name  *.c)
OBJS := $(SRCS:$(SRC_DIRS)/%.c=$(OBJ_DIR)/%.o)

DEBUG_FLAG := -g
ERROR_FLAGS := -Wall -Wextra
CFLAGS ?= $(INC_FLAGS) -I$(INC_DIR) $(ERROR_FLAGS) $(DEBUG_FLAG)

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_END=\033[0m

.PHONY: all
all : $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIRS)/%.c
	@echo -e "$(COLOUR_GREEN)[X] Compiling c files : $< -> $@$(COLOUR_END)"
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET) : $(OBJS)
	@echo -e "$(COLOUR_GREEN)[X] linking files$(COLOUR_END)"
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean
clean:
	@echo -e "$(COLOUR_RED)[X] Deleting executable $(TARGET)$(COLOUR_END)"
	@$(RM) $(TARGET)
	@echo -e "$(COLOUR_RED)[X] Deleting c object files$(COLOUR_END)"
	@$(RM) $(OBJS)

.PHONY: dirs
dirs: 
	@echo -e "$(COLOUR_GREEN)[X] Creating directories$(COLOUR_END)"
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)