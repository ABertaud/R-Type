cmake_minimum_required(VERSION 3.12)
project(r-type)

set(INCLUDES_SHARED_DIR ${PROJECT_SOURCE_DIR}/include/Shared)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/src/Shared)

set(INCLUDES_CLIENT_DIR ${PROJECT_SOURCE_DIR}/include/Client)
set(SRCS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/src/Client)

set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)

set(INCLUDES_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/include/Server/Components)
set(SRCS_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/src/Server/Components)
#SFML
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Threads)
#SFML
#find_package(SFML 2.5.1 REQUIRED system window graphics audio)

file(GLOB_RECURSE SRCS_SERVER ${SRCS_SERVER_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp ${SRCS_COMPONENTS_DIR}/*.cpp)
file(GLOB_RECURSE SRCS_CLIENT ${SRCS_CLIENT_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp)

add_executable(r-type_server ${SRCS_SERVER})
target_compile_features(r-type_server PRIVATE cxx_std_17)
target_compile_options(r-type_server
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3 -Wno-unused-local-typedefs -g>)
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDES_SERVER_DIR})
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDES_SHARED_DIR})
target_include_directories(r-type_server PRIVATE ${INCLUDES_COMPONENTS_DIR})
target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type_server ${CMAKE_DL_LIBS})
target_link_libraries(r-type_server ${CMAKE_THREAD_LIBS_INIT})

add_executable(r-type_client ${SRCS_CLIENT} ${SRCS_CLIENT_UI} ${SRCS_CLIENT_QRC})
target_compile_features(r-type_client PRIVATE cxx_std_17)
target_compile_options(r-type_client
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3 -Wno-unused-local-typedefs -lpthread -lboost_system -lboost_thread >)
target_include_directories(r-type_client PRIVATE SYSTEM ${INCLUDES_CLIENT_DIR})
target_include_directories(r-type_client PRIVATE SYSTEM ${INCLUDES_SHARED_DIR})
target_link_libraries(r-type_client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(r-type_client ${CONAN_LIBS})

#NO
#target_link_libraries(r-type_client sfml-window sfml-system sfml-audio sfml-graphics)
#Sfml
#target_link_libraries(r-type_client ${SFML_LIBRARIES})
#flags -lsfml-graphics -lsfml-window -lsfml-system
include(CTest)
enable_testing(MAKE_DIRECTORY tests)
add_subdirectory(tests)
add_subdirectory(ressources/monsters/)