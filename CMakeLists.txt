cmake_minimum_required(VERSION 3.5)
project(rt_weekend)
set(CMAKE_CXX_STANDARD 11)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(rtw ${SOURCES})
target_include_directories(rtw
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/geometry
        ${PROJECT_SOURCE_DIR}/include/material
        ${PROJECT_SOURCE_DIR}/include/camera
        ${PROJECT_SOURCE_DIR}/include/ray
        ${PROJECT_SOURCE_DIR}/include/vector
)
