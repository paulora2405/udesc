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
CMAKE_SOURCE_DIR = /home/paulo/git/soft_fase3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paulo/git/soft_fase3/build

# Include any dependencies generated for this target.
include test/CMakeFiles/Soft_fase3_tests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/Soft_fase3_tests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/Soft_fase3_tests.dir/flags.make

test/CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.o: test/CMakeFiles/Soft_fase3_tests.dir/flags.make
test/CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.o: ../test/AlunoUnitTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulo/git/soft_fase3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.o"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.o -c /home/paulo/git/soft_fase3/test/AlunoUnitTest.cpp

test/CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.i"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paulo/git/soft_fase3/test/AlunoUnitTest.cpp > CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.i

test/CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.s"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paulo/git/soft_fase3/test/AlunoUnitTest.cpp -o CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.s

test/CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.o: test/CMakeFiles/Soft_fase3_tests.dir/flags.make
test/CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.o: ../test/ProfessorUnitTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulo/git/soft_fase3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.o"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.o -c /home/paulo/git/soft_fase3/test/ProfessorUnitTest.cpp

test/CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.i"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paulo/git/soft_fase3/test/ProfessorUnitTest.cpp > CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.i

test/CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.s"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paulo/git/soft_fase3/test/ProfessorUnitTest.cpp -o CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.s

test/CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.o: test/CMakeFiles/Soft_fase3_tests.dir/flags.make
test/CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.o: ../test/MateriaUnitTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulo/git/soft_fase3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.o"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.o -c /home/paulo/git/soft_fase3/test/MateriaUnitTest.cpp

test/CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.i"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paulo/git/soft_fase3/test/MateriaUnitTest.cpp > CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.i

test/CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.s"
	cd /home/paulo/git/soft_fase3/build/test && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paulo/git/soft_fase3/test/MateriaUnitTest.cpp -o CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.s

# Object files for target Soft_fase3_tests
Soft_fase3_tests_OBJECTS = \
"CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.o" \
"CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.o" \
"CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.o"

# External object files for target Soft_fase3_tests
Soft_fase3_tests_EXTERNAL_OBJECTS =

test/Soft_fase3_tests: test/CMakeFiles/Soft_fase3_tests.dir/AlunoUnitTest.cpp.o
test/Soft_fase3_tests: test/CMakeFiles/Soft_fase3_tests.dir/ProfessorUnitTest.cpp.o
test/Soft_fase3_tests: test/CMakeFiles/Soft_fase3_tests.dir/MateriaUnitTest.cpp.o
test/Soft_fase3_tests: test/CMakeFiles/Soft_fase3_tests.dir/build.make
test/Soft_fase3_tests: lib/libgtest_maind.a
test/Soft_fase3_tests: libSoft_fase3.a
test/Soft_fase3_tests: lib/libgtestd.a
test/Soft_fase3_tests: test/CMakeFiles/Soft_fase3_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paulo/git/soft_fase3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Soft_fase3_tests"
	cd /home/paulo/git/soft_fase3/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Soft_fase3_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/Soft_fase3_tests.dir/build: test/Soft_fase3_tests

.PHONY : test/CMakeFiles/Soft_fase3_tests.dir/build

test/CMakeFiles/Soft_fase3_tests.dir/clean:
	cd /home/paulo/git/soft_fase3/build/test && $(CMAKE_COMMAND) -P CMakeFiles/Soft_fase3_tests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/Soft_fase3_tests.dir/clean

test/CMakeFiles/Soft_fase3_tests.dir/depend:
	cd /home/paulo/git/soft_fase3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulo/git/soft_fase3 /home/paulo/git/soft_fase3/test /home/paulo/git/soft_fase3/build /home/paulo/git/soft_fase3/build/test /home/paulo/git/soft_fase3/build/test/CMakeFiles/Soft_fase3_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/Soft_fase3_tests.dir/depend

