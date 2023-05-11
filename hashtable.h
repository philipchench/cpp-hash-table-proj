#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <functional>

template<typename K, typename V>
class HashTable
{

    /*
        This is an implementation of template class hash table. Type K
        is the key type, and V is the value type. This implementation
        uses std::vector for buckets, std::list for linked lists,
        std::pair for key-value pair, and std::hash for hash function.
    */

    public:
        // constructor that takes input the size of buckets vector
        HashTable(int size=10)
        {
            buckets.resize(size);
        }

        // destructor
        ~HashTable() {}

        // insert key value pair into the hash table
        void insert(K& key, V& value)
        {
            int idx = hash_func(key);
            auto& bucket = buckets[idx];

            // if item is in the bucket, then we update the value
            for (auto& item : bucket)
            {
                if (item.first == key)
                {
                    item.second = value;
                    return;
                }
            }
            // otherwise add new item
            bucket.push_back(std::make_pair(key, value));
        }

        // remove key from hash table if found
        void remove(K& key)
        {
            int idx = hash_func(key);
            auto& bucket = buckets[idx];

            // if item is in the bucket, then we erase it
            for (auto& item : bucket)
            {
                if (item.first == key)
                {
                    bucket.erase(item);
                    std::cout << "Successfully erased key.\n";
                    return;
                }
            }
            // for now just output message that no key found
            std::cout << "Remove key failed: no key found.\n";
        }

        // return value corresponding to key if found
        V& get(K& key)
        {
            int idx = hash_func(key);
            auto& bucket = buckets[idx];

            // if item is in the bucket, then we erase it
            for (auto& item : bucket)
            {
                if (item.first == key)
                {
                    std::cout << "Successfully found item.\n";
                    return item.second;
                }
            }
            // for now return null
            std::cout << "get key failed: returned NULL.\n";
            return NULL;
        }

        // custom stdout
        friend std::ostream& operator<< (std::ostream & out, const HashTable<K, V> & t)
        {
            out << "{\n";
            for (auto& bucket : t.buckets)
            {
                if (bucket.empty()) continue;
                for (auto& item : bucket)
                {
                    out << item.first << ": " << item.second << ", ";
                }
                out << "\n"; // each line shows 1 bucket's items
            }
            out << "}\n";
            return out;
        }

    private:
        // buckets to hash items to, each bucket is a std::list of pairs
        std::vector<std::list<std::pair<K, V>>> buckets;

        // hash function using std::hash and then mod by buckets size
        int hash_func(K& key)
        {
            return std::hash<K>()(key) % buckets.size();
        }

};

#endif