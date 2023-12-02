cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(expiry_date_extraction)

# Setting and including TVM Directory
set(TVM_ROOT $ENV{TVM_HOME})
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)
set(EXE_NAME "date_extraction")

# set common files sources
file(GLOB COMM_SRC ./common/*.cpp ./common/*.h ./common/*/*.cpp ./common/*/*.h)

# set image file source
file(GLOB DEF_SRC date_extraction.cpp image_processing.cpp utils.cpp)
add_executable (${EXE_NAME}
    ${DEF_SRC}
    ${COMM_SRC}
)

# find tesseract library and include dir 
find_library(TESSERACT_LIBRARY NAMES tesseract HINTS "${CMAKE_SYSROOT}/usr/lib64/") # require toolchain for the variable
find_path(TESSERACT_INCLUDE_DIR NAMES tesseract/baseapi.h HINTS "${CMAKE_SYSROOT}/usr/include/tesseract")
include_directories(${TESSERACT_INCLUDE_DIR})

# Add the Boost include directory & find Boost package
include_directories(boost)
include_directories(include) 

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

target_link_libraries(${EXE_NAME} ${OpenCV_LIBS} ${TESSERACT_LIBRARY})

TARGET_LINK_LIBRARIES(${EXE_NAME} pthread)
target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})
target_compile_definitions(${EXE_NAME} PRIVATE -DIMAGE_MODE)
