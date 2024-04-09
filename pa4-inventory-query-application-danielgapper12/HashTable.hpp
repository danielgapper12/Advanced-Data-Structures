#pragma once

#include <list>
#include <vector>
#include <optional>
#include <functional>
#include <string>

using namespace std;

template<typename KeyType, typename ProductDetails>
class HashNode 
{
public:
    KeyType key;
    ProductDetails value;
    
    HashNode(const KeyType& key, const ProductDetails& value) : key(key), value(value) {}
    
    ProductDetails getValue() const { return value; }
    void setValue(const ProductDetails& value) { this->value = value; }
};

template<typename KeyType, typename ValueType, typename Hash = hash<KeyType>> 
class HashTable 
{
public:
    HashTable(size_t size) : table(size) {}

    void insert(const KeyType& key, const ValueType& value) 
    {
        size_t index = Hash()(key) % table.size();
        // uses chaining as collision resolution
        table[index].push_back(HashNode<KeyType, ValueType>(key, value));
    }

    ValueType* find(const KeyType& key) 
    {
        size_t index = Hash()(key) % table.size();
        for (auto& node : table[index]) 
        {
            if (node.key == key) 
            {
                return &(node.value); // Return the address of the value
            }
        }
        return nullptr; 
    }

private:
    // vector of lists where each list is a bucket in hash table, facilitates chaining method for collision resolution
    vector<list<HashNode<KeyType, ValueType>>> table;
};
