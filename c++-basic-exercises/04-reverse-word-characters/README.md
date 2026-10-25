# Exercise 04 — Reverse letters inside each word

**Learning objective:** practice scanning a string, index arithmetic,
two-pointer swaps, and the C++20 ranges algorithm library.

## The problem

Take an ASCII sentence. Reverse the characters in each contiguous sequence
of non-space characters, while leaving every ASCII space in its original
position. Only the literal space character is a separator in this exercise.

| Input | Result |
| --- | --- |
| `"hello world"` | `"olleh dlrow"` |
| `"  abc  xy "` | `"  cba  yx "` |
| `""` | `""` |

## Approach A — explicit two-pointer reversal

1. Copy the borrowed `std::string_view` input into an owned `std::string`.
2. Skip spaces without changing them.
3. Find the next segment ending at a space or the end of the string.
4. Swap the first and last characters, then the second and second-last,
   moving inward until both pointers meet.
5. Continue scanning from the end of the segment.

Using `std::size_t` for indices matches `std::string::size()`.
The right pointer begins at the one-past-the-end position. Decrement it
**before** using it as an index, which avoids reading outside the string.

## Approach B — a C++20 algorithm

The professional version uses the same clear segment scanning but
replaces manual swapping with `std::ranges::reverse(begin, end)`.
This expresses *what* the operation does and delegates implementation
details to the standard library. We turn the string index into an iterator
offset using `std::ptrdiff_t`. For this beginner example, the conversion
assumes the string length fits an iterator's difference type, as required
by the standard library iterator model.

Both implementations run in **O(n)** time and use **O(n)** memory because the
returned output is an independently owned string. Extra memory beyond
the output is O(1). No threads are needed here.

## Constraints and common mistakes

Inputs are ASCII bytes, not Unicode grapheme clusters. Reversing UTF-8
bytes can corrupt accented letters. Never collapse repeated spaces or
reverse the order of words instead of each word's characters. Empty
strings and strings containing only spaces are valid.

## Build, test, and experiment

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Or, without CMake:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic -Werror tests.cpp -o reverse_tests
./reverse_tests
```

**Follow-up:** Support tabs as additional separators while preserving
their exact positions. Add tests before modifying the implementation.
