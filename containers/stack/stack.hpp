#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef Container                                   container_type;
        typedef typename container_type::value_type         value_type;
        typedef typename container_type::reference          reference;
        typedef typename container_type::const_reference    const_reference;
        typedef typename container_type::size_type          size_type;

    protected:
        container_type _c;

    public:
        explicit stack (const container_type& ctnr = container_type()) : _c(ctnr) {}

        bool               empty() const { return this->_c.empty(); }
        size_type          size() const { return this->_c.size(); }
        reference          top() { return this->_c.back(); }
        const_reference    top() const { return this->_c.back(); }

        void               push(const value_type& x) { this->_c.push_back(x); }
        void               pop() { this->_c.pop_back(); }

        void               swap(stack& c) { this->_c.swap(c); }

        /* Non-member function overloads */
        friend bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) { return x._c == y._c; };
		friend bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) { return x._c < y._c; };
		friend bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) { return x._c != y._c;};
		friend bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) { return x._c > y._c; };
		friend bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) { return x._c >= y._c; };
		friend bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) { return x._c <= y._c; };

    };
}


#endif /* STACK_HPP */
