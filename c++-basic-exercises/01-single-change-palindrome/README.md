# Exercise 01 — Single-Change Palindrome

## Problem

Given a string, determine whether **changing exactly one character** can make it a palindrome. A change must replace the character with a different character; doing nothing does not count.

Examples:

| Input | Result | Reason |
| --- | --- | --- |
| `"ab"` | `true` | Change one of the characters to match the other. |
| `"abba"` | `false` | It is already a palindrome of even length; one edit breaks symmetry. |
| `"abcba"` | `true` | The central character can be changed. |
| `"abca"` | `true` | Only one mirrored pair differs. |
| `"abcd"` | `false` | Two mirrored pairs differ. |
| `""` | `false` | There is no character to change. |

## Solutions

Both implementations are in [solutions.hpp](solutions.hpp).

- **simple** — clear baseline that counts all mismatched mirrored pairs.
- **optimized** — early exit when more than one mirrored pair differs; uses `std::string_view`, `[[nodiscard]]` and `noexcept`.

A string is solvable precisely when it has **one mismatched mirrored pair**, or when it is **already a palindrome of odd length** (the center may be changed).

Both solutions require **O(n) time** in the worst case and **O(1) extra memory**. The optimized variant can return sooner for inputs with multiple mismatches. Neither variant allocates memory. No speedup is asserted without benchmarking.

`std::string_view` borrows characters; the caller must keep the underlying storage alive for the duration of the call.

## Build and test

Requires a C++20 compiler, CMake 3.20+ and network access on the first configure to fetch Google Test 1.16.0.

```sh
cmake -S c++-basic-exercises/01-single-change-palindrome -B build/single-change-palindrome
cmake --build build/single-change-palindrome
ctest --test-dir build/single-change-palindrome --output-on-failure
```

Tests include representative edge cases and systematic checks across short strings.
