#include <catch2/catch_test_macros.hpp>
#include "lru_cache.h"

TEST_CASE("LRUCache") {
    SECTION("Insert and Find") {
        LRUCache cache(3);

        cache.Insert("communism", "999");
        cache.Insert("capitalism", "-999");
        cache.Insert("marksizm", "250");

        auto result = cache.Find("communism");
        REQUIRE(result.first);
        REQUIRE(result.second == "999");

        cache.Insert("another one", "228");

        result = cache.Find("another one");
        REQUIRE(result.first);
        REQUIRE(result.second == "228");

        result = cache.Find("capitalism");
        REQUIRE(!result.first);

        cache.Insert("a", "1");
        cache.Insert("b", "2");
        cache.Insert("c", "3");

        result = cache.Find("another one");
        REQUIRE(!result.first);

        result = cache.Find("capitalism");
        REQUIRE(!result.first);

        result = cache.Find("marksizm");
        REQUIRE(!result.first);

        result = cache.Find("a");
        REQUIRE(result.first);
        REQUIRE(result.second == "1");

        result = cache.Find("b");
        REQUIRE(result.first);
        REQUIRE(result.second == "2");

        result = cache.Find("c");
        REQUIRE(result.first);
        REQUIRE(result.second == "3");

        cache.Insert("last one", "123");

        result = cache.Find("a");
        REQUIRE(!result.first);
    }
}