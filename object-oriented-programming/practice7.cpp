#include <cmath>
#include <iostream>
#include <stdarg.h>

template<class Type> Type max1 (int params_amount = 1, ...)
{
	auto* ptr = &params_amount;
	Type value_max = *( ptr += ( sizeof(Type) / sizeof(ptr) ) );

	for (int param_num = 2; param_num <= params_amount; param_num++)
	{
		ptr += ( sizeof(Type) / sizeof(ptr) );
		value_max = (value_max < *ptr) ? *ptr : value_max;
	}


	return value_max;
}

int main()
{
	std::cout << max1<int>(4, 1, 2, 3, 4) << '\n';
	std::cout << max1<double>(4, (double) 1, (double) 2, (double) 3, (double) 4) << '\n';
	std::cout << max1<double>(4, 1, 2, 3, 4) << '\n';
}