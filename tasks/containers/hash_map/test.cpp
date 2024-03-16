#include <catch2/catch_test_macros.hpp>

#include "random_utils.h"

#include "hash_map.h"

#include <unordered_map>

void FillHashTable(std::unordered_map<std::string, std::string>& table, size_t entryCount) {
    for (size_t i = 0; i < entryCount; ++i) {
        table.insert({"key" + std::to_string(i), "value" + std::to_string(i)});
    }
}

void FillHashTable(HashTable<std::string, std::string>& table, size_t entryCount) {
    for (size_t i = 0; i < entryCount; ++i) {
        table.Insert("key" + std::to_string(i), "value" + std::to_string(i));
    }
}

template<typename Key, typename Value, typename Container>
void CheckCorrectness(HashTable<Key, Value>& hashTable, const Container& expected) {
    REQUIRE(expected.size() == hashTable.Size());

    for (auto& [key, expectedValue]: expected) {
        auto [find, actualValue] = hashTable.Find(key);

        REQUIRE(find);

        REQUIRE(actualValue == expectedValue);
    }
}

TEST_CASE("unique insert") {
    HashTable<std::string, std::string> hashTable;

    REQUIRE(hashTable.Insert("postupashki", "top"));
    REQUIRE(!hashTable.Insert("postupashki", "kal"));
    REQUIRE(!hashTable.Insert("postupashki", "228"));

    REQUIRE(hashTable.Find("postupashki").second == "top");
    hashTable.Remove("postupashki");
    REQUIRE(!hashTable.Find("postupashki").first);
}

TEST_CASE("insert/find check") {
    size_t testSize = 10000;
    HashTable<std::string, std::string> hashTable;
    FillHashTable(hashTable, testSize);

    std::unordered_map<std::string, std::string> expected;
    FillHashTable(expected, testSize);

    CheckCorrectness(hashTable, expected);
}

TEST_CASE("remove check") {
    size_t testSize = 10000;
    HashTable<std::string, std::string> hashTable;
    FillHashTable(hashTable, testSize);
    
    std::vector<std::pair<std::string, std::string>> expected;
    for (size_t i = 0; i < testSize; ++i) {
        if (i % 3 == 0) {
            hashTable.Remove("key" + std::to_string(i));
        } else {
            expected.push_back({"key" + std::to_string(i), "value" + std::to_string(i)});
        }
    }

    CheckCorrectness(hashTable, expected);
}

TEST_CASE("operator [] check") {
    size_t stringSize = 10000;

    HashTable<char, int> actualLetterCount;
    std::unordered_map<char, int> expectedLetterCount;

    std::string randString = Utils::GenerateRandomString(stringSize);

    for (auto letter: randString) {
        ++actualLetterCount[letter];
        ++expectedLetterCount[letter];
    }

    CheckCorrectness(actualLetterCount, expectedLetterCount);
}

TEST_CASE("iterator check") {
    size_t testSize = 10000;
    HashTable<std::string, std::string> hashTable;
    FillHashTable(hashTable, testSize);

    std::unordered_map<std::string, std::string> expected;
    FillHashTable(expected, testSize);
    std::unordered_map<std::string, std::string> actual;

    for (const auto& entry: hashTable) {
        actual[entry.key] = entry.value;
    }

    REQUIRE(actual == expected);
}

TEST_CASE("stress test") {
    std::unordered_map<std::string, int> expected;
    HashTable<std::string, int> hashTable;

    for (size_t i = 0; i < 100'000; ++i) {
        int choise = rand() % 10;

        if (0 <= choise && choise <= 4) {
            for (size_t j = 0; j < 10; ++j) {
                auto generated = Utils::GenerateRandomString(100);
                int randVal = rand();
                hashTable[generated] = randVal;
                expected[generated] = randVal; 
            }

            for (size_t j = 0; j < 10; ++j) {
                auto generated = Utils::GenerateRandomString(100);
                int randVal = rand();
                hashTable.Insert(generated, randVal);
                expected.insert({generated, randVal}); 
            }
        } else if (5 <= choise <= 9) {            
            for (size_t i = 0; i < 10; ++i) {
                if (!expected.empty()) {
                    std::string deleteKey = expected.begin()->first;
                    expected.erase(deleteKey);
                    hashTable.Remove(deleteKey);
                }
            }
        } else {
            CheckCorrectness(hashTable, expected);
        }
    }
}