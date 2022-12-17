#include <iostream>


void print (int* value) {
	std::cout << value << " ";
}




int main() {

	int x = 25;
	int &ref = x;
	int *ptr = &x;
	const int *cptr = &x;

	std::cout << &ref << " " << ptr << '\n';

	print(ptr);
	print(&ref);

	std::cout << '\n' << typeid(&ref).name() << " " << typeid(ptr).name() << '\n';	
	std::cout << '\n' << typeid(&ref).name() << " " << typeid(cptr).name() << '\n';	
	std::cout << '\n' << typeid(const_cast<int*>(cptr)).name();



}