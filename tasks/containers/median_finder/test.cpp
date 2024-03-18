#include "median_finder.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <unordered_set>

bool allowDuplicates = false;

std::vector<int> GenerateVector(size_t n, size_t restrict = 1'000'000) {
    if (!allowDuplicates) {
        std::unordered_set<int> s;
        while (s.size() != n) {
            s.insert(rand());
        }

        return std::vector<int>{s.begin(), s.end()};
    }

    std::vector<int> v;
    v.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        v.push_back(rand() % restrict);
    }

    return v;
}

void CheckMedian(std::vector<int> test, MedianFinder &medianFinder) {
    std::sort(test.begin(), test.end());
    if (test.empty()) {
        return;
    }
    REQUIRE((medianFinder.Find() == test[test.size() / 2] || medianFinder.Find() == test[(test.size() - 1) / 2]));
}

class TestLogger {
public:
    TestLogger(std::string testName)
            : testName_(std::move(testName)) {
        std::cout << "TEST running: " << testName_ << std::endl;
        start = std::chrono::high_resolution_clock::now();
    }

    ~TestLogger() {
        auto end = std::chrono::high_resolution_clock::now();

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "TEST " << testName_ << " HAS BEEN PASSED IN " << ms << "ms" << std::endl;
    }

private:
    std::string testName_;
    std::chrono::high_resolution_clock::time_point start;
};

TEST_CASE("No Duplicates") {
    allowDuplicates = false;
    SECTION("Simple test") {

        std::vector<int> test = {10, 3, 4, 5, 6, 13, 54};

        MedianFinder medianFinder;

        for (auto el: test) {
            medianFinder.Insert(el);
        }
        CheckMedian(test, medianFinder);
    }

    SECTION("Insert test") {
        std::vector<int> test = GenerateVector(1'000'000, 10);

        MedianFinder medianFinder;

        for (auto &el: test) {
            medianFinder.Insert(el);
        }
        CheckMedian(test, medianFinder);
    }

    SECTION("Delete test") {
        std::vector<int> test = GenerateVector(1'000'000, 10000);
        MedianFinder medianFinder;

        for (auto &el: test) {
            medianFinder.Insert(el);
        }

        std::vector<int> remain;
        for (size_t i = 0; i < test.size(); ++i) {
            auto val = test[i];
            if (i % 3 == 1) {
                medianFinder.Remove(val);
            } else {
                remain.push_back(val);
            }
        }

        CheckMedian(remain, medianFinder);
    }

    SECTION("Insert and delete test") {

        MedianFinder medianFinder;

        std::vector<int> test_data = GenerateVector(2'500);
        std::vector<int> test;

        for (auto el: test_data) {
            medianFinder.Insert(el);
            test.push_back(el);
            CheckMedian(test, medianFinder);
        }

        for (auto el: test_data) {
            medianFinder.Remove(el);
            test.erase(std::find(test.begin(), test.end(), el));
            CheckMedian(test, medianFinder);
        }
    }

    SECTION("Stress test") {

        std::vector<int> test;
        test.reserve(1'000'000);

        MedianFinder medianFinder;

        for (size_t i = 0; i < 20'000; ++i) {
            int choice = rand() % 10;

            if (choice == 0) {
                int val = test[rand() % test.size()];
                medianFinder.Remove(val);
                auto it = std::find(test.begin(), test.end(), val);
                test.erase(it);
            } else if (0 < choice && choice < 8) {
                int val = rand();
                medianFinder.Insert(val);
                test.push_back(val);
            } else {
                CheckMedian(test, medianFinder);
            }
        }
    }
    std::cout << "Tests without duplicates has been passed!" << std::endl;
    std::cout << std::endl;
}

TEST_CASE("With duplicates") {
    allowDuplicates = true;
    SECTION("Simple test") {

        std::vector<int> test = {10, 3, 4, 5, 6, 13, 54};

        MedianFinder medianFinder;

        for (auto el: test) {
            medianFinder.Insert(el);
        }
        CheckMedian(test, medianFinder);
    }

    SECTION("Insert test") {
        std::vector<int> test = GenerateVector(1'000'000, 10);

        MedianFinder medianFinder;

        for (auto &el: test) {
            medianFinder.Insert(el);
        }
        CheckMedian(test, medianFinder);
    }

    SECTION("Delete test") {
        std::vector<int> test = GenerateVector(1'000'000, 10000);
        MedianFinder medianFinder;

        for (auto &el: test) {
            medianFinder.Insert(el);
        }

        std::vector<int> remain;
        for (size_t i = 0; i < test.size(); ++i) {
            auto val = test[i];
            if (i % 3 == 1) {
                medianFinder.Remove(val);
            } else {
                remain.push_back(val);
            }
        }

        CheckMedian(remain, medianFinder);
    }

    SECTION("Insert and delete test") {

        MedianFinder medianFinder;

        std::vector<int> test_data = GenerateVector(2'500);
        std::vector<int> test;

        for (auto el: test_data) {
            medianFinder.Insert(el);
            test.push_back(el);
            CheckMedian(test, medianFinder);
        }

        for (auto el: test_data) {
            medianFinder.Remove(el);
            test.erase(std::find(test.begin(), test.end(), el));
            CheckMedian(test, medianFinder);
        }
    }

    SECTION("Stress test") {

        std::vector<int> test;
        test.reserve(1'000'000);

        MedianFinder medianFinder;

        for (size_t i = 0; i < 20'000; ++i) {
            int choice = rand() % 10;

            if (choice == 0) {
                int val = test[rand() % test.size()];
                medianFinder.Remove(val);
                auto it = std::find(test.begin(), test.end(), val);
                test.erase(it);
            } else if (0 < choice && choice < 8) {
                int val = rand();
                medianFinder.Insert(val);
                test.push_back(val);
            } else {
                CheckMedian(test, medianFinder);
            }
        }
    }
    SECTION("Extra duplicates") {

        std::vector<int> test;
        test.reserve(1'000'000);

        MedianFinder medianFinder;

        for (size_t i = 0; i < 1'000'001; ++i) {
            if (i % 10000 == 0) {
                CheckMedian(test, medianFinder);
            }
            if (i % 100 == 0) {
                medianFinder.Insert(1337);
                test.push_back(1337);
                continue;
            }

            if (i % 12345 == 0) {
                for (size_t i = 0; i < 100; ++i) {
                    test.erase(std::find(test.begin(), test.end(), 228));
                    medianFinder.Remove(228);
                }
                continue;
            }

            medianFinder.Insert(228);
            test.push_back(228);
        }
    }
    std::cout << "Tests with duplicates has been passed!" << std::endl;
    std::cout << std::endl;
}