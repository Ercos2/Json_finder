cmake_minimum_required(VERSION 3.24)
project(endgame)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(endgame main.cpp converter_JSON.h projects_source.h inverted_index.h search_server.h exception_source.h)

target_link_libraries(endgame PRIVATE nlohmann_json::nlohmann_json)

include(FetchContent)
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

target_link_libraries(endgame PRIVATE gtest_main)


include(GoogleTest)
gtest_discover_tests(endgame)
