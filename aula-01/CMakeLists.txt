cmake_minimum_required(VERSION 3.25)
project(aula-01)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

option(CROSS_COMPILE "Cross compile to Windows" OFF)
if(CROSS_COMPILE)
    include(CrossCompile)
endif()
include(SetDefaultBuild)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
    enable_testing()
    include(AddGoogleTest)
    add_subdirectory(tests)
endif()

include(AddGlad)
include(AddGLFW)

add_subdirectory("src")
