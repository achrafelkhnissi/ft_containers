#ifndef FT_CONTAINERS_REVERSE_TREE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_TREE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
    template<class Iterator>
    class tree_reverse_iterator
    {
    public:
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

    private:
        Iterator _ptr;

    public:
        /* ------------------------- CONSTRUCTORS ------------------------- */
        explicit tree_reverse_iterator(Iterator ptr) : _ptr(ptr) {} // todo: check if you can change it with pointer

        /* ------------------------- COPY CONSTRUCTOR ------------------------- */
        tree_reverse_iterator(const tree_reverse_iterator &other) : _ptr(other._ptr) {}

        /* ------------------------- DESTRUCTOR ------------------------- */
        ~tree_reverse_iterator() {} // todo: check if you can change it to virtual?

        /* ------------------------- ASSIGNATION OPERATOR ------------------------- */
        tree_reverse_iterator &operator=(const tree_reverse_iterator &other)
        {
            _ptr = other._ptr;
            return *this;
        }

        /* ------------------------- OPERATORS ------------------------- */
        tree_reverse_iterator &operator++() { --_ptr; return *this; }
        tree_reverse_iterator operator++(int) { tree_reverse_iterator tmp(*this); --_ptr; return tmp; }
        tree_reverse_iterator &operator--() { ++_ptr; return *this; }
        tree_reverse_iterator operator--(int) { tree_reverse_iterator tmp(*this); ++_ptr; return tmp; }
        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        /* ------------------------- COMPARISON OPERATORS ------------------------- */
        bool operator==(const tree_reverse_iterator &other) const { return _ptr == other._ptr; }
        bool operator!=(const tree_reverse_iterator &other) const { return _ptr != other._ptr; }

    };

}

#endif //FT_CONTAINERS_REVERSE_TREE_ITERATOR_HPP
