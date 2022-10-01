#include <algorithm>
#include <iostream>
#include <memory>
#define nline '\n'

class Type {
public:
	Type (int x = 1, int y = 2) {
		a = x; b = y;
	}
	~Type() = default;
	
	void SetValues(int x, int y) {
		a = x, b = y;
	};

	void print() {
		std::cout << '\n' << "(" << a << ";" << b << ")" << nline; 
	}
private:
int a;
int b;
};

int main() {
	auto ptr1 = std::make_unique<Type>(22,11);
	/* auto ptr2 = std::move(ptr1); */
	/* ptr2->print(); */
	auto ptr = [gg = std::move(ptr1)]() {
		gg->SetValues(24, 352);
		gg->print();
	};
	/* ptr1->print(); */

}
