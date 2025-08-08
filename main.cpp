#include "descending_order.cpp"
#include "miniframework.hpp"

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
