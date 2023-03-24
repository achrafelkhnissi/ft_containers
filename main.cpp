#include <iostream>
#include <vector>
#include "tester.hpp"

/*
 * TODO:
 * 1. std::allocator
 * 2. What is the difference between allocation and construction
 * 3. ::operator new/delete()
 * 4. inline functions
 * 5. std::numeric_limits<size_type>::max();
 *
 */

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool)
{
    fs << "\nBool result : \n";
    fs << " - STL : " << (stl_bool ? "true" : "false") << std::endl;
    fs << " - FT  : " << (ft_bool ? "true" : "false") << std::endl;

    return (stl_bool == ft_bool);
}

int main() {

    test_vector();
    std::cout << std::endl;

	test_stack();
	std::cout << std::endl;

	return 0;
}
