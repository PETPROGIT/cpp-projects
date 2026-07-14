#pragma once

// public methods and operators:

template<typename Key, typename Value>
FlatMap<Key, Value>::FlatMap(std::initializer_list<Pair> initializer_list) {
    for (const auto& i : initializer_list) {
        Insert(i);
    }
}

// Copy and Move constructors:
template<typename Key, typename Value>
FlatMap<Key, Value>::FlatMap(const FlatMap& other) : 
    Buffer(other.Buffer)
{

}
template<typename Key, typename Value>
FlatMap<Key, Value>::FlatMap(FlatMap&& other) noexcept : 
    Buffer(std::move(other.Buffer))
{

}

// Copy and Move operators:
template<typename Key, typename Value>
FlatMap<Key, Value>& FlatMap<Key, Value>::operator=(const FlatMap& other) {
    if (this != &other) {
        Buffer = other.Buffer;
    }
    return *this;
}
template<typename Key, typename Value>
FlatMap<Key, Value>& FlatMap<Key, Value>::operator=(FlatMap&& other) noexcept {
    if (this != &other) {
        Buffer = std::move(other.Buffer);
    }
    return *this;
}

// Returns a value by key.
// If the key is not present in the container, insert a default value into the container and return a reference to it:
template<typename Key, typename Value>
Value& FlatMap<Key, Value>::operator[](const Key& key) {
    bool inFlatMap;
    auto iteratorToInsert = Find(key, inFlatMap);
    if (!inFlatMap) {
        return Buffer.emplace(iteratorToInsert, key, Value{})->second;
    }
    return iteratorToInsert->second;
}

// Compares each key-value pair from two containers:
template<typename Key, typename Value>
bool FlatMap<Key, Value>::operator==(const FlatMap& rightOperand) const {
    return Buffer == rightOperand.Buffer;
}
template<typename Key, typename Value>
bool FlatMap<Key, Value>::operator!=(const FlatMap& rightOperand) const {
    return Buffer != rightOperand.Buffer;
}

// Exchanges the values of two flatmaps:
template<typename Key, typename Value>
void FlatMap<Key, Value>::Swap(FlatMap& other) noexcept {
    std::swap(Buffer, other.Buffer);
}

// Cleans the container:
template<typename Key, typename Value>
void FlatMap<Key, Value>::Clear() {
    Buffer.clear();
}

// Deletes an element by the specified key
// Returns true if the element is deleted successfully, else returns false:
template<typename Key, typename Value>
bool FlatMap<Key, Value>::Erase(const Key& key) {
    bool inFlatMap;
    auto iteratorToErase = Find(key, inFlatMap);
    if (!inFlatMap) {
        return false;
    }
    Buffer.erase(iteratorToErase);
    return true; 
}

// Inserting into a container. The return value is the success of the insertion
// Returns true if the element is inserted successfully, else returns false:
template<typename Key, typename Value>
bool FlatMap<Key, Value>::Insert(const Pair& pairKeyValue) {
    bool inFlatMap;
    auto iteratorToInsert = Find(pairKeyValue.first, inFlatMap);
    if (inFlatMap) {
        return false;
    }
    Buffer.emplace(iteratorToInsert, pairKeyValue);
    return true;
}
template<typename Key, typename Value>
bool FlatMap<Key, Value>::Insert(const Key& key, const Value& value) {
    return Insert(std::make_pair(key, value));
}

// Checks if a value is present for a given key:
template<typename Key, typename Value>
bool FlatMap<Key, Value>::Contains(const Key& key) const {
    bool inFlatMap;
    Find(key, inFlatMap);
    return inFlatMap;
}

// Returns a reference to the value by key. Throws an exception if unsuccessful:
template<typename Key, typename Value>
Value& FlatMap<Key, Value>::At(const Key& key) {
    bool inFlatMap;
    auto itertor = Find(key, inFlatMap);
    if (!inFlatMap) {
        throw std::out_of_range("The key is missing in FlatMap");
    }
    return itertor->second;
}
template<typename Key, typename Value>
const Value& FlatMap<Key, Value>::At(const Key& key) const {
    bool inFlatMap;
    const auto itertor = Find(key, inFlatMap);
    if (!inFlatMap) {
        throw std::out_of_range("The key is missing in FlatMap");
    }
    return itertor->second;
}

// Returns the current size of the container:
template<typename Key, typename Value>
size_t FlatMap<Key, Value>::Size() const noexcept {
    return Buffer.size();
}

// Returns true if the container is empty, else returns false:
template<typename Key, typename Value>
bool FlatMap<Key, Value>::Empty() const noexcept {
    return Buffer.empty();
}


// private methods:

// Helper method implementation:
template<typename Key, typename Value>
auto FlatMap<Key, Value>::templateFind(auto begin, auto end, const Key& key, bool& inFlatMap) const {
    if (begin == end) {
        inFlatMap = false;
        return begin;
    }
    auto left = begin;
    auto right = end;
    while (left < right) {
        auto mid = left + (right - left) / 2;
        if (key > mid->first) {
            left = mid + 1;
        }
        else if (key < mid->first) {
            right = mid;
        }
        else {
            inFlatMap = true;
            return mid;
        }
    }
    inFlatMap = false;
    return left;
}

// Returns the pair's index in the buffer, else returns the index for insertion:
template<typename Key, typename Value>
auto FlatMap<Key, Value>::Find(const Key& key, bool& inFlatMap) {
    return templateFind(Buffer.begin(), Buffer.end(), key, inFlatMap);
}
template<typename Key, typename Value>
const auto FlatMap<Key, Value>::Find(const Key& key, bool& inFlatMap) const {
    return templateFind(Buffer.begin(), Buffer.end(), key, inFlatMap);

}