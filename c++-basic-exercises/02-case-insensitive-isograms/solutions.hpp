#pragma once

#include <array>
#include <cstddef>
#include <string_view>

namespace cpp_basic_exercises::isograms {

// Only the English ASCII alphabet is accepted by this exercise.
[[nodiscard]] constexpr unsigned char ascii_lower(unsigned char ch) noexcept {
    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<unsigned char>(ch + ('a' - 'A'));
    }
    return ch;
}

// Baseline: compare each new letter with the letters already visited.
[[nodiscard]] inline bool simple(std::string_view word) noexcept {
    for (std::size_t i = 0; i < word.size(); ++i) {
        const auto current = ascii_lower(static_cast<unsigned char>(word[i]));
        if (current < 'a' || current > 'z') {
            return false;
        }

        for (std::size_t j = 0; j < i; ++j) {
            if (ascii_lower(static_cast<unsigned char>(word[j])) == current) {
                return false;
            }
        }
    }
    return true;
}

// One pass with a fixed-size lookup table; no heap allocation.
[[nodiscard]] inline bool optimized(std::string_view word) noexcept {
    std::array<bool, 26> seen{};

    for (const unsigned char original : word) {
        const auto letter = ascii_lower(original);
        if (letter < 'a' || letter > 'z') {
            return false;
        }

        const auto index = static_cast<std::size_t>(letter - 'a');
        if (seen[index]) {
            return false;
        }
        seen[index] = true;
    }
    return true;
}

} // namespace cpp_basic_exercises::isograms
