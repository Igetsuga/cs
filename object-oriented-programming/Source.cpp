#include <iostream>
#include <stdarg.h>


//template <class Type> class Fraction
//{
//public:
//	Fraction (Type numerator = 1, Type denominator = 1)
//	{
//		numerator_ = numerator;
//		denominator_ denominator;
//	}
//
//	~Fraction() {};
//
//	Type GetNumerator() { return numerator_; }
//
//	Type GetDenominator() { return denominator_; }
//private:
//	Type numerator_;
//	Type denominator_;
//};



template <class Type> Type Max1 (int amount_params, ...)
{
	Type *ptr = &amount_params;

	
	Type value_max = *++(++ptr);

	for (int value_num = 0; value_num < amount_params - 1; value_num++)
	{
		ptr+=2;
		value_max = (value_max < *ptr) ? *ptr : value_max;
	}


	return value_max;
}



double multiplication (double value, ...)
{
	if (value == 0.0) { return 0; }

	double *ptr = &value;
	double result = static_cast<double>(value);

	while (*++ptr != 0.0) 
	{
		result *= static_cast<double>(*ptr);
		std::cout << typeid(*ptr).name() << " : " << *ptr << '\n';
	}

	std::cout << '\n';
	return result;
}



//void prinf_ (char *c)
//{
//	va_list l;
//	va_start (l,c);
//	// const_cast
//	char *ptr = c;
//	int n_value;
//	Fraction<int> F;
//	while (*c) // while (*s != '\0')
//	{
//		if (*ptr == '%')
//		{
//			switch (*ptr)
//			{
//			case 'd' :
//				n_value = va_arg(l, int);
//				printf("%d", n_value);
//				break;
//			case 'F' :
//				F = va_arg(l, Fraction<int>);
//				printf("%d/%d", F.GetNumerator(), F.GetDenominator());
//				break;
//			default:
//				printf("%");
//				printf("%c", *ptr);
//				break;
//			}
//
//		}
//
//	}
//	va_end(l);
//}


int main()
{
	std::cout << Max1<int>(3, 3, 5, 500) << '\n';

	std::cout << multiplication(4.0, 6.0, 2.0, 0.0);
}