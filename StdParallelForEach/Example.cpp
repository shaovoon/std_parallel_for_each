
#include "Example.h"
#include <iostream>
#include "std_parallel_for_each.h"

void Example::Run()
{
	int arr[5000];

	loop::for_each(loop::execution::par, std::begin(arr), std::end(arr), [](int& n) { n = 3; });

	std::cout << "arr[5]: " << arr[5] << "\n";

}