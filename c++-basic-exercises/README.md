# C++ Basic Exercises

A growing series of standalone C++20 programming exercises focused on correctness, maintainable interfaces, memory behavior and measured performance.

Each exercise includes an independently written problem statement, a straightforward solution, a performance-oriented production-style solution, and automated tests (Google Test or dependency-free CTest, as documented per lesson).

| Exercise | Topic |
| --- | --- |
| [01 — Single-Change Palindrome](01-single-change-palindrome/) | String symmetry, O(1) space, early exit |
| [02 — Case-insensitive isograms](02-case-insensitive-isograms/) | Nested loops, ASCII normalization, `std::array`, one-pass lookup |
| [03 — Count ASCII vowels](03-vowel-count/) | Iteration, pure predicates, string views, C++20 ranges |
| [04 — Reverse letters within words](04-reverse-word-characters/) | Two-pointer reversal, preserving spaces, ranges algorithms |

Run each exercise using the CMake instructions in its own README. Each exercise is self-contained and does not depend on the repository's existing build system.
