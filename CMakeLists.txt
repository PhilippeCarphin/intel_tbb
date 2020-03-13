cmake_minimum_required(VERSION 3.10)

project(tbb_test CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(TBB REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE TBB::tbb)
