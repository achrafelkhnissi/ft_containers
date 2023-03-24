#ifndef FT_CONTAINERS_CONST_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_CONST_REVERSE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{

    template<class Iterator>
    class const_reverse_iterator
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
        explicit const_reverse_iterator() : _ptr(nullptr) {}

        explicit const_reverse_iterator(Iterator ptr) : _ptr(ptr) {}

        /* ------------------------- COPY CONSTRUCTOR ------------------------- */
        const_reverse_iterator(const const_reverse_iterator &other) : _ptr(other._ptr) {}

        /* ------------------------- DESTRUCTOR ------------------------- */
        virtual ~const_reverse_iterator() {}

        /* ------------------------- ASSIGNATION OPERATOR ------------------------- */
        const_reverse_iterator &operator=(const const_reverse_iterator &other)
        {
            _ptr = other._ptr;
            return *this;
        }

        /* ------------------------- OPERATORS ------------------------- */
        const_reverse_iterator &operator++()
        {
            --_ptr;
            return *this;
        }

        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator tmp(*this);
            --_ptr;
            return tmp;
        }

        const_reverse_iterator &operator--()
        {
            ++_ptr;
            return *this;
        }

        const_reverse_iterator operator--(int) {
            const_reverse_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        reference operator*() const {
            return *(_ptr - 1);
        }

        pointer operator->() const {
            return _ptr - 1;
        }

        reference operator[](difference_type n) const {
            return *(_ptr - n - 1);
        }

        /* -------------------------- COMPARISON OPERATORS -------------------------- */
        bool operator==(const const_reverse_iterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const const_reverse_iterator &other) const {
            return _ptr != other._ptr;
        }

        bool operator<(const const_reverse_iterator &other) const {
            return _ptr > other._ptr;
        }

        bool operator<=(const const_reverse_iterator &other) const {
            return _ptr >= other._ptr;
        }

        bool operator>(const const_reverse_iterator &other) const {
            return _ptr < other._ptr;
        }

        bool operator>=(const const_reverse_iterator &other) const {
            return _ptr <= other._ptr;
        }

        /* -------------------------- ARITHMETIC OPERATORS -------------------------- */
        const_reverse_iterator operator+(difference_type n) const {
            return const_reverse_iterator(_ptr - n);
        }

        const_reverse_iterator operator-(difference_type n) const {
            return const_reverse_iterator(_ptr + n);
        }

        const_reverse_iterator &operator+=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        const_reverse_iterator &operator-=(difference_type n) {
            _ptr += n;
            return *this;
        }

    };

}

#endif //FT_CONTAINERS_CONST_REVERSE_ITERATOR_HPP
