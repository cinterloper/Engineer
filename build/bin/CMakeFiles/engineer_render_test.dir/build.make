# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /home/brokenshakles/Projects/SoftwareEngines/Engineer/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brokenshakles/Projects/SoftwareEngines/Engineer/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/engineer_render_test.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/engineer_render_test.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/engineer_render_test.dir/flags.make

bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o: bin/CMakeFiles/engineer_render_test.dir/flags.make
bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/bin/engineer_render_test_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/bin/engineer_render_test_main.c

bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/bin/engineer_render_test_main.c > CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.i

bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/bin/engineer_render_test_main.c -o CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.s

bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.requires:

.PHONY : bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.requires

bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.provides: bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.requires
	$(MAKE) -f bin/CMakeFiles/engineer_render_test.dir/build.make bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.provides.build
.PHONY : bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.provides

bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.provides.build: bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o


# Object files for target engineer_render_test
engineer_render_test_OBJECTS = \
"CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o"

# External object files for target engineer_render_test
engineer_render_test_EXTERNAL_OBJECTS =

bin/engineer_render_test: bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o
bin/engineer_render_test: bin/CMakeFiles/engineer_render_test.dir/build.make
bin/engineer_render_test: lib/libEngineer.so
bin/engineer_render_test: /usr/lib64/libdb.so
bin/engineer_render_test: /opt/efler/lib/libeina.so
bin/engineer_render_test: /opt/efler/lib/libevas.so
bin/engineer_render_test: /opt/efler/lib/libefl.so
bin/engineer_render_test: /opt/efler/lib/libeio.so
bin/engineer_render_test: /opt/efler/lib/libeo.so
bin/engineer_render_test: /opt/efler/lib/libefreet.so
bin/engineer_render_test: /opt/efler/lib/libefreet_trash.so
bin/engineer_render_test: /opt/efler/lib/libecore.so
bin/engineer_render_test: /opt/efler/lib/libecore_file.so
bin/engineer_render_test: /opt/efler/lib/libeet.so
bin/engineer_render_test: /opt/efler/lib/libelementary.so
bin/engineer_render_test: bin/CMakeFiles/engineer_render_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable engineer_render_test"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engineer_render_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/engineer_render_test.dir/build: bin/engineer_render_test

.PHONY : bin/CMakeFiles/engineer_render_test.dir/build

bin/CMakeFiles/engineer_render_test.dir/requires: bin/CMakeFiles/engineer_render_test.dir/engineer_render_test_main.c.o.requires

.PHONY : bin/CMakeFiles/engineer_render_test.dir/requires

bin/CMakeFiles/engineer_render_test.dir/clean:
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/engineer_render_test.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/engineer_render_test.dir/clean

bin/CMakeFiles/engineer_render_test.dir/depend:
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brokenshakles/Projects/SoftwareEngines/Engineer/src /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/bin /home/brokenshakles/Projects/SoftwareEngines/Engineer/build /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/bin/CMakeFiles/engineer_render_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/engineer_render_test.dir/depend

