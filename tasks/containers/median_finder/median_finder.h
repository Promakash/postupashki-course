#pragma once

#include <set>
#include <cmath>
#include <vector>
#include <unordered_set>

class MedianFinder {
public:
    MedianFinder() = default;

    void Insert(int val);

    void Remove(int val);

    int Find();
};