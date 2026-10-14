#include "solutions.hpp"

#include <gtest/gtest.h>

#include <string>
#include <string_view>

namespace exercise = cpp_basic_exercises::single_change_palindrome;

struct Example {
    std::string_view input;
    bool expected;
};

TEST(SingleChangePalindrome, RepresentativeCases) {
    constexpr Example examples[]{
        {"", false},
        {"a", true},
        {"aa", false},
        {"ab", true},
        {"abba", false},
        {"aba", true},
        {"abcba", true},
        {"abcd", false},
        {"abca", true},
        {"aabx", false},
        {"aabb", false},
        {"aaaaa", true},
        {"aaaa", false},
        {"abcda", true},
        {"abcca", true},
    };

    for (const auto& [input, expected] : examples) {
        SCOPED_TRACE(input);
        EXPECT_EQ(exercise::simple(input), expected);
        EXPECT_EQ(exercise::optimized(input), expected);
    }
}

TEST(SingleChangePalindrome, BothVersionsAgreeForAllShortTernaryStrings) {
    for (int length = 0; length <= 8; ++length) {
        int count = 1;
        for (int i = 0; i < length; ++i) {
            count *= 3;
        }

        for (int encoded = 0; encoded < count; ++encoded) {
            std::string text(static_cast<std::size_t>(length), 'a');
            int remaining = encoded;
            for (char& ch : text) {
                ch = static_cast<char>('a' + remaining % 3);
                remaining /= 3;
            }
            SCOPED_TRACE(text);
            EXPECT_EQ(exercise::simple(text), exercise::optimized(text));
        }
    }
}
