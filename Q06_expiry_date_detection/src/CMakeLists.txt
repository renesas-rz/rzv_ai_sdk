cmake_minimum_required(VERSION 3.12)
project(text_extraction_date_type)


# Setting and including TVM Directory
set(TVM_ROOT $ENV{TVM_HOME})
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)


# setting and adding the application 
set(EXE_NAME date_extraction)

file(GLOB SOURCE *.cpp *.h */*.cpp */*.h)
add_executable (${EXE_NAME}
${SOURCE}
)

# find tesseract library and include dir 
find_library(TESSERACT_LIBRARY NAMES tesseract HINTS "${CMAKE_SYSROOT}/usr/lib64/") # require toolchain for the variable
find_path(TESSERACT_INCLUDE_DIR NAMES tesseract/baseapi.h HINTS "${CMAKE_SYSROOT}/usr/include/tesseract")
include_directories(${TESSERACT_INCLUDE_DIR})

target_link_libraries(${EXE_NAME} ${TESSERACT_LIBRARY})

# Add the Boost include directory & find Boost package
include_directories(boost)
include_directories(include) 
include_directories(../../../../src_tess/include)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${EXE_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
endif()

TARGET_LINK_LIBRARIES(${EXE_NAME} pthread)
TARGET_LINK_LIBRARIES(${EXE_NAME} jpeg)
TARGET_LINK_LIBRARIES(${EXE_NAME} wayland-client)

target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})