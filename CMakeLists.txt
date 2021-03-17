cmake_minimum_required(VERSION 3.14)

# cmake --log-level
set( CMAKE_MESSAGE_LOG_LEVEL "DEBUG" )
set(CMAKE_CXX_STANDARD 17)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)

message(DEBUG " Build type : ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL Release)
    message(DEBUG " Build type : ${CMAKE_BUILD_TYPE}")

    if(DEFINED $ENV{TRAVIS_BUILD_NUMBER})
        set(PATCH_VERSION $ENV{TRAVIS_BUILD_NUMBER})
    else()
        set(PATCH_VERSION 1)
    endif()
else()
    set(PATCH_VERSION 6)

endif()

project(meta_print_ip VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})


add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
