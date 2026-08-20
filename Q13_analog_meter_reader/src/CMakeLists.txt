cmake_minimum_required(VERSION 3.10)
project(analog_meter_reader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(NOT DEFINED ENV{TVM_ROOT})
  message(SEND_ERROR "Need to specify location of drp-tvm with option TVM_ROOT")
endif()

if(NOT DEFINED ENV{PRODUCT})
  message(SEND_ERROR "Need to specify product name with option PRODUCT")
endif()

set(TVM_ROOT "$ENV{TVM_ROOT}")
include_directories(${TVM_ROOT}/tvm/include)
include_directories(${TVM_ROOT}/setup/include)
include_directories(${TVM_ROOT}/tvm/3rdparty/dlpack/include)
include_directories(${TVM_ROOT}/tvm/3rdparty/dmlc-core/include)
include_directories(${TVM_ROOT}/tvm/3rdparty/compiler-rt)

set(EXE_NAME analog_reader)
set(PRODUCT $ENV{PRODUCT})

if(PRODUCT STREQUAL "V2H")
    include_directories(${CMAKE_SOURCE_DIR}/drp-ai_tvm_v251)
    file(GLOB SOURCE *.cpp *.h ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v251/*.cpp ${CMAKE_SOURCE_DIR}/drp-ai_tvm_v251/*.h)
    add_definitions(-DV2H)
    message("-- PRODUCT [V2H]") 
elseif(PRODUCT STREQUAL "V2N")
    include_directories(${CMAKE_SOURCE_DIR}/ruhmi_2026-06)
    file(GLOB SOURCE *.cpp *.h ${CMAKE_SOURCE_DIR}/ruhmi_2026-06/*.cpp ${CMAKE_SOURCE_DIR}/ruhmi_2026-06/*.h)
    include_directories(${CMAKE_SYSROOT}/usr/src/debug/gstreamer1.0-plugins-base/1.22.12/gst-libs/gst/gl)
    list(APPEND SOURCE ${CMAKE_SYSROOT}/usr/src/debug/gstreamer1.0-plugins-base/1.22.12/gst-libs/gst/gl/xdg-shell-client-protocol.c)
    add_definitions(-DV2H -DV2N)
    add_definitions(-DMERA_DRP_RUNTIME)
    message("-- PRODUCT [V2N]")
endif()

add_executable (${EXE_NAME} ${SOURCE})

target_compile_options(${EXE_NAME} PRIVATE -O2)

target_link_libraries(${EXE_NAME} 
    wayland-client 
    wayland-cursor 
    wayland-egl
    opencv_imgcodecs 
    opencv_imgproc 
    opencv_core 
    opencv_highgui
    EGL 
    GLESv2
    pthread
    jpeg
)

target_compile_definitions(${EXE_NAME} PUBLIC KDLDRPAI)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${EXE_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
endif()


if(PRODUCT STREQUAL "V2H")
    set(TVM_RUNTIME_LIB ${TVM_ROOT}/tvm/build_runtime/libtvm_runtime.so)
    target_link_libraries(${EXE_NAME} ${TVM_RUNTIME_LIB})
    target_compile_definitions(${EXE_NAME} PRIVATE V2H)
endif()
if(PRODUCT STREQUAL "V2N")
    target_link_libraries(${EXE_NAME} 
        mera2_runtime
        mera2_plan_io
        drp_tvm_rt
    )
    set (LIBMERA_RT_PATH ${TVM_ROOT}/obj/build_runtime/v2h/lib)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBMERA_RT_PATH} -Wl,-rpath-link,${LIBMERA_RT_PATH}")
    target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(${EXE_NAME} PUBLIC ${TVM_ROOT}/3rdparty/asio/asio/include)
    target_include_directories(${EXE_NAME} PUBLIC ${TVM_ROOT}/3rdparty/spdlog/include)
    target_link_directories(${EXE_NAME} PRIVATE ${LIBMERA_RT_PATH})
    target_compile_definitions(${EXE_NAME} PRIVATE V2N)
endif()
