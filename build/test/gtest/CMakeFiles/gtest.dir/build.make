# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/ethanseow/CS/pyjs/fmt-10.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ethanseow/CS/pyjs/build

# Include any dependencies generated for this target.
include test/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include test/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include test/gtest/CMakeFiles/gtest.dir/flags.make

test/gtest/CMakeFiles/gtest.dir/gmock-gtest-all.cc.o: test/gtest/CMakeFiles/gtest.dir/flags.make
test/gtest/CMakeFiles/gtest.dir/gmock-gtest-all.cc.o: /home/ethanseow/CS/pyjs/fmt-10.0.0/test/gtest/gmock-gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethanseow/CS/pyjs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/gtest/CMakeFiles/gtest.dir/gmock-gtest-all.cc.o"
	cd /home/ethanseow/CS/pyjs/build/test/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/gmock-gtest-all.cc.o -c /home/ethanseow/CS/pyjs/fmt-10.0.0/test/gtest/gmock-gtest-all.cc

test/gtest/CMakeFiles/gtest.dir/gmock-gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/gmock-gtest-all.cc.i"
	cd /home/ethanseow/CS/pyjs/build/test/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ethanseow/CS/pyjs/fmt-10.0.0/test/gtest/gmock-gtest-all.cc > CMakeFiles/gtest.dir/gmock-gtest-all.cc.i

test/gtest/CMakeFiles/gtest.dir/gmock-gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/gmock-gtest-all.cc.s"
	cd /home/ethanseow/CS/pyjs/build/test/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ethanseow/CS/pyjs/fmt-10.0.0/test/gtest/gmock-gtest-all.cc -o CMakeFiles/gtest.dir/gmock-gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/gmock-gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

test/gtest/libgtest.a: test/gtest/CMakeFiles/gtest.dir/gmock-gtest-all.cc.o
test/gtest/libgtest.a: test/gtest/CMakeFiles/gtest.dir/build.make
test/gtest/libgtest.a: test/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ethanseow/CS/pyjs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /home/ethanseow/CS/pyjs/build/test/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/ethanseow/CS/pyjs/build/test/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/gtest/CMakeFiles/gtest.dir/build: test/gtest/libgtest.a

.PHONY : test/gtest/CMakeFiles/gtest.dir/build

test/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/ethanseow/CS/pyjs/build/test/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : test/gtest/CMakeFiles/gtest.dir/clean

test/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/ethanseow/CS/pyjs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ethanseow/CS/pyjs/fmt-10.0.0 /home/ethanseow/CS/pyjs/fmt-10.0.0/test/gtest /home/ethanseow/CS/pyjs/build /home/ethanseow/CS/pyjs/build/test/gtest /home/ethanseow/CS/pyjs/build/test/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/gtest/CMakeFiles/gtest.dir/depend
