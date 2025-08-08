#include "test_framework.hpp"
#include <algorithm>
#include <string>


// ----------------------
// Funkcja logiczna
// ----------------------
int descending_order(int num) {
  std::string digits = std::to_string(num);
  std::sort(digits.begin(), digits.end(), std::greater<char>());
  return std::stoi(digits);
}

#ifdef RUN_GTESTS

// ----------------------
// Sekcja GTest
// ----------------------
#include <gtest/gtest.h>

struct DescendingOrderTestCase {
  int input;
  int expected;
};

class DescendingOrderTest
    : public ::testing::TestWithParam<DescendingOrderTestCase> {};

TEST_P(DescendingOrderTest, HandlesCases) {
  auto [input, expected] = GetParam();
  EXPECT_EQ(descending_order(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    DescendingOrderTests, DescendingOrderTest,
    ::testing::Values(DescendingOrderTestCase{0, 0},
                      DescendingOrderTestCase{15, 51},
                      DescendingOrderTestCase{123456789, 987654321},
                      DescendingOrderTestCase{42145, 54421},
                      DescendingOrderTestCase{145263, 654321}));

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#else

// ----------------------
// Sekcja mini-framework
// ----------------------
int main() {
  MiniTestFramework tester;

  tester.add_test("Test Zero", []() { return descending_order(0) == 0; });

  tester.add_test("Test Two Digits",
                  []() { return descending_order(15) == 51; });

  tester.add_test("Test Many Digits",
                  []() { return descending_order(123456789) == 987654321; });

  tester.add_test("Test Mixed Digits",
                  []() { return descending_order(42145) == 54421; });

  tester.add_test("Test Random Order",
                  []() { return descending_order(145263) == 654321; });

  tester.run();
  return 0;
}

#endif
