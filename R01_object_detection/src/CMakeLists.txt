cmake_minimum_required(VERSION 3.10)
project(object_detection_cpp)

set(CMAKE_CXX_STANDARD 17)

set(TVM_ROOT $ENV{TVM_HOME})
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)
set(EXE_NAME object_detection)

file(GLOB SOURCE *.cpp *.h)
if(V2H STREQUAL "ON")
    list(REMOVE_ITEM SOURCE ${CMAKE_SOURCE_DIR}/PreRuntime.cpp)
    add_definitions(-DV2H)
    message("-- PRODUCT [V2H]") 
else()
    list(REMOVE_ITEM SOURCE ${CMAKE_SOURCE_DIR}/PreRuntimeV2H.cpp)
    add_definitions(-DV2L)
    message("-- PRODUCT [V2L]")
endif()

add_executable (${EXE_NAME}
${SOURCE}
)
TARGET_LINK_LIBRARIES(${EXE_NAME} pthread)
TARGET_LINK_LIBRARIES(${EXE_NAME} jpeg)
TARGET_LINK_LIBRARIES(${EXE_NAME} wayland-client wayland-cursor wayland-egl)
target_link_libraries(${EXE_NAME} 
        opencv_imgcodecs opencv_imgproc opencv_core opencv_highgui
        EGL GLESv2 )
target_link_libraries(${EXE_NAME} mmngr mmngrbuf)
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${EXE_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
endif()
target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})
if(V2H STREQUAL "ON")
    target_compile_definitions(${EXE_NAME} PRIVATE V2H)
endif()