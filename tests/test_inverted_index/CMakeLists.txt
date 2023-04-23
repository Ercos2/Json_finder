cmake_minimum_required(VERSION 3.24)
project(test_inverted_index)


add_executable(${PROJECT_NAME} test_inverted_index.cpp)
set(CMAKE_CXX_STANDARD 20)

set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set (MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MY_SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR} ${MY_SOURCE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json invert gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})







