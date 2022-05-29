#include <cmath>
#include <iostream>
#include <stdarg.h>

template<class Type> Type max1 (int params_amount = 1, ...)
{
	auto* ptr = &params_amount;
	// std::cout << ">>> " << ptr << " : " << *ptr << typeid(*ptr).name() << '\n';
	/*ptr += 2;
	std::cout << ">>> " << ptr << " : " << *ptr << typeid(*ptr).name() << '\n';*/
	Type value_max = *(++ptr);
	// Type &;
	// static_cast<Type>(++(++ptr));
	

	char is_next = 'n';
	while (is_next == 'n')
	{
		std::cout << ptr << " : " << *ptr << " " << typeid(*ptr).name() << '\n';
		ptr += 1;
		std::cin >> is_next;
	}


	//for (int param_num = 2; param_num < params_amount; param_num++)
	//{
	//	iterator++;
	//	value_max = (value_max < *iterator) ? *iterator : value_max;
	//}


	return value_max;
}

int main()
{
	std::cout << max1<int>(4, 1, 2, 3, 4) << '\n';
	std::cout << max1<double>(4, (double) 1, (double) 2, (double) 3, (double) 4) << '\n';
	std::cout << max1<double>(4, 1, 2, 3, 4) << '\n';
}