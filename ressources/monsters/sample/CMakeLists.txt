cmake_minimum_required(VERSION 3.12)
project(sample_monster)

set(SRCS_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/../src)


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/../include)
file(GLOB_RECURSE SOURCES ${SRCS_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp)
# Create shared library
add_library(sample_monster SHARED ${SOURCES})