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

/* todo: remove duplicate code and make it more readable */
/* todo: add exception handling ? */
/* todo: add more tests */

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
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
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
                        const allocator_type& alloc = allocator_type()) :
                _size(n), _capacity(n), _allocator(alloc) {
            _data = _allocator.allocate(_capacity);
            for (_size = 0; _size < _capacity; ++_size) {
                _allocator.construct(_data + _size, val);
            }
        }

        /* Range constructor */
        template<class InputIterator>
        vector (typename ft::enable_if<std::is_class<InputIterator>::value, InputIterator>::type first,
				InputIterator last, const allocator_type& alloc = allocator_type() ) :
                _allocator(alloc) {
            _size = last - first;
            _data = _allocator.allocate(_size);
            for (_capacity = 0; first != last; ++first, ++_capacity) {
                _allocator.construct(_data + _capacity, *first);
            }
        }

        /* Copy constructor */
        vector(const vector& x) {
            *this = x;
        }

        /* Copy Assignment operator */
        vector& operator=(const vector& x) {
            if (this != &x) {
                _size = x._size;
                _capacity = x._capacity;
                _allocator = x._allocator;
                _data = _allocator.allocate(_capacity);
                for (size_type i = 0; i < _size; ++i) {
                    _allocator.construct(_data + i, x._data[i]);
                }
            }
            return *this;
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


        /* ------------------------- Iterators ------------------------- */
        iterator begin() { return iterator(_data); }
        const_iterator cbegin() const { return const_iterator(_data); }

        iterator end() { return iterator(_data + _size); }
        const_iterator cend() const { return const_iterator(_data + _size); }

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

        /* ------------------------- Capacity ------------------------- */
        size_type size() const { return _size; }
        size_type max_size() const { return _allocator.max_size(); }
        size_type capacity() const { return _capacity; }
        bool empty() const { return _size == 0; }

        void reserve(size_type n) {
            if (n > _capacity) {
                _reallocate(n);
            }
        }

        void resize(size_type n, value_type val = value_type()) {
            if (n > _size) {
                if (n > _capacity) {
                    _reallocate(n);
                }
                for (size_type i = _size; i < n; ++i) {
                    _allocator.construct(_data + i, val);
                }
            } else if (n < _size) {
                for (size_type i = n; i < _size; ++i) {
                    _allocator.destroy(_data + i);
                }
            }
            _size = n;
        }

        void shrink_to_fit() {
            if (_size < _capacity) {
                _reallocate(_size);
            }
        }

        /* ------------------------- Element access ------------------------- */
        reference front() { return _data[0]; }
        const_reference front() const { return _data[0]; }
        reference back() { return _data[_size - 1]; }
        const_reference back() const { return _data[_size - 1]; }

        /* ------------------------- Modifiers ------------------------- */
        template<class InputIterator>
        void assign (typename ft::enable_if<std::is_class<InputIterator>::value, InputIterator>::type first,
                     InputIterator last) {
            _clearVector();
            difference_type distance = last - first;
            if (distance > static_cast<difference_type>(_capacity)) {
                pointer tmp = _allocator.allocate(distance);
                for (size_type i = 0; first != last; ++first, ++i) {
                    _allocator.construct(tmp + i, *first);
                }
                _allocator.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = _size = distance;
            } else {
                for (_size = 0; first != last; ++first, ++_size) {
                    _allocator.construct(_data + _size, *first);
                }
            }
        }

        void assign (size_type n, const value_type& val) {
            _clearVector();
            if (n > _capacity) {
                pointer tmp = _allocator.allocate(n);
                for (size_type i = 0; i < n; ++i)
                    _allocator.construct(tmp + i, val);

                _allocator.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = _size = n;
            } else {
                for (_size = 0; _size < n; ++_size)
                    _allocator.construct(_data + _size, val);
            }
        }

        void push_back(const value_type& val) {
            if (_size < _capacity) {
                _allocator.construct(_data + _size, val);
            } else if (!_capacity) {
                _capacity = 1;
                _data = _allocator.allocate(_capacity);
                _allocator.construct(_data, val);
            } else {
                pointer tmp = _allocator.allocate(_capacity * 2);
                for (size_type i = 0; i < _size; ++i)
                    _allocator.construct(tmp + i, _data[i]);

                _allocator.construct(tmp + _size, val);
                _allocator.deallocate(_data, _capacity);
                _capacity *= 2;
                _clearVector();
                _data = tmp;
            }
            ++_size;
        }

        void pop_back() {
            if (_size > 0) {
                _allocator.destroy(_data + _size - 1);
                --_size;
            }
        }

        template<class InputIterator>
        void insert (iterator position, typename ft::enable_if<std::is_class<InputIterator>::value,
                     InputIterator>::type first, InputIterator last) {
            difference_type length = last - first;
            size_type pos = position - begin();

            if (_size + length >= _capacity) {

                pointer tmp = _allocator.allocate(_size + length);
                for (size_type i = 0; i < _size + length; ++i) {
                    if (i < pos) {
                        _allocator.construct(tmp + i, _data[i]);
                    } else if (i >= pos && i < pos + length) {
                        _allocator.construct(tmp + i, *first);
                        ++first;
                    } else {
                        _allocator.construct(tmp + i, _data[i - length]);
                    }
                }
                _clearVector();
                _allocator.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = _size + length;
            } else if (_size + length < _capacity) {
                for (difference_type i = 0; i < length; ++i, ++pos) {
                    pointer last_element = _data + (_size - i - 1);
                    _allocator.construct(last_element + length, *last_element);
                    _allocator.construct(_data + pos, *(first++));
                }
            }
            _size += length;
        }

        void insert (iterator position, size_type n, const value_type& val) {
            size_type pos = position - begin();
            if (_size + n > _capacity) {
                _reallocate(_size + n);
            }
            for (size_type i = _size; i > pos; --i) {
                _allocator.construct(_data + i + n - 1, _data[i - 1]);
                _allocator.destroy(_data + i - 1);
            }
            for (size_type i = 0; i < n; ++i) {
                _allocator.construct(_data + pos + i, val);
            }
            _size += n;
        }

        iterator insert (iterator position, const value_type& val) {
            size_type pos = position - begin();
            if (_size + 1 >= _capacity) {
                pointer tmp = _allocator.allocate(_capacity * 2);
                for (size_type i(0), j(0); i < _size + 1; ++i) {

                    if (i >= pos && i - pos < 1)
                        _allocator.construct(tmp + i, val);
                    else
                        _allocator.construct(tmp + i, _data[j++]);
                }
                _clearVector();
                _allocator.deallocate(_data, _capacity);
                _data = tmp;
                _capacity *= 2;
            } else if (_size + 1 < _capacity) {
                for (size_type i(0); i < 1; ++i, ++pos) {
                    pointer last_element = _data + (_size - i - 1);
                    _allocator.construct(last_element + 1, *last_element);
                    _allocator.construct(_data + pos, val);
                }
            }
            ++_size;
            return position;
        }

        void clear() {
            for (size_type i = 0; i < _size; ++i) {
                _allocator.destroy(_data + i);
            }
            _size = 0;
        }

        void swap (vector& x) {
            vector tmp = x;
            x = *this;
            *this = tmp;
        }

        void swap (value_type& x, value_type& y) {
            value_type tmp = x;
            x = y;
            y = tmp;
        }

        // TODO: compare it with the old one
        iterator erase (iterator position) {
            size_type pos = position - begin();
            for (size_type i = pos; i < _size - 1; ++i) {
                _allocator.construct(_data + i, _data[i + 1]);
                _allocator.destroy(_data + i + 1);
            }
            _allocator.destroy(_data + _size - 1);
            --_size;
            return iterator(_data + pos);
        }

        iterator erase (iterator first, iterator last) {
            size_type pos = first - begin();
            size_type n = last - first;
            for (size_type i = pos; i < _size - n; ++i) {
                _allocator.construct(_data + i, _data[i + n]);
                _allocator.destroy(_data + i + n);
            }
            for (size_type i = 0; i < n; ++i) {
                _allocator.destroy(_data + _size - 1 - i);
            }
            _size -= n;
            return iterator(_data + pos);
        }

        /* ------------------------- Allocator ------------------------- */
        allocator_type get_allocator() const {
            return _allocator;
        }

    }; /* class vector */

    /* ------------------------- Non-member function overloads ------------------------- */
    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
        x.swap(y);
    }

}

#endif /* VECTOR_HPP */
