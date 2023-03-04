cmake_minimum_required(VERSION 3.24)
project(test_inverted_index)


add_executable(${PROJECT_NAME} test_inverted_index.cpp)
set(CMAKE_CXX_STANDARD 20)

set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source_files)
set (MY_CLASS_DIR ${CMAKE_SOURCE_DIR}/class_files)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_CLASS_DIR} ${MY_SOURCE_DIR})

enable_testing()

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

