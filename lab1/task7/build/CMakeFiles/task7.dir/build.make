# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/alexandr/2-2-lab/lab1/task7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandr/2-2-lab/lab1/task7/build

# Include any dependencies generated for this target.
include CMakeFiles/task7.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/task7.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/task7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task7.dir/flags.make

CMakeFiles/task7.dir/src/task7.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/task7.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/task7.cpp
CMakeFiles/task7.dir/src/task7.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/task7.dir/src/task7.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/task7.cpp.o -MF CMakeFiles/task7.dir/src/task7.cpp.o.d -o CMakeFiles/task7.dir/src/task7.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/task7.cpp

CMakeFiles/task7.dir/src/task7.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/task7.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/task7.cpp > CMakeFiles/task7.dir/src/task7.cpp.i

CMakeFiles/task7.dir/src/task7.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/task7.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/task7.cpp -o CMakeFiles/task7.dir/src/task7.cpp.s

CMakeFiles/task7.dir/src/builder/builder.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/builder/builder.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/builder/builder.cpp
CMakeFiles/task7.dir/src/builder/builder.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/task7.dir/src/builder/builder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/builder/builder.cpp.o -MF CMakeFiles/task7.dir/src/builder/builder.cpp.o.d -o CMakeFiles/task7.dir/src/builder/builder.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/builder/builder.cpp

CMakeFiles/task7.dir/src/builder/builder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/builder/builder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/builder/builder.cpp > CMakeFiles/task7.dir/src/builder/builder.cpp.i

CMakeFiles/task7.dir/src/builder/builder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/builder/builder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/builder/builder.cpp -o CMakeFiles/task7.dir/src/builder/builder.cpp.s

CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/builder_concrete/builder_concrete.cpp
CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o -MF CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o.d -o CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/builder_concrete/builder_concrete.cpp

CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/builder_concrete/builder_concrete.cpp > CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.i

CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/builder_concrete/builder_concrete.cpp -o CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.s

CMakeFiles/task7.dir/src/logger/logger.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/logger/logger.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/logger/logger.cpp
CMakeFiles/task7.dir/src/logger/logger.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/task7.dir/src/logger/logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/logger/logger.cpp.o -MF CMakeFiles/task7.dir/src/logger/logger.cpp.o.d -o CMakeFiles/task7.dir/src/logger/logger.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/logger/logger.cpp

CMakeFiles/task7.dir/src/logger/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/logger/logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/logger/logger.cpp > CMakeFiles/task7.dir/src/logger/logger.cpp.i

CMakeFiles/task7.dir/src/logger/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/logger/logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/logger/logger.cpp -o CMakeFiles/task7.dir/src/logger/logger.cpp.s

CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/logger_concrete/logger_concrete.cpp
CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o -MF CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o.d -o CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/logger_concrete/logger_concrete.cpp

CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/logger_concrete/logger_concrete.cpp > CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.i

CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/logger_concrete/logger_concrete.cpp -o CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.s

CMakeFiles/task7.dir/src/memory/memory.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/memory/memory.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/memory/memory.cpp
CMakeFiles/task7.dir/src/memory/memory.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/task7.dir/src/memory/memory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/memory/memory.cpp.o -MF CMakeFiles/task7.dir/src/memory/memory.cpp.o.d -o CMakeFiles/task7.dir/src/memory/memory.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/memory/memory.cpp

CMakeFiles/task7.dir/src/memory/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/memory/memory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/memory/memory.cpp > CMakeFiles/task7.dir/src/memory/memory.cpp.i

CMakeFiles/task7.dir/src/memory/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/memory/memory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/memory/memory.cpp -o CMakeFiles/task7.dir/src/memory/memory.cpp.s

CMakeFiles/task7.dir/src/allocator/allocator.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/allocator/allocator.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/allocator/allocator.cpp
CMakeFiles/task7.dir/src/allocator/allocator.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/task7.dir/src/allocator/allocator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/allocator/allocator.cpp.o -MF CMakeFiles/task7.dir/src/allocator/allocator.cpp.o.d -o CMakeFiles/task7.dir/src/allocator/allocator.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/allocator/allocator.cpp

CMakeFiles/task7.dir/src/allocator/allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/allocator/allocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/allocator/allocator.cpp > CMakeFiles/task7.dir/src/allocator/allocator.cpp.i

CMakeFiles/task7.dir/src/allocator/allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/allocator/allocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/allocator/allocator.cpp -o CMakeFiles/task7.dir/src/allocator/allocator.cpp.s

CMakeFiles/task7.dir/src/long_number/long_number.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/long_number/long_number.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/long_number/long_number.cpp
CMakeFiles/task7.dir/src/long_number/long_number.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/task7.dir/src/long_number/long_number.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/long_number/long_number.cpp.o -MF CMakeFiles/task7.dir/src/long_number/long_number.cpp.o.d -o CMakeFiles/task7.dir/src/long_number/long_number.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/long_number/long_number.cpp

CMakeFiles/task7.dir/src/long_number/long_number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/long_number/long_number.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/long_number/long_number.cpp > CMakeFiles/task7.dir/src/long_number/long_number.cpp.i

CMakeFiles/task7.dir/src/long_number/long_number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/long_number/long_number.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/long_number/long_number.cpp -o CMakeFiles/task7.dir/src/long_number/long_number.cpp.s

CMakeFiles/task7.dir/src/string_number/string_number.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/string_number/string_number.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/string_number/string_number.cpp
CMakeFiles/task7.dir/src/string_number/string_number.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/task7.dir/src/string_number/string_number.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/string_number/string_number.cpp.o -MF CMakeFiles/task7.dir/src/string_number/string_number.cpp.o.d -o CMakeFiles/task7.dir/src/string_number/string_number.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/string_number/string_number.cpp

CMakeFiles/task7.dir/src/string_number/string_number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/string_number/string_number.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/string_number/string_number.cpp > CMakeFiles/task7.dir/src/string_number/string_number.cpp.i

CMakeFiles/task7.dir/src/string_number/string_number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/string_number/string_number.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/string_number/string_number.cpp -o CMakeFiles/task7.dir/src/string_number/string_number.cpp.s

CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/vector_number/vector_number.cpp
CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o -MF CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o.d -o CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/vector_number/vector_number.cpp

CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/vector_number/vector_number.cpp > CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.i

CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/vector_number/vector_number.cpp -o CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.s

CMakeFiles/task7.dir/src/bigint/bigint.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/bigint/bigint.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/bigint/bigint.cpp
CMakeFiles/task7.dir/src/bigint/bigint.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/task7.dir/src/bigint/bigint.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/bigint/bigint.cpp.o -MF CMakeFiles/task7.dir/src/bigint/bigint.cpp.o.d -o CMakeFiles/task7.dir/src/bigint/bigint.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/bigint/bigint.cpp

CMakeFiles/task7.dir/src/bigint/bigint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/bigint/bigint.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/bigint/bigint.cpp > CMakeFiles/task7.dir/src/bigint/bigint.cpp.i

CMakeFiles/task7.dir/src/bigint/bigint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/bigint/bigint.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/bigint/bigint.cpp -o CMakeFiles/task7.dir/src/bigint/bigint.cpp.s

CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o: CMakeFiles/task7.dir/flags.make
CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o: /home/alexandr/2-2-lab/lab1/task7/src/bigint_concrete/bigint_concrete.cpp
CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o: CMakeFiles/task7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o -MF CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o.d -o CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o -c /home/alexandr/2-2-lab/lab1/task7/src/bigint_concrete/bigint_concrete.cpp

CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandr/2-2-lab/lab1/task7/src/bigint_concrete/bigint_concrete.cpp > CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.i

CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandr/2-2-lab/lab1/task7/src/bigint_concrete/bigint_concrete.cpp -o CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.s

# Object files for target task7
task7_OBJECTS = \
"CMakeFiles/task7.dir/src/task7.cpp.o" \
"CMakeFiles/task7.dir/src/builder/builder.cpp.o" \
"CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o" \
"CMakeFiles/task7.dir/src/logger/logger.cpp.o" \
"CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o" \
"CMakeFiles/task7.dir/src/memory/memory.cpp.o" \
"CMakeFiles/task7.dir/src/allocator/allocator.cpp.o" \
"CMakeFiles/task7.dir/src/long_number/long_number.cpp.o" \
"CMakeFiles/task7.dir/src/string_number/string_number.cpp.o" \
"CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o" \
"CMakeFiles/task7.dir/src/bigint/bigint.cpp.o" \
"CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o"

# External object files for target task7
task7_EXTERNAL_OBJECTS =

task7: CMakeFiles/task7.dir/src/task7.cpp.o
task7: CMakeFiles/task7.dir/src/builder/builder.cpp.o
task7: CMakeFiles/task7.dir/src/builder_concrete/builder_concrete.cpp.o
task7: CMakeFiles/task7.dir/src/logger/logger.cpp.o
task7: CMakeFiles/task7.dir/src/logger_concrete/logger_concrete.cpp.o
task7: CMakeFiles/task7.dir/src/memory/memory.cpp.o
task7: CMakeFiles/task7.dir/src/allocator/allocator.cpp.o
task7: CMakeFiles/task7.dir/src/long_number/long_number.cpp.o
task7: CMakeFiles/task7.dir/src/string_number/string_number.cpp.o
task7: CMakeFiles/task7.dir/src/vector_number/vector_number.cpp.o
task7: CMakeFiles/task7.dir/src/bigint/bigint.cpp.o
task7: CMakeFiles/task7.dir/src/bigint_concrete/bigint_concrete.cpp.o
task7: CMakeFiles/task7.dir/build.make
task7: CMakeFiles/task7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable task7"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task7.dir/build: task7
.PHONY : CMakeFiles/task7.dir/build

CMakeFiles/task7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task7.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task7.dir/clean

CMakeFiles/task7.dir/depend:
	cd /home/alexandr/2-2-lab/lab1/task7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandr/2-2-lab/lab1/task7 /home/alexandr/2-2-lab/lab1/task7 /home/alexandr/2-2-lab/lab1/task7/build /home/alexandr/2-2-lab/lab1/task7/build /home/alexandr/2-2-lab/lab1/task7/build/CMakeFiles/task7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task7.dir/depend

