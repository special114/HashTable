#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

/* File from HashTable project
 * author: Rafał Surdej
 */

#include <iostream>

template<class K, class V>
class Node;

template<class K, class V, class F>
class HashTable;

template<class K, class V, class F>
class Iterator_Hasz;

template<class K, class V, class F>
class Const_Iterator_Hasz
{
private:
    const HashTable<K, V, F>* h_table;
    const Node<K, V>* node_ptr;
public:

    Const_Iterator_Hasz(): h_table(nullptr), node_ptr(nullptr) {}
    Const_Iterator_Hasz(const HashTable<K, V, F>* h_tab, const Node<K, V>* n_ptr): h_table(h_tab), node_ptr(n_ptr) {}
    Const_Iterator_Hasz(const Iterator_Hasz<K, V, F>& other): h_table(other.h_table), node_ptr(other.node_ptr) {}
    Const_Iterator_Hasz(const Const_Iterator_Hasz& other): h_table(other.h_table), node_ptr(other.node_ptr) {}

    Node<K, V>& operator*() const
    {
        return *node_ptr;
    }
    Node<K, V>* operator->() const
    {
        return node_ptr;
    }
    Const_Iterator_Hasz& operator++()
    {
        size_t bucket_num = h_table->getBucketNum(node_ptr->key);
        node_ptr = node_ptr->next();
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
    Const_Iterator_Hasz operator++(int)
    {
        Const_Iterator_Hasz tmp(*this);
        ++(*this);
        return tmp;
    }
    bool operator==(const Const_Iterator_Hasz& tmp) const
    {
        return h_table == tmp.h_table && node_ptr == tmp.node_ptr;
    }
    bool operator!=(const Const_Iterator_Hasz& tmp) const
    {
        return !(*this == tmp);
    }
    friend std::ostream& operator<<(std::ostream& os, const Const_Iterator_Hasz& it)
    {
        os << it.node_ptr;
        return os;
    }
};







#endif // CONSTITERATOR_HPP

