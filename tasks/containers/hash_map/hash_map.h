#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cstddef>

template <typename Key, typename Value>
class HashMap {
public:
    struct Entry {
        Key key;
        Value value;
    };
    
public:
    class Iterator {
    public:
        Iterator();

        Iterator& operator++();

        Entry& operator*();

        bool operator!=(const Iterator& rhs);
    };

public:
    bool Insert(const Key& key, const Value& value);

    std::pair<bool, Value> Find(const Key& key) const;

    bool Remove(const Key& key);

    Value& operator[](const Key& key);

    size_t Size() const;

    auto begin();

    auto end();

};
