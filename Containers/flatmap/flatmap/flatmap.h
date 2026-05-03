#pragma once

#include "vector"
#include "cstddef"
#include <stdexcept>
#include <utility>
#include "initializer_list"

// FlatMap class:
template<typename Key, typename Value>
class FlatMap {
private:
    // Vector for storing key-value pairs:
    std::vector<std::pair<Key, Value>> Buffer;

    // Helper method for binary search:
    auto templateFind(auto begin, auto end, const Key& key, bool& inFlatMap) const;

    // Returns the pair's index in the buffer, else returns the index for insertion:
    auto Find(const Key& key, bool& inFlatMap);
    const auto Find(const Key& key, bool& inFlatMap) const;
public:
    // Std::pair storing a key and a value of an element:
    using Pair = std::pair<Key, Value>;

    FlatMap() = default;
    FlatMap(std::initializer_list<Pair> initializer_list);

    // Copy and Move constructors:
    FlatMap(const FlatMap& other); 
    FlatMap(FlatMap&& other) noexcept;
    
    ~FlatMap() = default;

    // Copy and Move operators:
    FlatMap& operator=(const FlatMap& other);
    FlatMap& operator=(FlatMap&& other) noexcept;

    // Returns a value by key.
    // If the key is not present in the container, insert a default value into the container and return a reference to it:
    Value& operator[](const Key& key);
    
    // Compares each key-value pair from two containers:
    bool operator==(const FlatMap& rightOperand) const;
    bool operator!=(const FlatMap& rightOperand) const;


    // Exchanges the values of two flatmaps:
    void Swap(FlatMap& other) noexcept;

    // Cleans the container:
    void Clear();

    // Deletes an element by the specified key
    // Returns true if the element is deleted successfully, else returns false:
    bool Erase(const Key& key);

    // Inserting into a container. The return value is the success of the insertion
    // Returns true if the element is inserted successfully, else returns false:
    bool Insert(const Pair& pairKeyValue);
    bool Insert(const Key& key, const Value& value);


    // Checks if a value is present for a given key:
    bool Contains(const Key& key) const;

    // Returns a reference to the value by key. Throws an exception if unsuccessful:
    Value& At(const Key& key);
    const Value& At(const Key& key) const;

    // Returns the current size of the container:
    size_t Size() const noexcept;

    // Returns true if the container is empty, else returns false:
    bool Empty() const noexcept;
};


#include "flatmap.cpp"
