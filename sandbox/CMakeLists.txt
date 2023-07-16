cmake_minimum_required(VERSION 3.14)
project(my_project)

set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/Dependencies)

# Add the subdirectories containing the Google Test and Google Mock libraries
add_subdirectory(${DEPENDENCIES_DIR}/googletest)
add_subdirectory(${DEPENDENCIES_DIR}/googlemock)

add_executable(gmock_tutorial_example gmock_tutorial_example.cpp)
target_link_libraries(gmock_tutorial_example gtest gmock)