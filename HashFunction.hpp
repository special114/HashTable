#ifndef HASHFUNCTION_HPP
#define HASHFUNCTION_HPP

/* File from HashTable project
 * author: Rafał Surdej
 */

#include <iostream>
#include <functional>
#include <stdexcept>

const int N = 20;


template<class K>
class DefaultHashFun
{
private:
    size_t num_of_buckets;
public:
    DefaultHashFun(int buckets = N)
    {
        if (buckets <= 0)
            throw (std::invalid_argument("Number of buckets must be greater than 0."));
        num_of_buckets = buckets;
    }
    size_t getBuckets() const
    {
        return num_of_buckets;
    }
    size_t operator()(const K& key) const
    {
        return std::hash<K>()(key) % num_of_buckets;
    }
};


#endif // HASHFUNCTION_HPP
