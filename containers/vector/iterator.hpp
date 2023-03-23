#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {


    template<class T>
    class iterator {

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
        explicit iterator() : _ptr(nullptr) {}

        explicit iterator(pointer ptr) : _ptr(ptr) {}

        /* ------------------------- COPY CONSTRUCTOR ------------------------- */
        iterator(const iterator &other) : _ptr(other._ptr) {}

        /* ------------------------- DESTRUCTOR ------------------------- */
        virtual ~iterator() {}

        /* ------------------------- ASSIGNATION OPERATOR ------------------------- */
        iterator &operator=(const iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        /* ------------------------- OPERATORS ------------------------- */
        iterator &operator++() {
            ++_ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        iterator &operator--() {
            --_ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp(*this);
            --_ptr;
            return tmp;
        }

        difference_type operator-(const iterator &other) const {
            return _ptr - other._ptr;
        }

        iterator operator+(difference_type n) const {
            return iterator(_ptr + n);
        }

        iterator operator-(difference_type n) const {
            return iterator(_ptr - n);
        }

        iterator &operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        iterator &operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        reference operator*() const {
            return *_ptr; // return static_cast<reference>(*_ptr); ?
        }

        pointer operator->() const {
            return _ptr;
        }

        reference operator[](difference_type n) const {
            return _ptr[n];
        }

        bool operator==(const iterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const iterator &other) const {
            return _ptr != other._ptr;
        }

        bool operator<(const iterator &other) const {
            return _ptr < other._ptr;
        }

        bool operator<=(const iterator &other) const {
            return _ptr <= other._ptr;
        }

        bool operator>(const iterator &other) const {
            return _ptr > other._ptr;
        }

        bool operator>=(const iterator &other) const {
            return _ptr >= other._ptr;
        }

    };

}

#endif //FT_CONTAINERS_ITERATOR_HPP
