add_executable(test_twod twod.cpp)
target_link_libraries(test_twod GTest::gtest_main twod)
gtest_discover_tests(test_twod PROPERTIES TIMEOUT 600)
