#pragma once

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string_view>

namespace exercise03 {

[[nodiscard]] inline std::size_t count_vowels_simple(std::string_view text) noexcept {
    constexpr std::string_view vowels = "aeiouAEIOU";
    std::size_t result = 0;
    for (const char character : text) {
        if (vowels.find(character) != std::string_view::npos) {
            ++result;
        }
    }
    return result;
}

[[nodiscard]] constexpr bool is_ascii_vowel(char character) noexcept {
    switch (character) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return true;
        default:
            return false;
    }
}

[[nodiscard]] inline std::size_t count_vowels(std::string_view text) noexcept {
    return static_cast<std::size_t>(std::ranges::count_if(text, is_ascii_vowel));
}

}  // namespace exercise03
