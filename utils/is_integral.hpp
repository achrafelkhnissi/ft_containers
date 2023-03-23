#ifndef FT_CONTAINERS_IS_INTEGRAL_HPP
#define FT_CONTAINERS_IS_INTEGRAL_HPP

#include <iostream>

namespace ft
{
    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator value_type() const { return value; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <bool is_integral, typename T>
    struct is_integral_helper {
        typedef T type;
        static const bool value = is_integral;
    };

    template <typename T>
    struct is_integral_type : public is_integral_helper<false, bool> {};

    template <>
    struct is_integral_type<bool> : public is_integral_helper<true, bool> {};

    template <>
    struct is_integral_type<char> : public is_integral_helper<true, char> {};

    template <>
    struct is_integral_type<signed char> : public is_integral_helper<true, signed char> {};

    template <>
    struct is_integral_type<unsigned char> : public is_integral_helper<true, unsigned char> {};

    template <>
    struct is_integral_type<short> : public is_integral_helper<true, short> {};

    template <>
    struct is_integral_type<unsigned short> : public is_integral_helper<true, unsigned short> {};

    template <>
    struct is_integral_type<int> : public is_integral_helper<true, int> {};

    template <>
    struct is_integral_type<unsigned int> : public is_integral_helper<true, unsigned int> {};

    template <>
    struct is_integral_type<long> : public is_integral_helper<true, long> {};

    template <>
    struct is_integral_type<unsigned long> : public is_integral_helper<true, unsigned long> {};

    template <>
    struct is_integral_type<long long> : public is_integral_helper<true, long long> {};

    template <>
    struct is_integral_type<unsigned long long> : public is_integral_helper<true, unsigned long long> {};

    template <typename T>
    struct is_integral : public is_integral_type<T> {};

    template <typename T>
    struct is_integral<const T> : public is_integral_type<T> {};

}

#endif //FT_CONTAINERS_IS_INTEGRAL_HPP
