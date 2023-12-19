#include <iostream>
#include <vector>
#include <list>
#include <iterator>

// Hash Map class
template<typename KeyType, typename ValueType>
class HashMap {
private:
    struct KeyValuePair {
        KeyType key;
        ValueType value;
    };
    std::vector<std::list<KeyValuePair>> buckets;

    size_t hash(const KeyType& key) const {
        return std::hash<KeyType>{}(key) % buckets.size();
    }

public:
    HashMap(size_t size = 10) : buckets(size) {}

    void insert(const KeyType& key, const ValueType& value) {
        size_t index = hash(key);
        for (auto& pair : buckets[index]) {
            if (pair.key == key) {
                // Key already exists, update the value
                pair.value = value;
                return;
            }
        }

        // Key doesn't exist, add a new key-value pair
        buckets[index].push_back({key, value});
    }

    // Get the value associated with a key
    ValueType get(const KeyType& key) const {
        size_t index = hash(key);
        for (const auto& pair : buckets[index]) {
            if (pair.key == key) {
                // Key found, return the corresponding value
                return pair.value;
            }
        }

        // Key not found, return a default value (you might want to handle this differently)
        return ValueType{};
    }

    // Destructor
    ~HashMap() = default;
};