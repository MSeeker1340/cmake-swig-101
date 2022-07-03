cmake_minimum_required(VERSION 3.8.0)
project(lua-binding-test VERSION 0.1.0)

# set up swig lua
cmake_policy(SET CMP0078 NEW) # to surpress swig warnings
cmake_policy(SET CMP0086 NEW) # to surpress swig warnings
find_package(SWIG REQUIRED COMPONENTS lua)
include(${SWIG_USE_FILE})

include(${CMAKE_SOURCE_DIR}/cpp/mylib.cmake)
message(STATUS "CPP_SOURCES = ${CPP_SOURCES}")

swig_add_library(mylibLua
                 TYPE STATIC
                 LANGUAGE lua
                 SOURCES ${SWIG_WRAPPER})

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
    ${CPP_SOURCES})

target_link_libraries(${PROJECT_NAME}
    mylibLua lua)
