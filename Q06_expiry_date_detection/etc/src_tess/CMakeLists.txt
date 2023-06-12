cmake_minimum_required(VERSION 3.12)
project(Text_Extraction)

set(TVM_ROOT $ENV{TVM_HOME})
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)


# name of executable
set(EXE_NAME text_extract)
# find all cpp files to be added as executables
file(GLOB SOURCE *.cpp *.h */*.cpp */*.h  */*/*.cpp */*/*.h)
add_executable (${EXE_NAME}
${SOURCE}
)

# find tesseract library and include dir
# find_library(TESSERACT_LIBRARY NAMES tesseract HINTS "/usr/lib/x86_64-linux-gnu")
# find_path(TESSERACT_INCLUDE_DIR NAMES tesseract/baseapi.h HINTS "/usr/include/tesseract")
# include_directories(${TESSERACT_INCLUDE_DIR})

# find tesseract library and include dir 
find_library(TESSERACT_LIBRARY NAMES tesseract HINTS "${CMAKE_SYSROOT}/usr/lib64/") # require toolchain for the variable
find_path(TESSERACT_INCLUDE_DIR NAMES tesseract/baseapi.h HINTS "${CMAKE_SYSROOT}/usr/include/tesseract")
include_directories(${TESSERACT_INCLUDE_DIR})


target_link_libraries(${EXE_NAME} ${TESSERACT_LIBRARY})

# find leptonica library and include dir
# find_library(LEPTONICA_LIBRARY NAMES lept HINTS "/usr/lib/x86_64-linux-gnu")
# find_path(LEPTONICA_INCLUDE_DIR NAMES leptonica/allheaders.h HINTS "/usr/include/leptonica")
# include_directories(${LEPTONICA_INCLUDE_DIR})

# find opencv lib and include dir
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the Boost include directory & find Boost package
include_directories(boost)
include_directories(include)

target_link_libraries(${EXE_NAME} ${OpenCV_LIBRARIES} ${TESSERACT_LIBRARY})

target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})
