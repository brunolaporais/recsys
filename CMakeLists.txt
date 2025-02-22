cmake_minimum_required(VERSION 2.8.4)
project(blprecsys)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")        
    SET(warnings "-Wall -Wextra -Werror")
ENDIF ()

SET(CMAKE_BUILD_TYPE Release)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "")

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(file_operation)
ADD_SUBDIRECTORY(model)
ADD_SUBDIRECTORY(recsys_methods)
ADD_SUBDIRECTORY(evaluation)
ADD_SUBDIRECTORY(util)

add_executable(recommender main.cpp)

target_link_libraries(recommender model file_operation cf cb validation)
