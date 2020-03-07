#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* File from HashTable project
 * author: Rafał Surdej
 */

#include "HashFunction.hpp"
#include "Iterator.hpp"
#include "ConstIterator.hpp"

class InvalidHashFunction : public std::runtime_error
{
public:
    explicit InvalidHashFunction(const std::string& s);
};

template <class K, class V>
struct Node
{
public:
    K key;
    V data;
    struct Node* next;
};



template<class K, class V, class F>
class Const_Iterator_Hasz;

/* It is an array whose every single element is given hashcode provided by the number of this element.
 * All the array elements are forward lists. It is like having various buckets with a certain number.
 * When we add an element to HashTable it gets its hashcode from a hash function and goes
 * to proper bucket. There can be many elements in one bucket so it is needed to have a container
 * inside.
 * */

template <class K, class V, class F = DefaultHashFun<K>>
class HashTable{
private:
    Node<K, V>** table;
    F hash_fun;
    size_t elems;
public:
    using key_type = K;
    using mapped_type = V;
    using value_type = Node<key_type, mapped_type>;
    using iterator = Iterator_Hasz<key_type, mapped_type, F>;
    using const_iterator = Const_Iterator_Hasz<key_type, mapped_type, F>;


    HashTable(const F& h_fun = F()) : hash_fun(h_fun)
    {
        if (hash_fun.getBuckets() <= 0)
                throw InvalidHashFunction("Hash function created wrong number of buckets!");
        else
        {
            this->table = new value_type* [hash_fun.getBuckets()];
            for (size_t i = 0; i < hash_fun.getBuckets(); ++i)
                table[i] = nullptr;
        }
    }
    HashTable(const HashTable<key_type, mapped_type, F>& other): hash_fun(other.hash_fun)
    {
        table = new value_type* [hash_fun.getBuckets()];
        for (int i = 0; i < hash_fun.getBuckets(); ++i)
            table[i] = nullptr;
        for (HashTable<key_type, mapped_type, F>::iterator it = other.begin(); it != other.end(); ++it)
            dodaj(it->key, it->data);
    }
    HashTable operator=(const HashTable<key_type, value_type, F>& other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < hash_fun.getBuckets() ; ++i)
            {
                if (table[i])
                {
                    value_type* curr_node = table[i];
                    while (curr_node)
                    {
                        value_type* prev_node = curr_node;
                        curr_node = curr_node->next;
                        delete prev_node;
                    }
                }
            }
            delete [] table;
            hash_fun = other.hash_fun;
            table = new value_type* [hash_fun.getBuckets()];
            for (int i = 0; i < hash_fun.getBuckets(); ++i)
                table[i] = nullptr;
            for (HashTable<key_type, mapped_type, F>::iterator it = other.poczatek(); it != other.koniec(); ++it)
                dodaj(it->key, it->value);
        }
        return *this;
    }

    value_type* find(const K& key)
    {
        size_t cell_num = hash_fun(key);
        value_type* curr_node = table[cell_num];
        while (curr_node && key != curr_node->key)
            curr_node = curr_node->next;
        return curr_node;
    }
    iterator insert(const K& key, const V& value)
    {
        size_t cell_num = hash_fun(key);
        value_type* curr_node = table[cell_num];
        value_type* prev_node = nullptr;
        while (curr_node && key != curr_node->key)  // going to the end of the list
        {
            prev_node = curr_node;
            curr_node = curr_node->next;
        }
        if (!curr_node)                             // if element doesn't exsist
        {
            value_type* new_node = new value_type;
            new_node->key = key;
            new_node->data = value;
            new_node->next = nullptr;
            if (prev_node)                          // checking if the cell isn't empty
                prev_node->next = new_node;
            else
                table[cell_num] = new_node;
            ++elems;
            return HashTable<key_type, mapped_type, F>::iterator(this, new_node);
        }
        else
            return HashTable<key_type, mapped_type, F>::iterator(this, curr_node);
    }
    int erase(const K& key)                 // function returns number of erased elements
    {
        size_t cell_num = hash_fun(key);
        value_type* curr_node = table[cell_num];
        value_type* prev_node = nullptr;
        while (curr_node && key != curr_node->key)
        {
            prev_node = curr_node;
            curr_node = curr_node->next;
        }
        if (curr_node)
        {
            if (prev_node)
                prev_node->next = curr_node->next; // When we do not delete firs element from the list
            else
                table[cell_num] = curr_node->next; // When we delete firs element from the list
            delete curr_node;
            --elems;
            return 1;
        }
        return 0;
    }
    bool empty() const
    {
        return elems == 0;
    }
    size_t size() const
    {
        return elems;
    }
    iterator begin()
    {
        if (!elems)
            return iterator(this, nullptr);
        for (size_t i = 0; i < hash_fun.getBuckets(); ++i)
            {
                if (table[i])
                    return (iterator(this, table[i]));
            }
        return iterator(this, nullptr);
    }
    const_iterator begin() const
    {
        if (!elems)
            return const_iterator(this, nullptr);
        else
            for (size_t i = 0; i < hash_fun.getBuckets(); ++i)
            {
                if (table[i])
                    return (const_iterator(this, table[i]));
            }
        return const_iterator(this, nullptr);
    }
    iterator end()
    {
        return iterator(this, nullptr);
    }
    const_iterator end() const
    {
        return const_iterator(this, nullptr);
    }
    size_t getNumOfBuckets() const
    {
        return hash_fun.getBuckets();
    }
    size_t getBucketNum(const K& key) const
    {
        return hash_fun(key);
    }
    value_type* getTableElement(const size_t elem_num) const
    {
        return table[elem_num];
    }

    template<class StreamType>
    void print(StreamType& stream) const
    {
        for (size_t i = 0; i < hash_fun.getBuckets(); ++i)
            if (table[i])
            {
                value_type* tmp = table[i];
                while (tmp)
                {
                    stream << tmp->key << " - " << tmp->data << std::endl;
                    tmp = tmp->next;
                }
            }
    }

    ~HashTable()
    {
        for (size_t i = 0; i < hash_fun.getBuckets() ; ++i)
        {
            if (table[i])
            {
                value_type* curr_node = table[i];
                while (curr_node)
                {
                    value_type* prev_node = curr_node;
                    curr_node = curr_node->next;
                    delete prev_node;
                }
            }
        }
        delete [] table;
    }
};

#endif // HASHTABLE_HPP

