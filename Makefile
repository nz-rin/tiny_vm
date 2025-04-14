# Compiler
CXX 			= g++
CXXFLAGS 		= -g -Wall -Wextra -Iinclude
CXXDBFLAG 		= -DDEBUG

# Directories
DIR_ROOT		= $(PWD)
DIR_BUILD 		= $(DIR_ROOT)/build
DIR_SRC 		= $(DIR_ROOT)/src
DIR_DEBUG 		= $(DIR_ROOT)/debug

# Files
# Source code files
SRC_FILES		= $(wildcard $(DIR_SRC)/*.cxx)

# Main object files
MAIN_O_FILES 	= $(patsubst $(DIR_SRC)/%.cxx, $(DIR_BUILD)/%.o, $(SRC_FILES))

# Debug object files
DEBUG_O_FILES 	= $(patsubst $(DIR_SRC)/%.cxx, $(DIR_DEBUG)/%.o, $(SRC_FILES))

# Debug Main
DEBUG_ELF 		= $(DIR_DEBUG)/main-debug

# Main
MAIN_ELF 		= $(DIR_BUILD)/main

# Default
all:
	@echo "  Run make setup if you dont have a build or debug dir"
	@echo "  To build main or debug run make build-main or build-debug, make build-all builds both"
	@echo "  To run them use make run-build or make run-debug"
	@echo "  CLI can be passed in using make build-main ARGS=\"put args here\" same for build-debug"
	@echo "  there are also 3 clean functions to remove build artifacts, clean-all clean-build and clean-debug"
	@echo "  NOTE, If you have ran the build.sh previously make may fail or run/link incorrect files, be sure to delete the files or run make clean-all"

setup:
	mkdir -p build
	mkdir - debug

clean-all:
	rm -rf $(DIR_BUILD)/*
	rm -rf $(DIR_DEBUG)/*

clean-build:
	rm -rf $(DIR_BUILD)/*

clean-debug:
	rm -rf $(DIR_DEBUG)/*

run-build: $(MAIN_ELF)
	$(MAIN_ELF) $(ARGS)

run-debug: $(DEBUG_ELF)
	$(DEBUG_ELF) $(ARGS)

build-all: $(DEBUG_ELF) $(MAIN_ELF)

build-debug: $(DEBUG_ELF)

build-main: $(MAIN_ELF)


__MAKE_DIR_BUILD:
	mkdir -p build

__MAKE_DIR_DEBUG:
	mkdir -p debug

# Link object files for build main
$(MAIN_ELF): $(MAIN_O_FILES)
	$(CXX) $(CXXFLAGS) -o $(MAIN_ELF) $(MAIN_O_FILES)

# Compile object files for build main
$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cxx | $(DIR_BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files for debug main
$(DEBUG_ELF): $(DEBUG_O_FILES)
	$(CXX) $(CXXFLAGS) $(CXXDBFLAG) -o $(DEBUG_ELF) $(DEBUG_O_FILES)

# Compile object files for debug main
$(DIR_DEBUG)/%.o: $(DIR_SRC)/%.cxx | $(DIR_DEBUG)
	$(CXX) $(CXXFLAGS) $(CXXDBFLAG) -c $< -o $@
