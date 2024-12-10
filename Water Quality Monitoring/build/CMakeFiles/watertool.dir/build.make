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
CMAKE_SOURCE_DIR = "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build"

# Include any dependencies generated for this target.
include CMakeFiles/watertool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/watertool.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/watertool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/watertool.dir/flags.make

.rcc/qrc_watertool_translations.cpp: watertool_de.qm
.rcc/qrc_watertool_translations.cpp: watertool_fr.qm
.rcc/qrc_watertool_translations.cpp: .rcc/watertool_translations.qrc
.rcc/qrc_watertool_translations.cpp: /usr/lib64/qt6/libexec/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Running rcc for resource watertool_translations"
	/usr/lib64/qt6/libexec/rcc --output "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/.rcc/qrc_watertool_translations.cpp" --name watertool_translations "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/.rcc/watertool_translations.qrc"

CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o: watertool_autogen/mocs_compilation.cpp
CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o -MF CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/watertool_autogen/mocs_compilation.cpp"

CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/watertool_autogen/mocs_compilation.cpp" > CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.i

CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/watertool_autogen/mocs_compilation.cpp" -o CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.s

CMakeFiles/watertool.dir/main.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/main.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/main.cpp
CMakeFiles/watertool.dir/main.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/watertool.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/main.cpp.o -MF CMakeFiles/watertool.dir/main.cpp.o.d -o CMakeFiles/watertool.dir/main.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/main.cpp"

CMakeFiles/watertool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/main.cpp" > CMakeFiles/watertool.dir/main.cpp.i

CMakeFiles/watertool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/main.cpp" -o CMakeFiles/watertool.dir/main.cpp.s

CMakeFiles/watertool.dir/datamanager.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/datamanager.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/datamanager.cpp
CMakeFiles/watertool.dir/datamanager.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/watertool.dir/datamanager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/datamanager.cpp.o -MF CMakeFiles/watertool.dir/datamanager.cpp.o.d -o CMakeFiles/watertool.dir/datamanager.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/datamanager.cpp"

CMakeFiles/watertool.dir/datamanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/datamanager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/datamanager.cpp" > CMakeFiles/watertool.dir/datamanager.cpp.i

CMakeFiles/watertool.dir/datamanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/datamanager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/datamanager.cpp" -o CMakeFiles/watertool.dir/datamanager.cpp.s

CMakeFiles/watertool.dir/mainwindow.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/mainwindow.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/mainwindow.cpp
CMakeFiles/watertool.dir/mainwindow.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/watertool.dir/mainwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/mainwindow.cpp.o -MF CMakeFiles/watertool.dir/mainwindow.cpp.o.d -o CMakeFiles/watertool.dir/mainwindow.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/mainwindow.cpp"

CMakeFiles/watertool.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/mainwindow.cpp" > CMakeFiles/watertool.dir/mainwindow.cpp.i

CMakeFiles/watertool.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/mainwindow.cpp" -o CMakeFiles/watertool.dir/mainwindow.cpp.s

CMakeFiles/watertool.dir/overviewpage.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/overviewpage.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/overviewpage.cpp
CMakeFiles/watertool.dir/overviewpage.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/watertool.dir/overviewpage.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/overviewpage.cpp.o -MF CMakeFiles/watertool.dir/overviewpage.cpp.o.d -o CMakeFiles/watertool.dir/overviewpage.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/overviewpage.cpp"

CMakeFiles/watertool.dir/overviewpage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/overviewpage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/overviewpage.cpp" > CMakeFiles/watertool.dir/overviewpage.cpp.i

CMakeFiles/watertool.dir/overviewpage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/overviewpage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/overviewpage.cpp" -o CMakeFiles/watertool.dir/overviewpage.cpp.s

CMakeFiles/watertool.dir/enviwindow.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/enviwindow.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/enviwindow.cpp
CMakeFiles/watertool.dir/enviwindow.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/watertool.dir/enviwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/enviwindow.cpp.o -MF CMakeFiles/watertool.dir/enviwindow.cpp.o.d -o CMakeFiles/watertool.dir/enviwindow.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/enviwindow.cpp"

CMakeFiles/watertool.dir/enviwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/enviwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/enviwindow.cpp" > CMakeFiles/watertool.dir/enviwindow.cpp.i

CMakeFiles/watertool.dir/enviwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/enviwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/enviwindow.cpp" -o CMakeFiles/watertool.dir/enviwindow.cpp.s

CMakeFiles/watertool.dir/dashboard.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/dashboard.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/dashboard.cpp
CMakeFiles/watertool.dir/dashboard.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/watertool.dir/dashboard.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/dashboard.cpp.o -MF CMakeFiles/watertool.dir/dashboard.cpp.o.d -o CMakeFiles/watertool.dir/dashboard.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/dashboard.cpp"

CMakeFiles/watertool.dir/dashboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/dashboard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/dashboard.cpp" > CMakeFiles/watertool.dir/dashboard.cpp.i

CMakeFiles/watertool.dir/dashboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/dashboard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/dashboard.cpp" -o CMakeFiles/watertool.dir/dashboard.cpp.s

CMakeFiles/watertool.dir/compliance_dashboard.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/compliance_dashboard.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/compliance_dashboard.cpp
CMakeFiles/watertool.dir/compliance_dashboard.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/watertool.dir/compliance_dashboard.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/compliance_dashboard.cpp.o -MF CMakeFiles/watertool.dir/compliance_dashboard.cpp.o.d -o CMakeFiles/watertool.dir/compliance_dashboard.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/compliance_dashboard.cpp"

CMakeFiles/watertool.dir/compliance_dashboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/compliance_dashboard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/compliance_dashboard.cpp" > CMakeFiles/watertool.dir/compliance_dashboard.cpp.i

CMakeFiles/watertool.dir/compliance_dashboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/compliance_dashboard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/compliance_dashboard.cpp" -o CMakeFiles/watertool.dir/compliance_dashboard.cpp.s

CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/fluorinatedcompounds.cpp
CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o -MF CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o.d -o CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/fluorinatedcompounds.cpp"

CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/fluorinatedcompounds.cpp" > CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.i

CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/fluorinatedcompounds.cpp" -o CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.s

CMakeFiles/watertool.dir/pop.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/pop.cpp.o: /uolstore/home/users/sc23a2a/Downloads/Group-Project-main\ (1)/Water\ Quality\ Monitoring/pop.cpp
CMakeFiles/watertool.dir/pop.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/watertool.dir/pop.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/pop.cpp.o -MF CMakeFiles/watertool.dir/pop.cpp.o.d -o CMakeFiles/watertool.dir/pop.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/pop.cpp"

CMakeFiles/watertool.dir/pop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/pop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/pop.cpp" > CMakeFiles/watertool.dir/pop.cpp.i

CMakeFiles/watertool.dir/pop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/pop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/pop.cpp" -o CMakeFiles/watertool.dir/pop.cpp.s

CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o: CMakeFiles/watertool.dir/flags.make
CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o: .rcc/qrc_watertool_translations.cpp
CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o: CMakeFiles/watertool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o -MF CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o.d -o CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o -c "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/.rcc/qrc_watertool_translations.cpp"

CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/.rcc/qrc_watertool_translations.cpp" > CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.i

CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/.rcc/qrc_watertool_translations.cpp" -o CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.s

# Object files for target watertool
watertool_OBJECTS = \
"CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/watertool.dir/main.cpp.o" \
"CMakeFiles/watertool.dir/datamanager.cpp.o" \
"CMakeFiles/watertool.dir/mainwindow.cpp.o" \
"CMakeFiles/watertool.dir/overviewpage.cpp.o" \
"CMakeFiles/watertool.dir/enviwindow.cpp.o" \
"CMakeFiles/watertool.dir/dashboard.cpp.o" \
"CMakeFiles/watertool.dir/compliance_dashboard.cpp.o" \
"CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o" \
"CMakeFiles/watertool.dir/pop.cpp.o" \
"CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o"

# External object files for target watertool
watertool_EXTERNAL_OBJECTS =

watertool: CMakeFiles/watertool.dir/watertool_autogen/mocs_compilation.cpp.o
watertool: CMakeFiles/watertool.dir/main.cpp.o
watertool: CMakeFiles/watertool.dir/datamanager.cpp.o
watertool: CMakeFiles/watertool.dir/mainwindow.cpp.o
watertool: CMakeFiles/watertool.dir/overviewpage.cpp.o
watertool: CMakeFiles/watertool.dir/enviwindow.cpp.o
watertool: CMakeFiles/watertool.dir/dashboard.cpp.o
watertool: CMakeFiles/watertool.dir/compliance_dashboard.cpp.o
watertool: CMakeFiles/watertool.dir/fluorinatedcompounds.cpp.o
watertool: CMakeFiles/watertool.dir/pop.cpp.o
watertool: CMakeFiles/watertool.dir/build/.rcc/qrc_watertool_translations.cpp.o
watertool: CMakeFiles/watertool.dir/build.make
watertool: /usr/lib64/libQt6Charts.so.6.6.2
watertool: /usr/lib64/libQt6OpenGLWidgets.so.6.6.2
watertool: /usr/lib64/libQt6Widgets.so.6.6.2
watertool: /usr/lib64/libQt6OpenGL.so.6.6.2
watertool: /usr/lib64/libQt6Gui.so.6.6.2
watertool: /usr/lib64/libQt6Core.so.6.6.2
watertool: /usr/lib64/libGLX.so
watertool: /usr/lib64/libOpenGL.so
watertool: CMakeFiles/watertool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable watertool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/watertool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/watertool.dir/build: watertool
.PHONY : CMakeFiles/watertool.dir/build

CMakeFiles/watertool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/watertool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/watertool.dir/clean

CMakeFiles/watertool.dir/depend: .rcc/qrc_watertool_translations.cpp
	cd "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring" "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring" "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build" "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build" "/uolstore/home/users/sc23a2a/Downloads/Group-Project-main (1)/Water Quality Monitoring/build/CMakeFiles/watertool.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/watertool.dir/depend

