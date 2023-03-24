#ifndef FT_CONTAINERS_TREE_ITERATOR_HPP
#define FT_CONTAINERS_TREE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
    template<class T, class NodePtr, class Alloc = std::allocator<T>, class DiffType = typename Alloc::difference_type>
    class tree_iterator
    {
    public:
        typedef T value_type;
        typedef NodePtr pointer;
        typedef T &reference;
        typedef DiffType difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        pointer _ptr;

    public:
        /* ------------------------- CONSTRUCTORS ------------------------- */
        explicit tree_iterator( pointer ptr = nullptr ) : _ptr(ptr) {}

        /* ------------------------- COPY CONSTRUCTOR ------------------------- */
        tree_iterator& operator=( const tree_iterator& other ) {
            _ptr = other._ptr;
            return *this;
        }

        /* ------------------------- DESTRUCTOR ------------------------- */
        ~tree_iterator() {}

        /* ------------------------- OPERATORS ------------------------- */
        reference operator*() const { return _ptr->value; }
        pointer operator->() const { return _ptr; }
        tree_iterator& operator++() { _ptr = _ptr->next(); return *this; }
        tree_iterator operator++(int) { tree_iterator tmp(*this); _ptr = _ptr->next(); return tmp; }
        tree_iterator& operator--() { _ptr = _ptr->prev(); return *this; }
        tree_iterator operator--(int) { tree_iterator tmp(*this); _ptr = _ptr->prev(); return tmp; }

        /* ------------------------- COMPARISON OPERATORS ------------------------- */
        bool operator==( const tree_iterator& other ) const { return _ptr == other._ptr; }
        bool operator!=( const tree_iterator& other ) const { return _ptr != other._ptr; }

    };
}

#endif //FT_CONTAINERS_TREE_ITERATOR_HPP
