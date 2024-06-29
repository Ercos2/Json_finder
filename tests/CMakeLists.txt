#enable_testing()
#add_subdirectory(test_convert_JSON)
#enable_testing()
#add_subdirectory(test_inverted_index)
#enable_testing()
#add_subdirectory(test_search_server)

project(tests)

cmake_minimum_required (VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

#set (MESSAGE_DIR ${CMAKE_SOURCE_DIR}/../src/message)

#file(GLOB MESSAGE_SOURCES "${MESSAGE_DIR}/*.cpp")

#set(TEST_SOURCES
#    messagesTests.cpp
#    ittiQueueTests.cpp
#    ../src/utils.cpp 
#    ../src/ittiQueue.cpp
#    ${MESSAGE_SOURCES}
#)


set (MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set (MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set (MY_SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)

add_executable(${PROJECT_NAME} ${MY_SOURCE_DIR}/converter_JSON.cpp 
                                ${MY_SOURCE_DIR}/inverted_index.cpp 
                                ${MY_SOURCE_DIR}/search_server.cpp 
                                test_inverted_index.cpp 
                                test_search_server.cpp 
                                source_test.cpp
                                )


target_include_directories (${PROJECT_NAME} PUBLIC ${MY_SOURCE_DIR} ${MY_INCLUDE_DIR} ${MY_SOURCE_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
            googletest
            URL
            https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) 

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
FetchContent_MakeAvailable(googletest)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest gtest_main nlohmann_json::nlohmann_json)

set(gtest_disable_pthreads on)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

enable_testing()