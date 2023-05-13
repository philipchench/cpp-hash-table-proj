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
        HashTable(int size=10, float max_load_factor=1.0) : count{0}, max_load_factor{max_load_factor}
        {
            buckets.resize(size);
        }

        // destructor
        ~HashTable() {}

        // insert key value pair into the hash table
        void insert(const K& key, V value)
        {
            float loadfac = float(count) / buckets.size();
            if (loadfac > max_load_factor)
            {
                std::cout << "resizing at count: " << count << "\n";
                resize();
            }
            int idx = hash_func(key, buckets.size());
            auto& bucket = buckets[idx];
            count++;
            // if item is in the bucket, then we update the value
            for (auto& item : bucket)
            {
                if (item.first == key)
                {
                    item.second = std::move(value);
                    return;
                }
            }
            // otherwise add new item
            bucket.push_back(std::make_pair(key, value));
        }

        // remove key from hash table if found
        void remove(K& key)
        {
            int idx = hash_func(key, buckets.size());
            auto& bucket = buckets[idx];
            count--;
            // if item is in the bucket, then we erase it
            for (auto it{ bucket.begin() }; it != bucket.end(); it++)
            {
                if (it->first == key)
                {
                    bucket.erase(it);
                    std::cout << "Successfully erased key.\n";
                    return;
                }
            }
            // for now just output message that no key found
            std::cout << "Remove key failed: no key found.\n";
        }

        // return value corresponding to key if found
        V& get(const K& key)
        {
            int idx = hash_func(key, buckets.size());
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
            std::cout << "get key failed: returned empty object.\n";
            bucket.push_back(std::make_pair(key, V()));
            return bucket.back().second;
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
        int count;
        float max_load_factor;
        // buckets to hash items to, each bucket is a std::list of pairs
        std::vector<std::list<std::pair<K, V>>> buckets;
        // hash function using std::hash and then mod by buckets size
        int hash_func(const K& key, int numbuckets)
        {
            // std::cout << std::to_string(std::hash<K>()(key)) + "\n";
            return std::hash<K>()(key) % numbuckets;
        }

        void resize()
        {
            auto oldsize = buckets.size();
            auto newsize = oldsize * 2;
            std::vector<std::list<std::pair<K, V>>> newbuckets(newsize);
            for (auto& bucket : buckets)
            {
                for (auto it{ bucket.begin() }; it != bucket.end();)
                {
                    auto iter_copy = it;
                    it++;
                    int idx = hash_func(iter_copy->first, newsize);
                    auto& newbucket = newbuckets[idx];
                    newbucket.splice(newbucket.end(), bucket, iter_copy);
                }
            }
            buckets = newbuckets;
        }

};

#endif