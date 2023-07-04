cmake_minimum_required(VERSION 3.12)
project(expiry_date_extraction)


# Setting and including TVM Directory
set(TVM_ROOT $ENV{TVM_HOME})
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)


set(IMG_EXE_NAME "date_extraction_img")
set(CAM_EXE_NAME "date_extraction_cam")

# set common files sources
file(GLOB COMM_SRC ./common/*.cpp ./common/*.h ./common/*/*.cpp ./common/*/*.h)

# set image file source
file(GLOB IMG_SRC image_mode/*.cpp image_mode/*.h image_mode/*/*.cpp image_mode/*/*.h)
add_executable (${IMG_EXE_NAME}
    ${IMG_SRC}
    ${COMM_SRC}
)

# set camera files source
file(GLOB CAM_SRC camera_mode/*.cpp camera_mode/*.h)
add_executable (${CAM_EXE_NAME}
    ${CAM_SRC}
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

target_link_libraries(${IMG_EXE_NAME} ${OpenCV_LIBS} ${TESSERACT_LIBRARY})
target_link_libraries(${CAM_EXE_NAME} ${OpenCV_LIBS} ${TESSERACT_LIBRARY})

TARGET_LINK_LIBRARIES(${CAM_EXE_NAME} pthread)
TARGET_LINK_LIBRARIES(${CAM_EXE_NAME} jpeg)
TARGET_LINK_LIBRARIES(${CAM_EXE_NAME} wayland-client)

target_link_libraries(${IMG_EXE_NAME} ${TVM_RUNTIME_LIB})
target_link_libraries(${CAM_EXE_NAME} ${TVM_RUNTIME_LIB})

target_compile_definitions(${IMG_EXE_NAME} PRIVATE -DIMAGE_MODE)
target_compile_definitions(${CAM_EXE_NAME} PRIVATE -DCAMERA_MODE)