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
include lib/CMakeFiles/Engineer.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/Engineer.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/Engineer.dir/flags.make

lib/CMakeFiles/Engineer.dir/global/math/angl.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/angl.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/angl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/Engineer.dir/global/math/angl.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/angl.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/angl.c

lib/CMakeFiles/Engineer.dir/global/math/angl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/angl.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/angl.c > CMakeFiles/Engineer.dir/global/math/angl.c.i

lib/CMakeFiles/Engineer.dir/global/math/angl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/angl.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/angl.c -o CMakeFiles/Engineer.dir/global/math/angl.c.s

lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/angl.c.o


lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/cordic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/cordic.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/cordic.c

lib/CMakeFiles/Engineer.dir/global/math/cordic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/cordic.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/cordic.c > CMakeFiles/Engineer.dir/global/math/cordic.c.i

lib/CMakeFiles/Engineer.dir/global/math/cordic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/cordic.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/cordic.c -o CMakeFiles/Engineer.dir/global/math/cordic.c.s

lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o


lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/mtrx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/mtrx.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/mtrx.c

lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/mtrx.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/mtrx.c > CMakeFiles/Engineer.dir/global/math/mtrx.c.i

lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/mtrx.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/mtrx.c -o CMakeFiles/Engineer.dir/global/math/mtrx.c.s

lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o


lib/CMakeFiles/Engineer.dir/global/math/quat.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/quat.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/quat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lib/CMakeFiles/Engineer.dir/global/math/quat.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/quat.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/quat.c

lib/CMakeFiles/Engineer.dir/global/math/quat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/quat.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/quat.c > CMakeFiles/Engineer.dir/global/math/quat.c.i

lib/CMakeFiles/Engineer.dir/global/math/quat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/quat.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/quat.c -o CMakeFiles/Engineer.dir/global/math/quat.c.s

lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/quat.c.o


lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/sclr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/sclr.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/sclr.c

lib/CMakeFiles/Engineer.dir/global/math/sclr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/sclr.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/sclr.c > CMakeFiles/Engineer.dir/global/math/sclr.c.i

lib/CMakeFiles/Engineer.dir/global/math/sclr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/sclr.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/sclr.c -o CMakeFiles/Engineer.dir/global/math/sclr.c.s

lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o


lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/vec2.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec2.c

lib/CMakeFiles/Engineer.dir/global/math/vec2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/vec2.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec2.c > CMakeFiles/Engineer.dir/global/math/vec2.c.i

lib/CMakeFiles/Engineer.dir/global/math/vec2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/vec2.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec2.c -o CMakeFiles/Engineer.dir/global/math/vec2.c.s

lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o


lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/global/math/vec3.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec3.c

lib/CMakeFiles/Engineer.dir/global/math/vec3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/global/math/vec3.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec3.c > CMakeFiles/Engineer.dir/global/math/vec3.c.i

lib/CMakeFiles/Engineer.dir/global/math/vec3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/global/math/vec3.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/global/math/vec3.c -o CMakeFiles/Engineer.dir/global/math/vec3.c.s

lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.requires

lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.provides: lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.provides

lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.provides.build: lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o


lib/CMakeFiles/Engineer.dir/engineer_node.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/engineer_node.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_node.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lib/CMakeFiles/Engineer.dir/engineer_node.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/engineer_node.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_node.c

lib/CMakeFiles/Engineer.dir/engineer_node.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/engineer_node.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_node.c > CMakeFiles/Engineer.dir/engineer_node.c.i

lib/CMakeFiles/Engineer.dir/engineer_node.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/engineer_node.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_node.c -o CMakeFiles/Engineer.dir/engineer_node.c.s

lib/CMakeFiles/Engineer.dir/engineer_node.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/engineer_node.c.o.requires

lib/CMakeFiles/Engineer.dir/engineer_node.c.o.provides: lib/CMakeFiles/Engineer.dir/engineer_node.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/engineer_node.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/engineer_node.c.o.provides

lib/CMakeFiles/Engineer.dir/engineer_node.c.o.provides.build: lib/CMakeFiles/Engineer.dir/engineer_node.c.o


lib/CMakeFiles/Engineer.dir/engineer_scene.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/engineer_scene.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_scene.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lib/CMakeFiles/Engineer.dir/engineer_scene.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/engineer_scene.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_scene.c

lib/CMakeFiles/Engineer.dir/engineer_scene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/engineer_scene.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_scene.c > CMakeFiles/Engineer.dir/engineer_scene.c.i

lib/CMakeFiles/Engineer.dir/engineer_scene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/engineer_scene.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_scene.c -o CMakeFiles/Engineer.dir/engineer_scene.c.s

lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.requires

lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.provides: lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.provides

lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.provides.build: lib/CMakeFiles/Engineer.dir/engineer_scene.c.o


lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_viewport.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/engineer_viewport.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_viewport.c

lib/CMakeFiles/Engineer.dir/engineer_viewport.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/engineer_viewport.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_viewport.c > CMakeFiles/Engineer.dir/engineer_viewport.c.i

lib/CMakeFiles/Engineer.dir/engineer_viewport.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/engineer_viewport.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer_viewport.c -o CMakeFiles/Engineer.dir/engineer_viewport.c.s

lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.requires

lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.provides: lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.provides

lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.provides.build: lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o


lib/CMakeFiles/Engineer.dir/engineer.c.o: lib/CMakeFiles/Engineer.dir/flags.make
lib/CMakeFiles/Engineer.dir/engineer.c.o: /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object lib/CMakeFiles/Engineer.dir/engineer.c.o"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Engineer.dir/engineer.c.o   -c /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer.c

lib/CMakeFiles/Engineer.dir/engineer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Engineer.dir/engineer.c.i"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer.c > CMakeFiles/Engineer.dir/engineer.c.i

lib/CMakeFiles/Engineer.dir/engineer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Engineer.dir/engineer.c.s"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib/engineer.c -o CMakeFiles/Engineer.dir/engineer.c.s

lib/CMakeFiles/Engineer.dir/engineer.c.o.requires:

.PHONY : lib/CMakeFiles/Engineer.dir/engineer.c.o.requires

lib/CMakeFiles/Engineer.dir/engineer.c.o.provides: lib/CMakeFiles/Engineer.dir/engineer.c.o.requires
	$(MAKE) -f lib/CMakeFiles/Engineer.dir/build.make lib/CMakeFiles/Engineer.dir/engineer.c.o.provides.build
.PHONY : lib/CMakeFiles/Engineer.dir/engineer.c.o.provides

lib/CMakeFiles/Engineer.dir/engineer.c.o.provides.build: lib/CMakeFiles/Engineer.dir/engineer.c.o


# Object files for target Engineer
Engineer_OBJECTS = \
"CMakeFiles/Engineer.dir/global/math/angl.c.o" \
"CMakeFiles/Engineer.dir/global/math/cordic.c.o" \
"CMakeFiles/Engineer.dir/global/math/mtrx.c.o" \
"CMakeFiles/Engineer.dir/global/math/quat.c.o" \
"CMakeFiles/Engineer.dir/global/math/sclr.c.o" \
"CMakeFiles/Engineer.dir/global/math/vec2.c.o" \
"CMakeFiles/Engineer.dir/global/math/vec3.c.o" \
"CMakeFiles/Engineer.dir/engineer_node.c.o" \
"CMakeFiles/Engineer.dir/engineer_scene.c.o" \
"CMakeFiles/Engineer.dir/engineer_viewport.c.o" \
"CMakeFiles/Engineer.dir/engineer.c.o"

# External object files for target Engineer
Engineer_EXTERNAL_OBJECTS =

lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/angl.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/quat.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/engineer_node.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/engineer_scene.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/engineer.c.o
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/build.make
lib/libEngineer.so: /usr/lib64/libdb.so
lib/libEngineer.so: /opt/efler/lib/libeio.so
lib/libEngineer.so: /opt/efler/lib/libeina.so
lib/libEngineer.so: /opt/efler/lib/libeet.so
lib/libEngineer.so: /opt/efler/lib/libecore.so
lib/libEngineer.so: /opt/efler/lib/libecore_file.so
lib/libEngineer.so: /opt/efler/lib/libeo.so
lib/libEngineer.so: /opt/efler/lib/libevas.so
lib/libEngineer.so: /opt/efler/lib/libefl.so
lib/libEngineer.so: /opt/efler/lib/libefreet.so
lib/libEngineer.so: /opt/efler/lib/libefreet_trash.so
lib/libEngineer.so: /opt/efler/lib/libelementary.so
lib/libEngineer.so: lib/CMakeFiles/Engineer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brokenshakles/Projects/SoftwareEngines/Engineer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C shared library libEngineer.so"
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Engineer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/Engineer.dir/build: lib/libEngineer.so

.PHONY : lib/CMakeFiles/Engineer.dir/build

lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/angl.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/cordic.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/mtrx.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/quat.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/sclr.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/vec2.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/global/math/vec3.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/engineer_node.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/engineer_scene.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/engineer_viewport.c.o.requires
lib/CMakeFiles/Engineer.dir/requires: lib/CMakeFiles/Engineer.dir/engineer.c.o.requires

.PHONY : lib/CMakeFiles/Engineer.dir/requires

lib/CMakeFiles/Engineer.dir/clean:
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/Engineer.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/Engineer.dir/clean

lib/CMakeFiles/Engineer.dir/depend:
	cd /home/brokenshakles/Projects/SoftwareEngines/Engineer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brokenshakles/Projects/SoftwareEngines/Engineer/src /home/brokenshakles/Projects/SoftwareEngines/Engineer/src/lib /home/brokenshakles/Projects/SoftwareEngines/Engineer/build /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib /home/brokenshakles/Projects/SoftwareEngines/Engineer/build/lib/CMakeFiles/Engineer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/Engineer.dir/depend

