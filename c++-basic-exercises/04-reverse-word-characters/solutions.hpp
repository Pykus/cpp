#pragma once

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

namespace exercise04 {

// Baseline: two pointers swap characters inside each non-space segment.
[[nodiscard]] inline std::string reverse_words_simple(std::string_view text) {
    std::string result{text};
    std::size_t start = 0;
    while (start < result.size()) {
        if (result[start] == ' ') {
            ++start;
            continue;
        }
        std::size_t end = start;
        while (end < result.size() && result[end] != ' ') ++end;
        std::size_t left = start;
        std::size_t right = end;
        while (left < right) {
            --right;
            if (left >= right) break;
            std::swap(result[left], result[right]);
            ++left;
        }
        start = end;
    }
    return result;
}

// Modern algorithm: a C++20 ranges operation expresses the reversal intent.
[[nodiscard]] inline std::string reverse_words(std::string_view text) {
    std::string result{text};
    std::size_t start = 0;
    while (start < result.size()) {
        if (result[start] == ' ') {
            ++start;
            continue;
        }
        std::size_t end = start;
        while (end < result.size() && result[end] != ' ') ++end;
        std::ranges::reverse(result.begin() + static_cast<std::ptrdiff_t>(start),
                             result.begin() + static_cast<std::ptrdiff_t>(end));
        start = end;
    }
    return result;
}

}  // namespace exercise04
