cmake_minimum_required(VERSION 3.20)
project(single_change_palindrome LANGUAGES CXX)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(single_change_palindrome_tests tests.cpp)
    target_compile_features(single_change_palindrome_tests PRIVATE cxx_std_20)
    target_link_libraries(single_change_palindrome_tests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(single_change_palindrome_tests)
endif()
