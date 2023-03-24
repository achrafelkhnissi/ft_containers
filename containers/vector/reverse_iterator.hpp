#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{

    template<class Iterator>
    class reverse_iterator
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
        explicit reverse_iterator() : _ptr(nullptr) {}

        explicit reverse_iterator(Iterator ptr) : _ptr(ptr) {}

        /* ------------------------- COPY CONSTRUCTOR ------------------------- */
        reverse_iterator(const reverse_iterator &other) : _ptr(other._ptr) {}

        /* ------------------------- DESTRUCTOR ------------------------- */
        virtual ~reverse_iterator() {}

        /* ------------------------- ASSIGNATION OPERATOR ------------------------- */
        reverse_iterator &operator=(const reverse_iterator &other)
        {
            _ptr = other._ptr;
            return *this;
        }

        /* ------------------------- OPERATORS ------------------------- */
        reverse_iterator &operator++()
        {
            --_ptr;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            --_ptr;
            return tmp;
        }

        reverse_iterator &operator--()
        {
            ++_ptr;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        reference operator*() const {
            return *(_ptr - 1);
        }

        pointer operator->() const {
            return _ptr - 1; // return _ptr;
        }

        reference operator[](difference_type n) const {
            return *(_ptr - n - 1);
        }

        /* ------------------------- COMPARISON OPERATORS ------------------------- */
        bool operator==(const reverse_iterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const reverse_iterator &other) const {
            return _ptr != other._ptr;
        }

        bool operator<(const reverse_iterator &other) const {
            return _ptr > other._ptr;
        }

        bool operator<=(const reverse_iterator &other) const {
            return _ptr >= other._ptr;
        }

        bool operator>(const reverse_iterator &other) const {
            return _ptr < other._ptr;
        }

        bool operator>=(const reverse_iterator &other) const {
            return _ptr <= other._ptr;
        }

        /* ------------------------- ARITHMETIC OPERATORS ------------------------- */
        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(_ptr - n);
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(_ptr + n);
        }

        reverse_iterator &operator+=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        reverse_iterator &operator-=(difference_type n) {
            _ptr += n;
            return *this;
        }

    };
}

#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP
