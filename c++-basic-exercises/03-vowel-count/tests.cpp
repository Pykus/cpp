#include "solutions.hpp"

#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

namespace {
int assertions = 0;

void check(std::string_view text, std::size_t expected) {
    const auto simple = exercise03::count_vowels_simple(text);
    const auto professional = exercise03::count_vowels(text);
    ++assertions;
    if (simple != expected || professional != expected) {
        std::cerr << "Vowel-count mismatch: expected " << expected
                  << ", simple=" << simple << ", professional=" << professional << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

int main() {
    constexpr std::array<std::pair<std::string_view, std::size_t>, 18> examples{{
        {"", 0}, {"bcdfg", 0}, {"aeiou", 5}, {"AEIOU", 5},
        {"Hello World", 3}, {"rhythm", 0}, {"A quick brown fox", 5},
        {"1234567890", 0}, {"a", 1}, {"U", 1}, {"y", 0},
        {"xyz!", 0}, {"A e I o U", 5}, {"C++20", 0},
        {"Education", 5}, {"Queue", 4}, {"facetious", 5}, {"bookkeeper", 5}
    }};
    for (const auto& [text, expected] : examples) {
        check(text, expected);
    }
    for (std::size_t size = 0; size <= 256; ++size) {
        check(std::string(size, 'a'), size);
        check(std::string(size, 'z'), 0);
    }
    std::cout << "PASS " << assertions << " cases (both solutions)\n";
}
