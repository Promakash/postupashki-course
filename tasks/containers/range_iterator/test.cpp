#include <catch2/catch_test_macros.hpp>
#include "range.h"

#include <vector>

std::vector<int> GetExpectedRange(int start, int end, int step) {
    std::vector<int> res;

    if (step < 0) {
        for (size_t i = start; i > end; i += step) {
            res.push_back(i);
        }

        return res;
    }

    for (size_t i = start; i < end; i += step) {
        res.push_back(i);
    }

    return res;
}

TEST_CASE("Range Iterator") {
    SECTION("Default range") {
        std::vector<int> expected = GetExpectedRange(0, 10, 1);

        std::vector<int> actual;
        for (auto el: Range(10)) {
            actual.push_back(el);
        }

        REQUIRE(actual == expected);
    }

    SECTION("Full range") {
        std::vector<int> expected = GetExpectedRange(228, 1488, 1);

        std::vector<int> actual;
        for (auto el: Range(228, 1488)) {
            actual.push_back(el);
        }

        REQUIRE(actual == expected);
    }

    SECTION("Full range with non-default step") {
        std::vector<int> expected = GetExpectedRange(1234, 12345, 5);

        std::vector<int> actual;
        for (auto el: Range(1234, 12345, 5)) {
            actual.push_back(el);
        }

        REQUIRE(actual == expected);
    }

    SECTION("Full range with negative step") {
        std::vector<int> expected = GetExpectedRange(1000, 0, -1);

        std::vector<int> actual;
        for (auto el: Range(1000, 0, -1)) {
            actual.push_back(el);
        }

        REQUIRE(actual == expected);
    }
}