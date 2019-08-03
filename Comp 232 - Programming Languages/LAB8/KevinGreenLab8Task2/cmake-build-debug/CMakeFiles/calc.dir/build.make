# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Volumes/CLion/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Volumes/CLion/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/calc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/calc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calc.dir/flags.make

calcParser.c: ../calc/calc.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][calcParser] Building parser with bison 2.3"
	cd /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2 && /usr/bin/bison -d -o /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcParser.c calc/calc.y

calcParser.h: calcParser.c
	@$(CMAKE_COMMAND) -E touch_nocreate calcParser.h

calcScanner.c: ../calc/calc.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][calcScanner] Building scanner with flex 2.5.35"
	cd /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2 && /usr/bin/flex -o/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcScanner.c calc/calc.l

CMakeFiles/calc.dir/calc/calc.c.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/calc/calc.c.o: ../calc/calc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/calc.dir/calc/calc.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/calc.dir/calc/calc.c.o   -c /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/calc/calc.c

CMakeFiles/calc.dir/calc/calc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/calc.dir/calc/calc.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/calc/calc.c > CMakeFiles/calc.dir/calc/calc.c.i

CMakeFiles/calc.dir/calc/calc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/calc.dir/calc/calc.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/calc/calc.c -o CMakeFiles/calc.dir/calc/calc.c.s

CMakeFiles/calc.dir/calc/calc.c.o.requires:

.PHONY : CMakeFiles/calc.dir/calc/calc.c.o.requires

CMakeFiles/calc.dir/calc/calc.c.o.provides: CMakeFiles/calc.dir/calc/calc.c.o.requires
	$(MAKE) -f CMakeFiles/calc.dir/build.make CMakeFiles/calc.dir/calc/calc.c.o.provides.build
.PHONY : CMakeFiles/calc.dir/calc/calc.c.o.provides

CMakeFiles/calc.dir/calc/calc.c.o.provides.build: CMakeFiles/calc.dir/calc/calc.c.o


CMakeFiles/calc.dir/calcScanner.c.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/calcScanner.c.o: calcScanner.c
CMakeFiles/calc.dir/calcScanner.c.o: calcParser.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/calc.dir/calcScanner.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/calc.dir/calcScanner.c.o   -c /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcScanner.c

CMakeFiles/calc.dir/calcScanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/calc.dir/calcScanner.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcScanner.c > CMakeFiles/calc.dir/calcScanner.c.i

CMakeFiles/calc.dir/calcScanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/calc.dir/calcScanner.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcScanner.c -o CMakeFiles/calc.dir/calcScanner.c.s

CMakeFiles/calc.dir/calcScanner.c.o.requires:

.PHONY : CMakeFiles/calc.dir/calcScanner.c.o.requires

CMakeFiles/calc.dir/calcScanner.c.o.provides: CMakeFiles/calc.dir/calcScanner.c.o.requires
	$(MAKE) -f CMakeFiles/calc.dir/build.make CMakeFiles/calc.dir/calcScanner.c.o.provides.build
.PHONY : CMakeFiles/calc.dir/calcScanner.c.o.provides

CMakeFiles/calc.dir/calcScanner.c.o.provides.build: CMakeFiles/calc.dir/calcScanner.c.o


CMakeFiles/calc.dir/calcParser.c.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/calcParser.c.o: calcParser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/calc.dir/calcParser.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/calc.dir/calcParser.c.o   -c /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcParser.c

CMakeFiles/calc.dir/calcParser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/calc.dir/calcParser.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcParser.c > CMakeFiles/calc.dir/calcParser.c.i

CMakeFiles/calc.dir/calcParser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/calc.dir/calcParser.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/calcParser.c -o CMakeFiles/calc.dir/calcParser.c.s

CMakeFiles/calc.dir/calcParser.c.o.requires:

.PHONY : CMakeFiles/calc.dir/calcParser.c.o.requires

CMakeFiles/calc.dir/calcParser.c.o.provides: CMakeFiles/calc.dir/calcParser.c.o.requires
	$(MAKE) -f CMakeFiles/calc.dir/build.make CMakeFiles/calc.dir/calcParser.c.o.provides.build
.PHONY : CMakeFiles/calc.dir/calcParser.c.o.provides

CMakeFiles/calc.dir/calcParser.c.o.provides.build: CMakeFiles/calc.dir/calcParser.c.o


# Object files for target calc
calc_OBJECTS = \
"CMakeFiles/calc.dir/calc/calc.c.o" \
"CMakeFiles/calc.dir/calcScanner.c.o" \
"CMakeFiles/calc.dir/calcParser.c.o"

# External object files for target calc
calc_EXTERNAL_OBJECTS =

calc: CMakeFiles/calc.dir/calc/calc.c.o
calc: CMakeFiles/calc.dir/calcScanner.c.o
calc: CMakeFiles/calc.dir/calcParser.c.o
calc: CMakeFiles/calc.dir/build.make
calc: CMakeFiles/calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable calc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calc.dir/build: calc

.PHONY : CMakeFiles/calc.dir/build

CMakeFiles/calc.dir/requires: CMakeFiles/calc.dir/calc/calc.c.o.requires
CMakeFiles/calc.dir/requires: CMakeFiles/calc.dir/calcScanner.c.o.requires
CMakeFiles/calc.dir/requires: CMakeFiles/calc.dir/calcParser.c.o.requires

.PHONY : CMakeFiles/calc.dir/requires

CMakeFiles/calc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/calc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/calc.dir/clean

CMakeFiles/calc.dir/depend: calcParser.c
CMakeFiles/calc.dir/depend: calcParser.h
CMakeFiles/calc.dir/depend: calcScanner.c
	cd /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2 /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2 /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug /Volumes/USB/COMP232/LAB8/KevinGreenLab8Task2/cmake-build-debug/CMakeFiles/calc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/calc.dir/depend

