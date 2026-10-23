# Exercise 02 — Case-insensitive isograms

**Level:** C++20 foundations. **Learning goals:** nested loops, character normalization, `std::string_view`, `std::array`, early returns, and choosing an algorithm with a clear memory budget.

## The problem

Write a function that returns `true` if no English letter appears more than once in a word. Treat uppercase and lowercase versions of the same letter as equal.

For this exercise, inputs may contain only ASCII letters (`A`–`Z`, `a`–`z`); any other byte returns `false`. An empty word returns `true`. This explicit invalid-input rule makes behavior predictable instead of silently ignoring unsupported characters.

| Input | Result | Explanation |
| --- | --- | --- |
| `"isogram"` | `true` | Every letter is different. |
| `"AbC"` | `true` | Case is ignored. |
| `"moOse"` | `false` | `o` and `O` are equal after normalization. |
| `"Aa"` | `false` | The same letter appears twice. |
| `""` | `true` | There are no repeated letters. |
| `"a-b"` | `false` | A hyphen is outside the permitted input. |

Both solutions live in [solutions.hpp](solutions.hpp) and share the same interface.

## Solution A — quick and straightforward

```cpp
[[nodiscard]] inline bool simple(std::string_view word) noexcept {
    for (std::size_t i = 0; i < word.size(); ++i) {
        const auto current = ascii_lower(static_cast<unsigned char>(word[i]));
        if (current < 'a' || current > 'z') return false;

        for (std::size_t j = 0; j < i; ++j) {
            if (ascii_lower(static_cast<unsigned char>(word[j])) == current)
                return false;
        }
    }
    return true;
}
```

**Read it line by line:**

1. `i` identifies the character we are checking now; `std::size_t` matches the unsigned indexing type of strings.
2. `ascii_lower` converts ASCII uppercase letters into their lowercase equivalents, so `A` and `a` compare equally. The `unsigned char` conversion avoids accidental issues with negative `char` values.
3. The input check rejects spaces, punctuation, digits, and non-ASCII bytes.
4. `j < i` scans **only characters already visited**. If we find the current letter there, it is a duplicate and we return `false` immediately.
5. If the loop finishes, no duplicate exists, so we return `true`.

**Trade-off:** It is extremely easy to understand and uses no additional containers, but may repeatedly compare the same previously visited letters. It does not allocate memory.

## Solution B — production-style lookup table

```cpp
[[nodiscard]] inline bool optimized(std::string_view word) noexcept {
    std::array<bool, 26> seen{};

    for (const unsigned char original : word) {
        const auto letter = ascii_lower(original);
        if (letter < 'a' || letter > 'z') return false;

        const auto index = static_cast<std::size_t>(letter - 'a');
        if (seen[index]) return false;
        seen[index] = true;
    }
    return true;
}
```

**Read it line by line:**

1. `std::array<bool, 26> seen{}` creates a fixed-size table of **26 values initialized to `false`**. No `new`, no heap allocation, and no variable-length data structure are needed.
2. The range-for loop processes the word once, borrowing it through `std::string_view` instead of copying it. The caller owns the original characters during the call.
3. Normalize the letter and reject anything outside `a`–`z`.
4. Subtracting `'a'` converts the valid lowercase letter into its array index: `a -> 0`, `b -> 1`, ..., `z -> 25`. The validation above ensures this index is in range.
5. `seen[index]` means "we encountered this letter earlier." If it is already `true`, report a duplicate immediately. Otherwise, mark the letter as seen.
6. Returning `true` at the end means that every valid letter occurred at most once.

### Why these C++20 choices?

- **`std::string_view`** is a non-owning view of an existing string and avoids copying; **do not store a view** beyond its owner's lifetime. Both versions only read the view during the call.
- **`std::array`** expresses the fixed 26-letter domain, keeps the lookup table local to each invocation, and needs no synchronization when called from different threads.
- **`[[nodiscard]]`** helps the compiler warn if the caller ignores the returned answer.
- **`noexcept`** is appropriate here: the operations in these implementations cannot throw; no dynamic allocation is performed. This is not a rule to apply blindly to every function.
- **`inline`** permits these definitions in a header included from multiple translation units. It is *not* a promise that the compiler will physically inline every call.
- **No threads:** spawning threads for a word this small would make the code more complex and usually slower. Concurrency belongs in later lessons with enough work to justify it.

## Complexity and a subtle detail

The baseline uses a nested loop: in a *generalized* alphabet, a word with all distinct characters needs `1 + 2 + ... + (n-1)` comparisons, **O(n²)**. The lookup-table approach examines at most one array entry per letter, **O(n)**, with **O(1) extra space** (26 boolean entries). The baseline also uses **O(1) extra space**.

**Important nuance:** Here the alphabet has only 26 letters, so an all-distinct valid word has at most 26 characters. Any longer valid word necessarily contains a repeat, and both implementations stop when it is found. Thus the usual O(n²) comparison describes the nested-loop *pattern*, not an unlimited asymptotic worst case for this particular fixed-alphabet contract. Do not claim measured speedups without benchmarks.

## Edge cases and common mistakes

- `"Aa"` must be `false`: compare normalized letters, not original bytes.
- Empty input is `true` because there are no duplicate letters.
- `seen{}` matters: without zero-initialization the table could hold indeterminate values.
- Verify a letter is valid **before** computing and using an index.
- `std::tolower` has preconditions and locale-dependent behavior; this exercise deliberately uses explicit ASCII normalization instead.
- Non-English Unicode characters need a different contract and a Unicode-aware implementation; this code intentionally rejects non-ASCII bytes.

## Build and test

Requires CMake 3.20+ and a C++20 compiler. The test runner uses standard C++ and CTest: **no downloads or third-party dependencies**.

From the repository root:

```sh
cmake -S 'c++-basic-exercises/02-case-insensitive-isograms' -B build/isograms
cmake --build build/isograms
ctest --test-dir build/isograms --output-on-failure
```

You can also run `./build/isograms/case_insensitive_isograms_tests` on Linux/macOS (or the corresponding `.exe` on Windows). It reports the number of checks performed.

The tests cover representative inputs, unsupported bytes, and exhaustive short words over a mixed-case alphabet; each version is checked against an independent `std::set` reference implementation.

## Try it yourself

1. Change the specification so digits are allowed but do not count toward repeated letters. Which lines must change in both functions?
2. Replace the `std::array<bool, 26>` with `std::bitset<26>` and compare clarity. Does it change the asymptotic complexity?
3. Explain why using `std::unordered_set` here introduces more machinery than a 26-entry array, even though both lookups are usually constant-time.
