if(NOT EXISTS "${PROJECT_SOURCE_DIR}/../extern/googletest/CMakeLists.txt")
    find_package(Git QUIET)

    if(GIT_FOUND)
        if(EXISTS "${PROJECT_SOURCE_DIR}/../.git")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init extern/googletest
                            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/.."
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init extern/googletest failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        else()
            message(FATAL_ERROR "This is not a git repository and the extern/googletest directory does not contain a CMakeLists.txt. Since this is not a repository we can't sync the submodules. To fix this download a zip archive from the official glfw github and extract it inside the extern/googletest folder. The file extern/googletest/CMakeLists.txt should exist. Or simply turn the tests off by setting PACKAGE_TESTS=OFF")
        endif()
    else()
        message(FATAL_ERROR "Git was not found and the extern/googletest directory does not contain a CMakeLists.txt. The directory is a git submodule and the files should be downloaded with git, however, if necessary, download a zip archive from the official glfw github and extract it inside the extern/googletest folder. The file extern/googletest/CMakeLists.txt should exist. Or simply turn the tests off by setting PACKAGE_TESTS=OFF")
    endif()
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()
include(GoogleTest)

macro(package_add_test TESTNAME)
    # create an executable in which the tests will be stored
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address -g")
    add_executable(${TESTNAME} ${ARGN})
    # link the Google test infrastructure, mocking library, and a default main function to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    gtest_discover_tests(${TESTNAME}
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
