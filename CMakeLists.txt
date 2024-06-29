cmake_minimum_required(VERSION 3.24)
project(Json_finder)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set (MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set (MY_SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)

add_subdirectory(nlohmann_json)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp
        ${MY_INCLUDE_DIR}/projects_source.h
        ${MY_INCLUDE_DIR}/exception_source.h
        ${MY_SOURCE_DIR}/converter_JSON.cpp
        ${MY_SOURCE_DIR}/inverted_index.cpp
        ${MY_SOURCE_DIR}/search_server.cpp
        ${MY_SOURCE_INCLUDE_DIR}/converter_JSON.h
        ${MY_SOURCE_INCLUDE_DIR}/inverted_index.h
        ${MY_SOURCE_INCLUDE_DIR}/search_server.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR} ${MY_SOURCE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

enable_testing()