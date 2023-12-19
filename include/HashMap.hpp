#include <iostream>
#include <vector>
#include <list>
using namespace std;

class StringHashMap {
private:
    struct KeyValuePair {
        string key;
        string value;
    };

    vector<list<KeyValuePair>> buckets;

    // Hash function to map a key to an index
    size_t hash(const string& key) const {
        size_t sum = 0;
        for (char c : key) {
            sum += static_cast<size_t>(c);
        }
        return sum % buckets.size();
    }

public:
    StringHashMap(size_t size = 10) : buckets(size) {}

    // Insert a key-value pair into the hash map
    void insert(const string& key, const string& value) {
        size_t index = hash(key);
        for (auto& pair : buckets[index]) {
            if (pair.key == key) {
                // Key already exists, update the value
                pair.value = value;
                return;
            }
        }

        // Key doesn't exist, add a new key-value pair
        buckets[index].push_back({ key, value });
    }

    // Get the value associated with a key
    string get(const string& key) const {
        size_t index = hash(key);
        for (const auto& pair : buckets[index]) {
            if (pair.key == key) {
                // Key found, return the corresponding value
                return pair.value;
            }
        }

        return "";
    }
    
    ~StringHashMap() = default;
};