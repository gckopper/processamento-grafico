if(NOT EXISTS "${PROJECT_SOURCE_DIR}/../extern/glfw/CMakeLists.txt")
    message(FATAL_ERROR "GLFW not found! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/../extern/glfw ${PROJECT_SOURCE_DIR}/../extern/glfw/build)
