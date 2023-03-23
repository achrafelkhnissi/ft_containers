#ifndef FT_CONTAINERS_CONST_ITERATOR_HPP
#define FT_CONTAINERS_CONST_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {

    template <class T>
    class const_iterator {
    public:
        typedef typename ft::iterator_traits<T *>::value_type value_type;
        typedef typename ft::iterator_traits<T *>::pointer pointer;
        typedef typename ft::iterator_traits<T *>::reference reference;
        typedef typename ft::iterator_traits<T *>::difference_type difference_type;
        typedef typename ft::iterator_traits<T *>::iterator_category iterator_category;

    private:
        pointer _ptr;

    public:

        /* ------------------------- CONSTRUCTORS ------------------------- */
        explicit const_iterator() : _ptr(nullptr) {}

        explicit const_iterator(pointer ptr) : _ptr(ptr) {}

        /* ------------------------- COPY CONSTRUCTOR ------------------------- */
        const_iterator(const const_iterator &other) : _ptr(other._ptr) {}

        /* ------------------------- DESTRUCTOR ------------------------- */
        virtual ~const_iterator() {}

        /* ------------------------- ASSIGNATION OPERATOR ------------------------- */
        const_iterator &operator=(const const_iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        /* ------------------------- OPERATORS ------------------------- */
        const_iterator &operator++() {
            ++_ptr;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        const_iterator &operator--() {
            --_ptr;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --_ptr;
            return tmp;
        }

        difference_type operator-(const const_iterator &other) const {
            return _ptr - other._ptr;
        }

        const_iterator operator+(difference_type n) const {
            return const_iterator(_ptr + n);
        }

        const_iterator operator-(difference_type n) const {
            return const_iterator(_ptr - n);
        }

        bool operator==(const const_iterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const const_iterator &other) const {
            return _ptr != other._ptr;
        }

        bool operator<(const const_iterator &other) const {
            return _ptr < other._ptr;
        }

        bool operator<=(const const_iterator &other) const {
            return _ptr <= other._ptr;
        }

        bool operator>(const const_iterator &other) const {
            return _ptr > other._ptr;
        }

        bool operator>=(const const_iterator &other) const {
            return _ptr >= other._ptr;
        }

        reference operator*() const {
            return *_ptr;
        }

        pointer operator->() const {
            return _ptr;
        }

        reference operator[](difference_type n) const {
            return _ptr[n];
        }

    };
}

#endif //FT_CONTAINERS_CONST_ITERATOR_HPP
