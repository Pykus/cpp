cmake_minimum_required(VERSION 3.20)
project(case_insensitive_isograms LANGUAGES CXX)

include(CTest)

add_executable(case_insensitive_isograms_tests tests.cpp)
target_compile_features(case_insensitive_isograms_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(case_insensitive_isograms_tests PRIVATE /W4)
else()
    target_compile_options(case_insensitive_isograms_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME case_insensitive_isograms COMMAND case_insensitive_isograms_tests)
