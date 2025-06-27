cmake_minimum_required(VERSION 3.12)
project(face_recognition)

set(CMAKE_CXX_STANDARD 17)

set(TVM_ROOT $ENV{TVM_HOME})
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${TVM_ROOT}/include)
include_directories(${TVM_ROOT}/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/3rdparty/compiler-rt)

set(TVM_RUNTIME_LIB ${TVM_ROOT}/build_runtime/libtvm_runtime.so)
set(EXE_NAME face_recognition)
set(PRODUCT $ENV{PRODUCT})

if(PRODUCT STREQUAL "V2H")
    include_directories(${CMAKE_SOURCE_DIR}/drp-ai_tvm_v230)
    file(GLOB SOURCE *.cpp *.h ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v230/*.cpp ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v230/*.h)
    add_definitions(-DV2H)
    message("-- PRODUCT [V2H]") 
elseif(PRODUCT STREQUAL "V2N")
    include_directories(${CMAKE_SOURCE_DIR}/drp-ai_tvm_v251)
    file(GLOB SOURCE *.cpp *.h ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v251/*.cpp ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v251/*.h)
    add_definitions(-DV2H -DV2N)
    message("-- PRODUCT [V2N]")
else()
    include_directories(${CMAKE_SOURCE_DIR}/drp-ai_tvm_v230)
    file(GLOB SOURCE *.cpp *.h ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v230/*.cpp ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v230/*.h)
    add_definitions(-DV2L)
    message("-- PRODUCT [V2L]")
endif()

add_executable (${EXE_NAME}
${SOURCE}
)

target_include_directories(${EXE_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})

if(PRODUCT STREQUAL "V2H")
    target_compile_definitions(${EXE_NAME} PRIVATE V2H)
endif()
if(PRODUCT STREQUAL "V2N")
    target_compile_definitions(${EXE_NAME} PRIVATE V2N)
endif()