// Сиразетдинов Рустем КМБО-01-21 Вариант- 18

#include <iostream>
#include <string>

class class_A
{
protected:
	int a_;
public:

	class_A(int value = 100) { a_ = value; std::cout << '\n' << "class_A has been created" << '\n'; }
	~class_A() { std::cout << '\n' << "class_A has been deleted" << '\n'; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "I has been called from  " << typeid(*this).name() << '\n';
	}

	virtual void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_";
	}

	void GetMainValue() { std::cout << "The Main Value is >> " << a_ << " <<" << '\n'; }

};

class class_B1 : public virtual class_A
{
protected:
	int b1_;
public:
	class_B1(int value = 99) : class_A(value) { b1_ = value;  std::cout << "class_B1 has been created" << '\n'; }
	~class_B1() { std::cout << '\n' << "class_B1 has been deleted"; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected b1_ is equal: " << b1_ << '\n';
	}

	virtual void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_ & b1_";
	}

	
};

class class_B2 : public virtual class_A
{
protected:
	int b2_;
public:
	class_B2(int value = 89) : class_A(value) { b2_ = value;  std::cout << "class_B2 has been created" << '\n'; }
	~class_B2() { std::cout << '\n' << "class_B2 has been deleted"; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected b2_ is equal: " << b2_ << '\n';
	}

	virtual void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_ & b2_";
	}


};

class class_C : public class_B1, public class_B2
{
protected:
	int c_;
public:
	class_C(int value = 79) : class_A(value) { c_ = value;  std::cout << "class_C has been created" << '\n'; }
	~class_C() { std::cout << '\n' << "class_C has been deleted"; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected b2_ is equal: " << a_ << '\n';
	}

	void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_ & b1_ & b2_";
	}


};

class class_D1 : public class_C
{
protected:
	int d1_;
public:
	class_D1(int value = 69) : class_C(value) { d1_ = value;  std::cout << "class_D1 has been created" << '\n'; }
	~class_D1() { std::cout << '\n' << "class_D1 has been deleted"; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected d1_ is equal: " << d1_ << '\n';
	}

	void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_ & b1_ & b2_ & c_";
	}


};

class class_D2 : public class_C
{
protected:
	int d2_;
public:
	class_D2(int value = 59) : class_C(value) { d2_ = value;  std::cout << "class_D2 has been created" << '\n'; }
	~class_D2() { std::cout << '\n' << "class_D2 has been deleted"; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected d2_ is equal: " << d2_ << '\n';
	}

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected d1_ is equal: " << d2_ << '\n';
	}

	void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_ & b1_ & b2_ & c_";
	}



};


int main()
{

	class_A parrent(56); parrent.print();

	class_B1 class_B1; class_B1.print();


	return 0;
}