# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pq-two.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pq-two.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pq-two.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pq-two.dir/flags.make

CMakeFiles/pq-two.dir/data/two/code.cpp.o: CMakeFiles/pq-two.dir/flags.make
CMakeFiles/pq-two.dir/data/two/code.cpp.o: ../data/two/code.cpp
CMakeFiles/pq-two.dir/data/two/code.cpp.o: CMakeFiles/pq-two.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pq-two.dir/data/two/code.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pq-two.dir/data/two/code.cpp.o -MF CMakeFiles/pq-two.dir/data/two/code.cpp.o.d -o CMakeFiles/pq-two.dir/data/two/code.cpp.o -c /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/data/two/code.cpp

CMakeFiles/pq-two.dir/data/two/code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pq-two.dir/data/two/code.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/data/two/code.cpp > CMakeFiles/pq-two.dir/data/two/code.cpp.i

CMakeFiles/pq-two.dir/data/two/code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pq-two.dir/data/two/code.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/data/two/code.cpp -o CMakeFiles/pq-two.dir/data/two/code.cpp.s

# Object files for target pq-two
pq__two_OBJECTS = \
"CMakeFiles/pq-two.dir/data/two/code.cpp.o"

# External object files for target pq-two
pq__two_EXTERNAL_OBJECTS =

pq-two: CMakeFiles/pq-two.dir/data/two/code.cpp.o
pq-two: CMakeFiles/pq-two.dir/build.make
pq-two: CMakeFiles/pq-two.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pq-two"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pq-two.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pq-two.dir/build: pq-two
.PHONY : CMakeFiles/pq-two.dir/build

CMakeFiles/pq-two.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pq-two.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pq-two.dir/clean

CMakeFiles/pq-two.dir/depend:
	cd /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug /mnt/c/Users/86180/Desktop/数据结构/大作业/STLite_ACM/priority_queue/cmake-build-debug/CMakeFiles/pq-two.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pq-two.dir/depend

