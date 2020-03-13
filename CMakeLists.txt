cmake_minimum_required(VERSION 3.10)

project(tbb_test CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(TBB REQUIRED)

add_executable(simple_vector simple_vector.cpp)
add_executable(parallelize_levels parallelize_levels.cpp)
add_executable(2d_iteration 2d_iteration.cpp)

target_link_libraries(simple_vector PRIVATE TBB::tbb)
target_link_libraries(parallelize_levels PRIVATE TBB::tbb)
target_link_libraries(2d_iteration PRIVATE TBB::tbb)

add_custom_target(checks COMMAND ${CMAKE_CURRENT_BINARY_DIR}/simple_vector)
add_custom_target(checkp COMMAND ${CMAKE_CURRENT_BINARY_DIR}/parallelize_levels)
add_custom_target(check2d COMMAND ${CMAKE_CURRENT_BINARY_DIR}/2d_iteration)
