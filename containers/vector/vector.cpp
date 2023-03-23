#include "vector.hpp"

namespace ft {

    /* Fill constructor */
    template<class T, class Alloc>
    vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc) :
        _allocator(alloc) {
        _size = n;
        _capacity = n;
        _data = _allocator.allocate(n);
        for (size_type i = 0; i < n; ++i) {
            _allocator.construct(_data + i, val);
        }
    }

    /* Range constructor */
    template<class T, class Alloc>
    template<class InputIterator>
    vector<T, Alloc>::vector(typename ft::enable_if<std::is_class<InputIterator>::value, InputIterator>::type first,
                             InputIterator last, const allocator_type &alloc) : _allocator(alloc) {
        _size = last - first;
        _data = _allocator.allocate(_size);
        for (_capacity(0); first != last; ++first, ++_capacity) {
            _allocator.construct(_data + _capacity, *first);
        }
    }

}
