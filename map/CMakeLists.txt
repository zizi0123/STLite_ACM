#
#cmake_minimum_required(VERSION 3.22)
#project(map)
#
#set(CMAKE_CXX_STANDARD 14)
#
#include_directories(data)
#include_directories(src)
#
#add_executable(map
#        data/two/code.cpp)







cmake_minimum_required(VERSION 3.11)
project(map)

set(CMAKE_CXX_FLAGS "-g -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/data)
# Testing
enable_testing()
set(files_prefix "${CMAKE_CURRENT_SOURCE_DIR}/data")
file(GLOB_RECURSE CPPs "${files_prefix}/**.cpp")

string(REGEX REPLACE "^/([a-zA-Z]*/)*" "" cata "${CMAKE_CURRENT_SOURCE_DIR}")

foreach (cpp_file ${CPPs})
string(REGEX REPLACE "/[a-zA-Z]*\\.cpp" "" fpath ${cpp_file})
string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/data/" "" testname "${fpath}")
set(testname "map.${testname}")
add_executable(${testname} ${cpp_file})
add_test(NAME ${testname}
        COMMAND bash -c "$<TARGET_FILE:${testname}> | diff -Zb ${fpath}/answer.txt -")
set_property(TEST ${testname} PROPERTY TIMEOUT 180)
endforeach ()