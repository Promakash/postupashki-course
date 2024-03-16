#pragma once

#include <cstdlib>
#include <utility>
#include <string>

class LRUCache {
public:
    LRUCache(size_t maxSize);

    void Insert(const std::string& key, const std::string& value);

    std::pair<bool, std::string> Find(const std::string& key);
};