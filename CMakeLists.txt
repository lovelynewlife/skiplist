cmake_minimum_required(VERSION 3.20)
project(skiplist)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("third_party/googletest")

add_executable(main main.cpp)

add_executable(skiplist_test src/skiplist_test.cpp
        src/skiplist.hpp
        src/skiplist.cpp)
target_link_libraries(skiplist_test gtest gtest_main)
add_test(NAME "skiplist_test" COMMAND "skiplist_test")

