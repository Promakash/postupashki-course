#include "enumerate.h"
#include <catch2/catch_test_macros.hpp>

#include <utility>

TEST_CASE("enumerate test") {
    std::vector<std::string> test = {"this", "is", "very", "stupid", "test", ":)"};

    std::vector<std::pair<size_t, std::string>> actual;
    for (const auto& [index, element]: Enumerate(test.begin(), test.end())) {
        actual.push_back({index, element});
    }

    REQUIRE(actual.size() == test.size());

    for (size_t i = 0; i < test.size(); ++i) {
        REQUIRE(test[i] == actual[i].second);
        REQUIRE(i == actual[i].first);
    }
}