cmake_minimum_required(VERSION 3.24)
project(test_convert_JSON)

set(CMAKE_CXX_STANDARD 20)

set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set (MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MY_SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)

add_executable(${PROJECT_NAME} test_convert_JSON.cpp ${MY_SOURCE_DIR}/converter_JSON.cpp ${MY_SOURCE_INCLUDE_DIR}/converter_JSON.h)

include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR} ${MY_SOURCE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})