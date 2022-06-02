#include <cmath>
#include <limits>
#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

template<class Type> Type max1 (int params_amount = 1, ...)
{
	int *ptr = &params_amount; std::cout << ">>> " << ptr << " : " << *ptr << typeid(*ptr).name() << '\n';
	auto* pp = ptr + 1; std::cout << ">>>>>> " << pp << " : " << *pp << typeid(*pp).name() << '\n';
	// ptr += 1;
	// Type value_max = *( ptr += ( sizeof(Type) / sizeof(int) ) );
	Type value_max = *(ptr += 2);
	// Type value_max = *++ptr; std::cout << ">>> " << ptr << " : " << *ptr << typeid(*ptr).name() << '\n';
	for (int param_num = 2; param_num <= params_amount; param_num++)
	{
		//ptr += ( sizeof(Type) / sizeof(int) );
		// ptr++;
		ptr += 2;
		std::cout << ">>> " << ptr << " : " << *ptr << typeid(*ptr).name() << '\n';
		value_max = (value_max < *ptr) ? *ptr : value_max;
	}


	return value_max;
}

template<class Type> double harmonic_mean(Type param, ...)
{
	double sum_result = 0;
	int param_amount = 0;

	Type* pointer = &param;

	while ( (Type) *pointer - std::numeric_limits<Type>::epsilon() > 0)
	{
		sum_result += (double) 1 / (*pointer) ;
		param_amount++;
		pointer++;
	}


	return (param_amount / sum_result);
}






int main()
{
	std::cout << harmonic_mean<int>(1, 2, 3, 4, 5, 6, 7, 0) << '\n';

	std::cout << harmonic_mean<double>(235.34234, 329.90, 24.0, 4.0, 912.11, 1.0, 0) << '\n';




	//std::cout << max1<int>(4, 1, 2, 3, 4) << '\n';
	//std::cout << max1<double>(4, 1.0, 2.0, 3.0, 4.0) << '\n';
	//std::cout << max1<double>(4, 100, 5, 10, 4) << '\n';
	//std::cout << max1<double>(4, 1, 2, 3, 4) << '\n';
	//
	//std::cout << max1<double>(4, (double)1, (double)2, (double)3, (double)4) << '\n';
}


