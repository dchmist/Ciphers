# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/radmor/Desktop/fun/Ciphers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/radmor/Desktop/fun/Ciphers/build

# Include any dependencies generated for this target.
include software/src/CMakeFiles/miniAES.dir/depend.make

# Include the progress variables for this target.
include software/src/CMakeFiles/miniAES.dir/progress.make

# Include the compile flags for this target's objects.
include software/src/CMakeFiles/miniAES.dir/flags.make

software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o: software/src/CMakeFiles/miniAES.dir/flags.make
software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o: ../software/src/Ciphers/miniAES/MiniAES.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/radmor/Desktop/fun/Ciphers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o"
	cd /home/radmor/Desktop/fun/Ciphers/build/software/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o -c /home/radmor/Desktop/fun/Ciphers/software/src/Ciphers/miniAES/MiniAES.cpp

software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.i"
	cd /home/radmor/Desktop/fun/Ciphers/build/software/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/radmor/Desktop/fun/Ciphers/software/src/Ciphers/miniAES/MiniAES.cpp > CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.i

software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.s"
	cd /home/radmor/Desktop/fun/Ciphers/build/software/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/radmor/Desktop/fun/Ciphers/software/src/Ciphers/miniAES/MiniAES.cpp -o CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.s

software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.requires:

.PHONY : software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.requires

software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.provides: software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.requires
	$(MAKE) -f software/src/CMakeFiles/miniAES.dir/build.make software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.provides.build
.PHONY : software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.provides

software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.provides.build: software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o


# Object files for target miniAES
miniAES_OBJECTS = \
"CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o"

# External object files for target miniAES
miniAES_EXTERNAL_OBJECTS =

software/src/libminiAES.so: software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o
software/src/libminiAES.so: software/src/CMakeFiles/miniAES.dir/build.make
software/src/libminiAES.so: software/src/CMakeFiles/miniAES.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/radmor/Desktop/fun/Ciphers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libminiAES.so"
	cd /home/radmor/Desktop/fun/Ciphers/build/software/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/miniAES.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
software/src/CMakeFiles/miniAES.dir/build: software/src/libminiAES.so

.PHONY : software/src/CMakeFiles/miniAES.dir/build

software/src/CMakeFiles/miniAES.dir/requires: software/src/CMakeFiles/miniAES.dir/Ciphers/miniAES/MiniAES.cpp.o.requires

.PHONY : software/src/CMakeFiles/miniAES.dir/requires

software/src/CMakeFiles/miniAES.dir/clean:
	cd /home/radmor/Desktop/fun/Ciphers/build/software/src && $(CMAKE_COMMAND) -P CMakeFiles/miniAES.dir/cmake_clean.cmake
.PHONY : software/src/CMakeFiles/miniAES.dir/clean

software/src/CMakeFiles/miniAES.dir/depend:
	cd /home/radmor/Desktop/fun/Ciphers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/radmor/Desktop/fun/Ciphers /home/radmor/Desktop/fun/Ciphers/software/src /home/radmor/Desktop/fun/Ciphers/build /home/radmor/Desktop/fun/Ciphers/build/software/src /home/radmor/Desktop/fun/Ciphers/build/software/src/CMakeFiles/miniAES.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : software/src/CMakeFiles/miniAES.dir/depend
