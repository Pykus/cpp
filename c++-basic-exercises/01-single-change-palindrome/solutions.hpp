#pragma once

#include <cstddef>
#include <string_view>

namespace cpp_basic_exercises::single_change_palindrome {

// Straightforward baseline: inspect every mirrored pair.
[[nodiscard]] inline bool simple(std::string_view text) noexcept {
    std::size_t mismatches = 0;

    for (std::size_t i = 0; i < text.size() / 2; ++i) {
        if (text[i] != text[text.size() - 1 - i]) {
            ++mismatches;
        }
    }

    return mismatches == 1 || (mismatches == 0 && text.size() % 2 != 0);
}

// Early-exit variant: avoid scanning once two pairs disagree.
[[nodiscard]] inline bool optimized(std::string_view text) noexcept {
    std::size_t mismatches = 0;
    const std::size_t n = text.size();

    for (std::size_t i = 0; i < n / 2; ++i) {
        if (text[i] != text[n - 1 - i] && ++mismatches > 1) {
            return false;
        }
    }

    return mismatches == 1 || (n % 2 != 0);
}

} // namespace cpp_basic_exercises::single_change_palindrome
