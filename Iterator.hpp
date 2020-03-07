#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* File from HashTable project
 * author: Rafał Surdej
 */

#include <cstddef>
#include <iterator>

#include "HashTable.hpp"
#include "ConstIterator.hpp"

template<class K, class V, class F>
class Iterator_Hasz
{
private:
    HashTable<K, V, F>* h_table;
    Node<K, V>* node_ptr;

    friend class Const_Iterator_Hasz<K, V ,F>;
public:

    Iterator_Hasz(): h_table(nullptr), node_ptr(nullptr) {}
    Iterator_Hasz(HashTable<K, V, F>* h_tab, Node<K, V>* n_ptr): h_table(h_tab), node_ptr(n_ptr) {}
    Iterator_Hasz(const Iterator_Hasz& other): h_table(other.h_table), node_ptr(other.node_ptr) {}

    Node<K, V>& operator*() const
    {
        return *node_ptr;
    }
    Node<K, V>* operator->() const
    {
        return node_ptr;
    }
    Iterator_Hasz& operator++()
    {
        size_t bucket_num = h_table->getBucketNum(node_ptr->key);
        node_ptr = node_ptr->next;
        if (!node_ptr)                   // if it is the last element in this bucket, we're looking for a next node
                                         // in subsequent table cells
        {
            for (size_t i = bucket_num + 1; i < h_table->getNumOfBuckets(); ++i)
            {
                if (h_table->getTableElement(i))
                {
                    node_ptr = h_table->getTableElement(i);
                    return *this;
                }
            }
        }
        return *this;
    }
    Iterator_Hasz operator++(int)
    {
        Iterator_Hasz tmp(*this);
        ++(*this);
        return tmp;
    }
    bool operator==(const Iterator_Hasz& tmp) const
    {
        return h_table == tmp.h_table && node_ptr == tmp.node_ptr;
    }
    bool operator!=(const Iterator_Hasz& tmp) const
    {
        return !(*this == tmp);
    }
    Iterator_Hasz operator=(const Iterator_Hasz& other)
    {
        h_table = other.h_table;
        node_ptr = other.node_ptr;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Iterator_Hasz& it)
    {
        os << it.node_ptr;
        return os;
    }
};




#endif // ITERATOR_HPP

