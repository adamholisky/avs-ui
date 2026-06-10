#Make config things
.DEFAULT_GOAL := all
SHELL := /bin/bash -O globstar

# Directory structure
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SOURCE_DIR_NAME := src
HEADER_DIR_NAME := include
BUILD_DIR_NAME := build
SOURCE_DIR := $(ROOT_DIR)/$(SOURCE_DIR_NAME)
HEADER_DIR := $(ROOT_DIR)/$(HEADER_DIR_NAME)
BUILD_DIR := $(ROOT_DIR)/$(BUILD_DIR_NAME)

# Basic variables
EXE_NAME := avs-ui-test
SOURCES_CPP := $(shell ls $(SOURCE_DIR_NAME)/**/*.cpp )
SOURCES_C := $(shell ls $(SOURCE_DIR_NAME)/**/*.c )
HEADERS := $(shell ls $(HEADER_DIR_NAME)/**/*.h )
OBJECTS_CPP := $(patsubst %.cpp, $(BUILD_DIR_NAME)/%.o, $(shell echo $(SOURCES_CPP) | xargs -n 1 basename))
OBJECTS_C := $(patsubst %.c, $(BUILD_DIR_NAME)/%.o, $(shell echo $(SOURCES_C) | xargs -n 1 basename))

# Path setup
VPATH = $(shell find $(SOURCE_DIR) -type d -printf "$(SOURCE_DIR_NAME)/%P:")

# Compiler control
CC := /usr/bin/gcc
CPP := /usr/bin/g++
LD := /usr/bin/ld
DEFINES := -DAVS_ENV_LINUX
CFLAGS := -g -O0 -I$(HEADER_DIR) -I/usr/include/SDL2
LDFLAGS := -lSDL2 -lm

# Helpers

mfdebug:
	@echo "Debug Info"
	@echo " "
	@echo "ROOT_DIR:   " $(ROOT_DIR)
	@echo "SOURCE_DIR: " $(SOURCE_DIR)
	@echo "HEADER_DIR: " $(HEADER_DIR)
	@echo "BUILD_DIR:  " $(BUILD_DIR)
	@echo "VPATH:      " $(VPATH)
	@echo " "
	@echo "EXE_NAME:   " $(EXE_NAME)
	@echo "SOURCES_C:  " $(SOURCES_C)
	@echo "OBJECTS_C:  " $(OBJECTS_C)
	@echo "HEADERS:    " $(HEADERS)
	@echo " "
	@echo "CC:         " $(CC)
	@echo "LD:         " $(LD)
	@echo "CFLAGS:     " $(CFLAGS)
	@echo "LDFLAGS:    " $(LDFLAGS)
	@echo "DEFINES:    " $(DEFINES)

# Basic 
all: $(EXE_NAME)

run: $(EXE_NAME)
	./$(EXE_NAME)

run-wayland: $(EXE_NAME)
	SDL_VIDEODRIVER=wayland ./$(EXE_NAME)

clean:
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(ROOT_DIR)/build-temp/*
	rm -rf $(EXE_NAME)

$(EXE_NAME): $(OBJECTS_C) $(OBJECTS_CPP)
	$(CPP) $(CFLAGS) $(OBJECTS_C) $(OBJECTS_CPP) $(LDFLAGS) -o $(EXE_NAME)

build/%.o: %.cpp
	$(CPP) $(CFLAGS) $(DEFINES) -fdiagnostics-color=always -c $< -o $(BUILD_DIR_NAME)/$*.o

build/%.o: %.c
	$(CC) $(CFLAGS) $(DEFINES) -fdiagnostics-color=always -c $< -o $(BUILD_DIR_NAME)/$*.o
