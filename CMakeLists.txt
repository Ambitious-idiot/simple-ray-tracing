cmake_minimum_required(VERSION 3.5)
project(rt_weekend)
set(CMAKE_CXX_STANDARD 11)
aux_source_directory(src SOURCES)
add_executable(pbr ${SOURCES})
target_include_directories(pbr
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)