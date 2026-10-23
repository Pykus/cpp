#include "solutions.hpp"

#include <array>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <string_view>

namespace exercise = cpp_basic_exercises::isograms;

struct Example {
    std::string_view input;
    bool expected;
};

// Separate STL-based reference to compare against both lesson implementations.
[[nodiscard]] bool reference(std::string_view input) {
    std::set<unsigned char> visited;
    for (const unsigned char original : input) {
        const auto letter = exercise::ascii_lower(original);
        if (letter < 'a' || letter > 'z' || !visited.insert(letter).second) {
            return false;
        }
    }
    return true;
}

int main() {
    constexpr std::array examples{
        Example{"", true},
        Example{"a", true},
        Example{"AbC", true},
        Example{"isogram", true},
        Example{"Dermatoglyphics", true},
        Example{"abcdefghijklmnopqrstuvwxyz", true},
        Example{"aba", false},
        Example{"moOse", false},
        Example{"Aa", false},
        Example{"Alphabet", false},
        Example{"example", false},
        Example{"aBcA", false},
        Example{"a-b", false},
        Example{"a b", false},
        Example{"a1b", false},
        Example{"!a", false},
        Example{"abcdefghijklmnopqrstuvwxyza", false},
    };

    std::size_t checks = 0;
    std::size_t failures = 0;
    const auto verify = [&](std::string_view input, bool expected) {
        ++checks;
        const bool easy = exercise::simple(input);
        const bool fast = exercise::optimized(input);
        if (easy != expected || fast != expected) {
            ++failures;
            std::cerr << "Mismatch for input of length " << input.size()
                      << ": expected " << expected
                      << ", simple " << easy << ", optimized " << fast << '\n';
        }
    };

    for (const auto& [input, expected] : examples) {
        verify(input, expected);
    }
    const std::string non_ascii{"\xC3\xA9", 2};
    const std::string high_byte(1, static_cast<char>(0xFF));
    const std::string null_byte(1, '\0');
    verify(non_ascii, false);
    verify(high_byte, false);
    verify(null_byte, false);

    // Enumerate every string up to length 7 over a mixed-case alphabet and '!'.
    constexpr std::array alphabet{'a', 'B', 'c', '!'};
    for (std::size_t length = 0; length <= 7; ++length) {
        std::size_t combinations = 1;
        for (std::size_t i = 0; i < length; ++i) {
            combinations *= alphabet.size();
        }
        for (std::size_t encoded = 0; encoded < combinations; ++encoded) {
            std::string word(length, 'a');
            auto remaining = encoded;
            for (char& ch : word) {
                ch = alphabet[remaining % alphabet.size()];
                remaining /= alphabet.size();
            }
            verify(word, reference(word));
        }
    }

    if (failures != 0) {
        std::cerr << failures << " failed out of " << checks << " test cases\n";
        return 1;
    }
    std::cout << "PASS: " << checks << " test cases (both implementations)\n";
    return 0;
}
