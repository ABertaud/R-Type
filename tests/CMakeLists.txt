set(INCLUDES_CLIENT_DIR ${PROJECT_SOURCE_DIR}/include/Client)
set(SRCS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/src/ClientUdp)
set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)

set(INCLUDES_SHARED_DIR ${PROJECT_SOURCE_DIR}/include/Shared)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/src/Shared)

set(INCLUDES_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/include/Server/Components)
set(SRCS_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/src/Server/Components)

set(TESTS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/tests/Client)
set(TESTS_SERVER_DIR ${PROJECT_SOURCE_DIR}/tests/Server)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SRCS_CLIENT ${SRCS_CLIENT_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp)
file(GLOB_RECURSE SRCS_SERVER ${SRCS_SERVER_DIR}/*.cpp ${SRCS_SHARED_DIR}/*.cpp ${SRCS_COMPONENTS_DIR}/*.cpp)

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
target_link_libraries(unit_tests_client criterion)
target_link_libraries(unit_tests_client ${CONAN_LIBS})          
add_test(first unit_tests_client)

add_executable(unit_tests_server ${TESTS_SERVER} ${SRCS_SERVER})
target_compile_features(unit_tests_server PRIVATE cxx_std_17)
target_compile_options(unit_tests_server
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(unit_tests_server PRIVATE ${INCLUDES_SERVER_DIR})
target_include_directories(unit_tests_server PRIVATE ${INCLUDES_SHARED_DIR})  
target_include_directories(unit_tests_server PRIVATE ${INCLUDES_COMPONENTS_DIR})
target_link_libraries(unit_tests_server criterion)
target_link_libraries(unit_tests_server ${CONAN_LIBS})          
add_test(second unit_tests_server)

                      