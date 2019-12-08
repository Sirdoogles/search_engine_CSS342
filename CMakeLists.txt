cmake_minimum_required(VERSION 3.10)
project(possible_parentheses)

set(CMAKE_CXX_STANDARD 17)
Set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
Set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/src)

Set(CMAKE_BINARY_DIR  ${CMAKE_SOURCE_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

include(googletest/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/googletest
        ${LIBRARY_OUTPUT_PATH}/googletest
)

enable_testing()

add_subdirectory(test)