# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/khavelun/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.6682.181/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/khavelun/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.6682.181/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/khavelun/Desktop/development/logscope/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/Catch_tests_run.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/Catch_tests_run.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/Catch_tests_run.dir/flags.make

tests/CMakeFiles/Catch_tests_run.dir/Test1.cpp.o: tests/CMakeFiles/Catch_tests_run.dir/flags.make
tests/CMakeFiles/Catch_tests_run.dir/Test1.cpp.o: ../tests/Test1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/Catch_tests_run.dir/Test1.cpp.o"
	cd /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Catch_tests_run.dir/Test1.cpp.o -c /Users/khavelun/Desktop/development/logscope/backend/tests/Test1.cpp

tests/CMakeFiles/Catch_tests_run.dir/Test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Catch_tests_run.dir/Test1.cpp.i"
	cd /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/khavelun/Desktop/development/logscope/backend/tests/Test1.cpp > CMakeFiles/Catch_tests_run.dir/Test1.cpp.i

tests/CMakeFiles/Catch_tests_run.dir/Test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Catch_tests_run.dir/Test1.cpp.s"
	cd /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/khavelun/Desktop/development/logscope/backend/tests/Test1.cpp -o CMakeFiles/Catch_tests_run.dir/Test1.cpp.s

# Object files for target Catch_tests_run
Catch_tests_run_OBJECTS = \
"CMakeFiles/Catch_tests_run.dir/Test1.cpp.o"

# External object files for target Catch_tests_run
Catch_tests_run_EXTERNAL_OBJECTS =

tests/Catch_tests_run: tests/CMakeFiles/Catch_tests_run.dir/Test1.cpp.o
tests/Catch_tests_run: tests/CMakeFiles/Catch_tests_run.dir/build.make
tests/Catch_tests_run: tests/CMakeFiles/Catch_tests_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Catch_tests_run"
	cd /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Catch_tests_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/Catch_tests_run.dir/build: tests/Catch_tests_run

.PHONY : tests/CMakeFiles/Catch_tests_run.dir/build

tests/CMakeFiles/Catch_tests_run.dir/clean:
	cd /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/Catch_tests_run.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/Catch_tests_run.dir/clean

tests/CMakeFiles/Catch_tests_run.dir/depend:
	cd /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/khavelun/Desktop/development/logscope/backend /Users/khavelun/Desktop/development/logscope/backend/tests /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests /Users/khavelun/Desktop/development/logscope/backend/cmake-build-debug/tests/CMakeFiles/Catch_tests_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/Catch_tests_run.dir/depend

