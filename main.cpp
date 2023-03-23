#include <iostream>
#include <fstream>
#include <vector>
#include "vector.hpp"

/*
 * TODO:
 * 1. std::allocator
 * 2. What is the difference between allocation and construction
 * 3. ::operator new/delete()
 * 4. inline functions
 * 5. std::numeric_limits<size_type>::max();
 *
 */

#define SIZE 5

/* TEST MACROS */
//#define ALL
#define VECTOR
//#define STACK
//#define MAP

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool)
{
    fs << "\nBool result : \n";
    fs << " - STL : " << (stl_bool ? "true" : "false") << std::endl;
    fs << " - FT  : " << (ft_bool ? "true" : "false") << std::endl;

    return (stl_bool == ft_bool);
}

int main() {

#if defined(VECTOR) || defined(ALL)
//	test_vector();
    std::vector<int> a;
    std::vector<int>::const_iterator i;

    i = a.begin();
	std::cout << "Vector" << std::endl;

//	std::cout << *v.end() << std::endl;
#elif defined(STACK) || defined(ALL)
//	test_stack();
	std::cout << std::endl;
#elif defined(MAP) || defined(ALL)
//    test_map();

#else

#endif

	return 0;
}
