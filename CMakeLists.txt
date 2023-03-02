cmake_minimum_required(VERSION 3.24)
project(endgame)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source_files)
set (MY_CLASS_DIR ${CMAKE_SOURCE_DIR}/class_files)

add_subdirectory(nlohmann_json test)

add_executable(endgame main.cpp
        ${MY_CLASS_DIR}/converter_JSON.h
        ${MY_CLASS_DIR}/inverted_index.h
        ${MY_CLASS_DIR}/search_server.h
        ${MY_SOURCE_DIR}/projects_source.h
        ${MY_SOURCE_DIR}/exception_source.h)



target_include_directories(endgame PUBLIC ${MY_CLASS_DIR} ${MY_SOURCE_DIR})
target_link_libraries(endgame PRIVATE nlohmann_json::nlohmann_json)

