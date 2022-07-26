//#include <bits/stdc++.h>
 #include <iostream>
 #include <vector>
 #include <algorithm>
 #include <string>
 #include <bitset>
 #include <map>
 #include <unordered_map>
 #include <stack>
 #include <queue>
 #include <numeric>
 #include <iterator>
 #include <math.h>
 #include <set>
 #include <functional>
 #include <fstream>
 #include <chrono>
 #include <random>
 #include <assert.h>


#include <list>


#define all(x) begin(x), end(x)

using std::cin;
using std::cout;
using std::vector;
using std::string;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;


const ll mod = ll(1e9 + 7);


const auto ready = []()
{
	cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	return true;
}();

using namespace std;
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


// Сиразетдинов Рустем КМБО-01-21 Вариант- 24


// insert element in front of the list
template<class Type> void push_(list<Type>& list_, Type element)
{
	auto itt = list_.begin();

	while (itt != list_.end())
	{
		if (*itt > element) { break; }
		itt++;
	}

	list_.insert(itt, element);
}

// remove element under the index 
template<class Type> void pop_(list<Type>& list_, int index)
{
	auto itt = list_.begin() + index;
	list_.erase(itt);
}

// remove a chain of the elements
template<class Type> void pop_(list<Type> list_, int index_begin, int index_end)
{
	auto itt_begin = list_.begin() + index_begin;
	auto itt_end = list_.begin() + index_end;

	list_.erase(itt_begin, itt_end);
}

// print your list 
template<class Type> void print_(list<Type> list_)
{
	auto itt = list_.begin();

	std::cout << '\n' << ">>>>>";

	while (itt != list_.end())
	{
		std::cout << " " << *itt;
		itt++;
	}

	std::cout << "<<<<<" << '\n';
}

// predicate for 1.1
bool IsEvenFactorial(int value)
{
	int divider = 2;
	int isIncrement = 0;
	while (value > 1)
	{
		if (!(value % divider))
		{
			value /= divider;
			divider++;
			isIncrement = 1;
		}
		else { return false; }
	}

	if (isIncrement && !((divider - 1) % 2)) { return true; }


	return false;
}

// accept only factorials of even values
template<class Type> void filter(list<Type>& list_, bool(*function)(int))
{
	auto itt = list_.begin();
	
	while (itt != list_.end())
	{
		if (!function(*itt)) { list_.erase(itt); }
	}
}


int main()	
{
	list<int> list_ = { 33, 49, 71, 101, 119, 123, 203, 221, 249, 276,
		318, 334, 377, 414, 438, 463, 490, 509, 533, 548, 554, 575, 587,
		627, 635, 666, 688, 697, 715, 725, 732, 774, 799, 806, 807, 831,
		832, 836, 878, 887, 892, 954, 960, 967, 970, 970, 974, 975, 976, 981 };
	
	print_(list_);

	cout << "///////////////////////////////////////////////////////////////////" << '\n';

	// TEST: void insert(list<T>& lst, T element)

 	push_(list_, 3628800);   // = 10!
	push_(list_, 24);        // = 4!
	push_(list_, 479001600); // = 12!
	push_(list_, 40320);     // = 8!
	push_(list_, 720);       // = 6!
	push_(list_, 3628800);   // = 10!
	
	print_(list_);

	cout << "///////////////////////////////////////////////////////////////////" << '\n';

	// TEST: void pop_(list<Type>& list_, int index)  
	// TEST: void pop_(list<Type> list_, int index_begin, int index_end)
	
	pop_(list_, 8); // list_[8] = 
	pop_(list_, 8, 11);
	
	print_(list_); 

	cout << "///////////////////////////////////////////////////////////////////" << '\n';

	// TEST: filter(list<Type>& list_, bool(*function)(int))
	bool (*function)(int); function = IsEvenFactorial;

	filter(list_, function);
	
	print_(list_);

	cout << "///////////////////////////////////////////////////////////////////" << '\n';

	return 0;
}