# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLionProjects\lexAnalyzer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLionProjects\lexAnalyzer\cmake-build-debug-coverage

# Include any dependencies generated for this target.
include CMakeFiles/lexAnalyzer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lexAnalyzer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lexAnalyzer.dir/flags.make

CMakeFiles/lexAnalyzer.dir/main.c.obj: CMakeFiles/lexAnalyzer.dir/flags.make
CMakeFiles/lexAnalyzer.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\lexAnalyzer\cmake-build-debug-coverage\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lexAnalyzer.dir/main.c.obj"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lexAnalyzer.dir\main.c.obj   -c D:\CLionProjects\lexAnalyzer\main.c

CMakeFiles/lexAnalyzer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lexAnalyzer.dir/main.c.i"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionProjects\lexAnalyzer\main.c > CMakeFiles\lexAnalyzer.dir\main.c.i

CMakeFiles/lexAnalyzer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lexAnalyzer.dir/main.c.s"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionProjects\lexAnalyzer\main.c -o CMakeFiles\lexAnalyzer.dir\main.c.s

# Object files for target lexAnalyzer
lexAnalyzer_OBJECTS = \
"CMakeFiles/lexAnalyzer.dir/main.c.obj"

# External object files for target lexAnalyzer
lexAnalyzer_EXTERNAL_OBJECTS =

lexAnalyzer.exe: CMakeFiles/lexAnalyzer.dir/main.c.obj
lexAnalyzer.exe: CMakeFiles/lexAnalyzer.dir/build.make
lexAnalyzer.exe: CMakeFiles/lexAnalyzer.dir/linklibs.rsp
lexAnalyzer.exe: CMakeFiles/lexAnalyzer.dir/objects1.rsp
lexAnalyzer.exe: CMakeFiles/lexAnalyzer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\lexAnalyzer\cmake-build-debug-coverage\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lexAnalyzer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lexAnalyzer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lexAnalyzer.dir/build: lexAnalyzer.exe

.PHONY : CMakeFiles/lexAnalyzer.dir/build

CMakeFiles/lexAnalyzer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lexAnalyzer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lexAnalyzer.dir/clean

CMakeFiles/lexAnalyzer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\lexAnalyzer D:\CLionProjects\lexAnalyzer D:\CLionProjects\lexAnalyzer\cmake-build-debug-coverage D:\CLionProjects\lexAnalyzer\cmake-build-debug-coverage D:\CLionProjects\lexAnalyzer\cmake-build-debug-coverage\CMakeFiles\lexAnalyzer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lexAnalyzer.dir/depend

