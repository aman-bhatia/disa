# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = "/home/abhatia/Qt Projects/EasyDraw/database-src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/abhatia/Qt Projects/EasyDraw/database-src"

# Include any dependencies generated for this target.
include CMakeFiles/db.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/db.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/db.dir/flags.make

CMakeFiles/db.dir/dbcreate.cpp.o: CMakeFiles/db.dir/flags.make
CMakeFiles/db.dir/dbcreate.cpp.o: dbcreate.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/abhatia/Qt Projects/EasyDraw/database-src/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/db.dir/dbcreate.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/db.dir/dbcreate.cpp.o -c "/home/abhatia/Qt Projects/EasyDraw/database-src/dbcreate.cpp"

CMakeFiles/db.dir/dbcreate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/db.dir/dbcreate.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/abhatia/Qt Projects/EasyDraw/database-src/dbcreate.cpp" > CMakeFiles/db.dir/dbcreate.cpp.i

CMakeFiles/db.dir/dbcreate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/db.dir/dbcreate.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/abhatia/Qt Projects/EasyDraw/database-src/dbcreate.cpp" -o CMakeFiles/db.dir/dbcreate.cpp.s

CMakeFiles/db.dir/dbcreate.cpp.o.requires:
.PHONY : CMakeFiles/db.dir/dbcreate.cpp.o.requires

CMakeFiles/db.dir/dbcreate.cpp.o.provides: CMakeFiles/db.dir/dbcreate.cpp.o.requires
	$(MAKE) -f CMakeFiles/db.dir/build.make CMakeFiles/db.dir/dbcreate.cpp.o.provides.build
.PHONY : CMakeFiles/db.dir/dbcreate.cpp.o.provides

CMakeFiles/db.dir/dbcreate.cpp.o.provides.build: CMakeFiles/db.dir/dbcreate.cpp.o

# Object files for target db
db_OBJECTS = \
"CMakeFiles/db.dir/dbcreate.cpp.o"

# External object files for target db
db_EXTERNAL_OBJECTS =

db: CMakeFiles/db.dir/dbcreate.cpp.o
db: CMakeFiles/db.dir/build.make
db: /usr/local/lib/libopencv_xphoto.so.3.0.0
db: /usr/local/lib/libopencv_xobjdetect.so.3.0.0
db: /usr/local/lib/libopencv_ximgproc.so.3.0.0
db: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
db: /usr/local/lib/libopencv_tracking.so.3.0.0
db: /usr/local/lib/libopencv_text.so.3.0.0
db: /usr/local/lib/libopencv_surface_matching.so.3.0.0
db: /usr/local/lib/libopencv_stereo.so.3.0.0
db: /usr/local/lib/libopencv_saliency.so.3.0.0
db: /usr/local/lib/libopencv_rgbd.so.3.0.0
db: /usr/local/lib/libopencv_reg.so.3.0.0
db: /usr/local/lib/libopencv_optflow.so.3.0.0
db: /usr/local/lib/libopencv_line_descriptor.so.3.0.0
db: /usr/local/lib/libopencv_latentsvm.so.3.0.0
db: /usr/local/lib/libopencv_face.so.3.0.0
db: /usr/local/lib/libopencv_datasets.so.3.0.0
db: /usr/local/lib/libopencv_cvv.so.3.0.0
db: /usr/local/lib/libopencv_ccalib.so.3.0.0
db: /usr/local/lib/libopencv_bioinspired.so.3.0.0
db: /usr/local/lib/libopencv_bgsegm.so.3.0.0
db: /usr/local/lib/libopencv_adas.so.3.0.0
db: /usr/local/lib/libopencv_videostab.so.3.0.0
db: /usr/local/lib/libopencv_videoio.so.3.0.0
db: /usr/local/lib/libopencv_video.so.3.0.0
db: /usr/local/lib/libopencv_superres.so.3.0.0
db: /usr/local/lib/libopencv_stitching.so.3.0.0
db: /usr/local/lib/libopencv_shape.so.3.0.0
db: /usr/local/lib/libopencv_photo.so.3.0.0
db: /usr/local/lib/libopencv_objdetect.so.3.0.0
db: /usr/local/lib/libopencv_ml.so.3.0.0
db: /usr/local/lib/libopencv_imgproc.so.3.0.0
db: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
db: /usr/local/lib/libopencv_highgui.so.3.0.0
db: /usr/local/lib/libopencv_hal.a
db: /usr/local/lib/libopencv_flann.so.3.0.0
db: /usr/local/lib/libopencv_features2d.so.3.0.0
db: /usr/local/lib/libopencv_core.so.3.0.0
db: /usr/local/lib/libopencv_calib3d.so.3.0.0
db: /usr/local/lib/libopencv_text.so.3.0.0
db: /usr/local/lib/libopencv_face.so.3.0.0
db: /usr/local/lib/libopencv_xobjdetect.so.3.0.0
db: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
db: /usr/local/lib/libopencv_shape.so.3.0.0
db: /usr/local/lib/libopencv_video.so.3.0.0
db: /usr/local/lib/libopencv_calib3d.so.3.0.0
db: /usr/local/lib/libopencv_features2d.so.3.0.0
db: /usr/local/lib/libopencv_ml.so.3.0.0
db: /usr/local/lib/libopencv_highgui.so.3.0.0
db: /usr/local/lib/libopencv_videoio.so.3.0.0
db: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
db: /usr/local/lib/libopencv_imgproc.so.3.0.0
db: /usr/local/lib/libopencv_flann.so.3.0.0
db: /usr/local/lib/libopencv_core.so.3.0.0
db: /usr/local/lib/libopencv_hal.a
db: /usr/lib/x86_64-linux-gnu/libGLU.so
db: /usr/lib/x86_64-linux-gnu/libGL.so
db: /usr/lib/x86_64-linux-gnu/libSM.so
db: /usr/lib/x86_64-linux-gnu/libICE.so
db: /usr/lib/x86_64-linux-gnu/libX11.so
db: /usr/lib/x86_64-linux-gnu/libXext.so
db: CMakeFiles/db.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable db"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/db.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/db.dir/build: db
.PHONY : CMakeFiles/db.dir/build

CMakeFiles/db.dir/requires: CMakeFiles/db.dir/dbcreate.cpp.o.requires
.PHONY : CMakeFiles/db.dir/requires

CMakeFiles/db.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/db.dir/cmake_clean.cmake
.PHONY : CMakeFiles/db.dir/clean

CMakeFiles/db.dir/depend:
	cd "/home/abhatia/Qt Projects/EasyDraw/database-src" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/abhatia/Qt Projects/EasyDraw/database-src" "/home/abhatia/Qt Projects/EasyDraw/database-src" "/home/abhatia/Qt Projects/EasyDraw/database-src" "/home/abhatia/Qt Projects/EasyDraw/database-src" "/home/abhatia/Qt Projects/EasyDraw/database-src/CMakeFiles/db.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/db.dir/depend

