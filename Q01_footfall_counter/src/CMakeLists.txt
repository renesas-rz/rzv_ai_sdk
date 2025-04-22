cmake_minimum_required(VERSION 3.10)
project(object_tracker_cpp)

set(CMAKE_CXX_STANDARD 17)

if(V2H STREQUAL "ON") 
	add_definitions(-DV2H)
	message("-- PRODUCT [V2H]")	
else()
	add_definitions(-DV2L)
	message("-- PRODUCT [V2L]")
endif()

set(TVM_ROOT $ENV{TVM_HOME})
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)
set(EXE_NAME object_tracker)

file(GLOB SOURCE *.cpp *.h)
add_executable (${EXE_NAME}
${SOURCE}
)
TARGET_LINK_LIBRARIES(${EXE_NAME} 
	pthread glib-2.0 mmngr gobject-2.0 gstreamer-1.0  gstbase-1.0 gstapp-1.0 
	opencv_imgcodecs opencv_imgproc opencv_core opencv_highgui
	jpeg webp tiff z tbb gtk-3 png16 gdk-3 cairo
	lzma rt cairo-gobject
	xkbcommon wayland-cursor wayland-egl wayland-client epoxy
	fribidi harfbuzz fontconfig
	glib-2.0 gobject-2.0 gdk_pixbuf-2.0 gmodule-2.0 pangocairo-1.0
	atk-1.0 gio-2.0 pango-1.0 freetype pixman-1 uuid pcre
	mount resolv expat pangoft2-1.0 blkid
	EGL GLESv2 mmngrbuf)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${EXE_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
endif()
target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})
