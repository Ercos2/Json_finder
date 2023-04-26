cmake_minimum_required(VERSION 3.24)
project(endgame)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set (MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set (MY_SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)

add_subdirectory(nlohmann_json)
add_subdirectory(tests)

add_executable(endgame main.cpp
        ${MY_INCLUDE_DIR}/projects_source.h
        ${MY_INCLUDE_DIR}/exception_source.h
        ${MY_SOURCE_DIR}/converter_JSON.cpp
        ${MY_SOURCE_DIR}/inverted_index.cpp
        ${MY_SOURCE_DIR}/search_server.cpp
        ${MY_SOURCE_INCLUDE_DIR}/converter_JSON.h
        ${MY_SOURCE_INCLUDE_DIR}/inverted_index.h
        ${MY_SOURCE_INCLUDE_DIR}/search_server.h)

target_include_directories(endgame PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR} ${MY_SOURCE_INCLUDE_DIR})
target_link_libraries(endgame PRIVATE nlohmann_json::nlohmann_json)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${MY_INCLUDE_DIR}/")
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()