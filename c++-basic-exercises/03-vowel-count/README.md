# Exercise 03 — Count ASCII vowels

**Goal:** Practice iteration, pure helper functions, string views, and C++20 ranges.

## Problem and sample I/O

Given a character sequence, count English vowels (a, e, i, o, u), ignoring
letter case. Every other character counts as zero; y is not a vowel.

| Input | Output |
| --- | --- |
| Hello World | 3 |
| rhythm | 0 |
| aeiou | 5 |

This is intentionally an ASCII exercise. Accented letters and general Unicode
code points are outside its byte-based contract.

## Quick implementation

`count_vowels_simple` loops over every character and searches for it in the
ten-letter constant `aeiouAEIOU`. Every hit increments a counter.
The lookup string has fixed length, so total work grows linearly with input.

## Production-style C++20 implementation

The `constexpr` helper `is_ascii_vowel` uses an explicit switch to express the
classification rule. The main function uses `std::ranges::count_if`, which
communicates the intent without manual loop bookkeeping.

Important choices:

1. `std::string_view` avoids copying input; the caller must keep its source alive.
2. `[[nodiscard]]` warns if a caller discards the answer.
3. `noexcept` is appropriate here because these operations cannot throw.
4. `constexpr` permits the helper to be evaluated at compile time.
5. Converting the algorithm's result to `std::size_t` makes the API type explicit.

Both solutions take **O(n)** time and **O(1)** auxiliary space. The switch
avoids a small sequential search, but real speedups require measurement.
Neither implementation allocates or needs multithreading.

## Common mistakes and edge cases

Count both cases; do not count `y`; do not allocate a temporary lowercase
string; do not confuse UTF-8 bytes with Unicode characters. Empty input returns
zero. The public functions only borrow text while they execute.

## Build and run

CMake (3.20+), with a C++20 compiler:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Or with GCC alone:

```sh
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tests.cpp -o vowel_tests
./vowel_tests
```

## Follow-up exercise

Return five separate counters (a, e, i, o, u) in one traversal, without
copying the input. Test mixed case, empty strings, and long strings.
