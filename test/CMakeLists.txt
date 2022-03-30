find_package(GTest REQUIRED)
add_executable(test_tabla test.cpp)
target_link_libraries(test_tabla tabla GTest::gtest GTest::gtest_main)
