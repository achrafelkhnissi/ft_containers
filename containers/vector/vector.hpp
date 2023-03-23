#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "is_integral.hpp"

#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"
#include "reverse_iterator.hpp"
#include "const_reverse_iterator.hpp"

namespace ft {

    template <class T, class Alloc = std::allocator<T> >
    class vector {
    public:

        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename ft::iterator<value_type> iterator;
        typedef typename ft::const_iterator<value_type> const_iterator;
        typedef typename ft::reverse_iterator<value_type> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;


    private:
        size_type _size;
        size_type _capacity;
        pointer _data;
        allocator_type _allocator;

        void _reallocate(size_type n) {
            pointer tmp = _allocator.allocate(n);
            for (size_type i = 0; i < _size; ++i) {
                _allocator.construct(tmp + i, _data[i]);
            }
            _allocator.deallocate(_data, _capacity);
            _data = tmp;
            _capacity = n;
        }

        void _reallocate() {
            _reallocate(_capacity * 2);
        }

        void _deallocate() {
            for (size_type i = 0; i < _size; ++i) {
                _allocator.destroy(_data + i);
            }
            _allocator.deallocate(_data, _capacity);
        }

        void _clearVector() {
            for (size_type i(0); i < _size; ++i) {
                _allocator.destroy(_data + i);
            }
        }


    public:

        /* ------------------------- Constructors ------------------------- */

        /* Default constructor */
        explicit vector(const allocator_type& alloc = allocator_type()) :
                _size(0), _capacity(0), _data(NULL), _allocator(alloc) {}

        /* Fill constructor */
        explicit vector(size_type n, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type());

        /* Range constructor */
        template<class InputIterator>
        vector (typename ft::enable_if<std::is_class<InputIterator>::value, InputIterator>::type first,
				InputIterator last, const allocator_type& alloc = allocator_type());


        bool empty() const {
            return _size == 0;
        }

        size_type size() const {
            return _size;
        }
        size_type max_size() const {
            return _allocator.max_size();
        }

        size_type capacity() const {
            return _capacity;
        }

        reference operator[](size_type n) {
            return _data[n];
        }

        const_reference operator[](size_type n) const {
            return _data[n];
        }

        reference at(size_type n) {
            if (n >= _size) {
                throw std::out_of_range("vector::at");
            }
            return _data[n];
        }

        const_reference at(size_type n) const {
            if (n >= _size) {
                throw std::out_of_range("vector::at");
            }
            return _data[n];
        }



        const_iterator begin() const {
            return const_iterator(_data);
        }

        iterator begin() {
            return iterator(_data);
        }

        const_iterator end() const {
            return const_iterator(_data + _size);
        }

        iterator end() {
            return iterator(_data + _size);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }


        const_iterator cbegin() const {
            return const_iterator(_data);
        }

        const_iterator cend() const {
            return const_iterator(_data + _size);
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }





    };

}

#endif /* VECTOR_HPP */
