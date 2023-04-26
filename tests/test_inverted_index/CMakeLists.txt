cmake_minimum_required(VERSION 3.24)
project(test_inverted_index)



set(CMAKE_CXX_STANDARD 20)

set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set (MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MY_SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)

add_executable(${PROJECT_NAME} test_inverted_index.cpp ${MY_SOURCE_DIR}/inverted_index.cpp ${MY_SOURCE_INCLUDE_DIR}/inverted_index.h)
#add_executable(inverted inverted_index.cpp include/inverted_index.h)
#target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR})
#target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR} ${MY_SOURCE_INCLUDE_DIR})

#add_subdirectory(${MY_SOURCE_DIR})
include_directories(${MY_INCLUDE_DIR} ${MY_SOURCE_DIR} ${MY_SOURCE_INCLUDE_DIR})

#target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json gtest gtest_main)
#target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json invert gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})







