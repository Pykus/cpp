#include "solutions.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>

namespace {
int checks = 0;
void test(std::string_view input, std::string_view expected) {
    const auto baseline = exercise04::reverse_words_simple(input);
    const auto modern = exercise04::reverse_words(input);
    ++checks;
    if (baseline != expected || modern != expected) {
        std::cerr << "FAIL reverse_words input: " << input << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}
int main() {
    test("", "");
    test("abc", "cba");
    test("a", "a");
    test("ab cd", "ba dc");
    test("  abc  xy ", "  cba  yx ");
    test("hello world", "olleh dlrow");
    test("   ", "   ");
    test("a,b c!", "b,a !c");
    test("12 345", "21 543");
    test("  A bc D  ", "  A cb D  ");
    for (std::size_t length = 0; length <= 1000; ++length) {
        const std::string letters(length, 'a');
        test(letters, letters);
        test(std::string(" ") + letters + " ", std::string(" ") + letters + " ");
    }
    std::cout << "PASS " << checks << " input cases (two C++20 solutions)\n";
}
