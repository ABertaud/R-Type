set(INCLUDES_CLIENT_DIR ${PROJECT_SOURCE_DIR}/include/Client)
set(SRCS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/src/ClientUdp)
set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)

set(INCLUDES_SHARED_DIR ${PROJECT_SOURCE_DIR}/include/Shared)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/src/Shared)

set(INCLUDE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/engine/include/)
set(SOURCE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/engine/src/)

set(INCLUDE_SYSTEMS_DIR ${PROJECT_SOURCE_DIR}/include/Server/Systems)
set(SOURCE_SYSTEMS_DIR ${PROJECT_SOURCE_DIR}/src/Server/Systems)

set(INCLUDE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/include/Server/Components)
set(SOURCE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/src/Server/Components)

set(INCLUDES_SHARED_MONSTERS_DIR ${INCLUDES_SHARED_DIR}/Monsters)
set(SRCS_SHARED_MONSTERS_DIR ${SRCS_SHARED_DIR}/Monsters)

set(TESTS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/tests/Client)
set(TESTS_SERVER_DIR ${PROJECT_SOURCE_DIR}/tests/Server)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Threads)

file(GLOB_RECURSE SRCS_SERVER ${SRCS_SERVER_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp ${SOURCE_ENGINE_DIR}/*.cpp ${SOURCE_SYSTEMS_DIR}/*.cpp {SOURCE_COMPONENTS_DIR}/*.cpp ${SRCS_SHARED_MONSTERS_DIR}/*.cpp)
file(GLOB_RECURSE SRCS_CLIENT ${SRCS_CLIENT_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp ${SRCS_SHARED_MONSTERS_DIR}/*.cpp)

file(GLOB_RECURSE TESTS_CLIENT ${TESTS_CLIENT_DIR}/*.cpp)
file(GLOB_RECURSE TESTS_SERVER ${TESTS_SERVER_DIR}/*.cpp)

list(REMOVE_ITEM SRCS_CLIENT ${PROJECT_SOURCE_DIR}/src/Client/main.cpp)
list(REMOVE_ITEM SRCS_SERVER ${PROJECT_SOURCE_DIR}/src/Server/main.cpp)

add_executable(unit_tests_client ${TESTS_CLIENT} ${SRCS_CLIENT})
target_compile_features(unit_tests_client PRIVATE cxx_std_17)
target_compile_options(unit_tests_client
                        PRIVATE
                        $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(unit_tests_client PRIVATE ${INCLUDES_CLIENT_DIR})
target_include_directories(unit_tests_client PRIVATE ${INCLUDES_SHARED_DIR})
target_include_directories(unit_tests_client PRIVATE SYSTEM ${INCLUDES_SHARED_MONSTERS_DIR})
target_link_libraries(unit_tests_client criterion)
target_link_libraries(unit_tests_client ${CONAN_LIBS})
target_link_libraries(unit_tests_client ${CMAKE_THREAD_LIBS_INIT})
add_test(first unit_tests_client)

add_executable(unit_tests_server ${TESTS_SERVER} ${SRCS_SERVER})
target_compile_features(unit_tests_server PRIVATE cxx_std_17)
target_compile_options(unit_tests_server
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SERVER_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SHARED_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDE_COMPONENTS_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDE_SYSTEMS_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDE_ENGINE_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SHARED_MONSTERS_DIR})
target_link_libraries(unit_tests_server criterion)
target_link_libraries(unit_tests_server ${CONAN_LIBS})
target_link_libraries(unit_tests_server ${CMAKE_THREAD_LIBS_INIT})
add_test(second unit_tests_server)

                      