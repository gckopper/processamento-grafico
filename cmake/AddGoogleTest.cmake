if(NOT EXISTS "${PROJECT_SOURCE_DIR}/../extern/googletest/CMakeLists.txt")
    message(FATAL_ERROR "Google tests not found! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/../extern/googletest ${PROJECT_SOURCE_DIR}/../extern/googletest/build)
