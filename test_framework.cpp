#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>


struct TestCase {
  std::string name;
  std::function<bool()> test_fn;
};

class MiniTestFramework {
private:
  std::vector<TestCase> tests;

public:
  void add_test(const std::string &name, std::function<bool()> fn) {
    tests.push_back({name, fn});
  }

  void run() {
    int passed = 0, failed = 0;
    for (const auto &test : tests) {
      bool result = false;
      try {
        result = test.test_fn();
      } catch (...) {
        result = false;
      }

      if (result) {
        std::cout << "✅ " << test.name << "\n";
        ++passed;
      } else {
        std::cout << "❌ " << test.name << "\n";
        ++failed;
      }
    }

    std::cout << "\n--- Mini-Framework Summary ---\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";
  }
};
