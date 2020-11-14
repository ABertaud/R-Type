cmake_minimum_required(VERSION 3.12)
project(spaceship_monster)

set(SRCS_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/../src)

set(INCLUDE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/../../../include/Server/Components)
set(SOURCE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/../../../src/Server/Components)

set(INCLUDE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../../../engine/include)
set(SOURCE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../../../engine/src)

set(INCLUDE_SHARED_MONSTERS_DIR ${PROJECT_SOURCE_DIR}/../../../include/Shared/Monsters)
set(SOURCE_SHARED_MONSTERS_DIR ${PROJECT_SOURCE_DIR}/../../../src/Shared/Monsters)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_SHARED_MONSTERS_DIR})
include_directories(${INCLUDE_ENGINE_DIR})
include_directories(${INCLUDE_COMPONENTS_DIR})

file(GLOB_RECURSE SOURCES ${SRCS_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp ${SOURCE_ENGINE_DIR}/*.cpp {PROJECT_SOURCE_DIR}/../../../src/Shared/Error.cpp ${SOURCE_SHARED_MONSTERS_DIR}/*.cpp ${SOURCE_COMPONENTS_DIR}/*.cpp)
# Create shared library
add_library(spaceship_monster SHARED ${SOURCES})