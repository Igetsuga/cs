// Сиразетдинов Рустем КМБО-01-21 Вариант- 18

#include <iostream>

using std::cin;
using std::cout;
// using std::vector;
// using std::string;
//
// using vi = vector<int>;
// using vvi = vector<vi>;
//
// using ll = long long;
//
// const ll mod = ll(1e9 + 7);

class class_A
{
protected:
	int a_;
public:

	class_A(int value = 100) { a_ = value; cout << '\n' << "class_A has been created" << '\n'; }
	~class_A() { cout << '\n' << "class_A has been deleted" << '\n'; }

	void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}

	void show()
	{
		cout << '\n' << "That object " << typeid(*this).name() << " have access to:" << "a_ = " << a_ << '\n';
	}

	void GetMainValue() { cout << "(" << typeid(*this).name() << ") The Main Value is >> " << a_ << " <<" << '\n'; }
	void SetMainValue(int value) { a_ = value; }

	
};

class class_B1 : public class_A
{
protected:
	int b1_;
public:
	class_B1(int value = 99) : class_A(value) { b1_ = value;  cout << "class_B1 has been created" << '\n'; }
	~class_B1() { cout << '\n' << "class_B1 has been deleted"; }

	void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}

	void show()
	{
		cout << '\n' << "That object  " << typeid(*this).name() << " have access to: " << "a_ = " << a_ << '\n';
		cout << "                                          b1_ = " << b1_ << '\n';
	}

	
};

class class_B2 : public class_A
{
protected:
	int b2_;
public:
	class_B2(int value = 89) : class_A(value) { b2_ = value;  cout << "class_B2 has been created" << '\n'; }
	~class_B2() { cout << '\n' << "class_B2 has been deleted"; }

	void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}

	void show()
	{
		cout << '\n' << "That object  " << typeid(*this).name() << " have access to: " << "a_ = " << a_ << '\n';
		cout << "                                          b2_ = " << b2_ << '\n';
	}


};

class class_C : public class_B1, public class_B2
{
protected:
	int c_;
public:
	class_C(int value = 79) { c_ = value;  cout << '\n' << "class_C has been created" << '\n'; }
	~class_C() { cout << '\n' << "class_C has been deleted"; }

	virtual void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}

	virtual void show()
	{
		cout << '\n' << "That object  " << typeid(*this).name() << " have access to: " << "b1_ = " << b1_ << '\n';
		cout << "                                           b2_ = " << b2_ << '\n';
		cout << "                                            c_ = " << c_ << '\n';
	}

	 virtual void GetMainValue() { cout << "(" << typeid(*this).name() << ") The Main Value is >> " << c_ << " <<" << '\n'; }
	 virtual void SetMainValue(int value) { c_ = value; }

	 virtual void ssp() { cout << '\n' << "HELLO!" << '\n'; }


};

class class_D1 : virtual public class_C
{
protected:
	int d1_;
public:
	class_D1(int value = 69) : class_C(value) { d1_ = value;  cout << "class_D1 has been created" << '\n'; }
	~class_D1() { cout << '\n' << "class_D1 has been deleted"; }

	virtual void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}

	void show()
	{
		cout << '\n' << "That object  " << typeid(*this).name() << " have access to: " << "b1_ = " << b1_ << '\n';
		cout << "                                            b2_ = " << b2_ << '\n';
		cout << "                                             c_ = " << c_ << '\n';
	}


};

class class_D2 : virtual public class_C
{
protected:
	int d2_;
public:
	class_D2(int value = 59) : class_C(value) { d2_ = value;  cout << "class_D2 has been created" << '\n'; }
	~class_D2() { cout << '\n' << "class_D2 has been deleted"; }

	void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}


	void show()
	{
		cout << '\n' << "That object  " << typeid(*this).name() << " have access to: " << "b1_ = " << b1_ << '\n';
		cout << "                                           b2_ = " << b2_ << '\n';
		cout << "                                            c_ = " << c_ << '\n';
	}



};

class class_E : public class_D1, public class_D2
{
protected:
	int e_;
public:
	class_E(int value = 49) { e_ = value;  cout << "class_E has been created" << '\n'; }
	~class_E() { cout << '\n' << "class_D2 has been deleted"; }

	void print()
	{
		cout << "\n" << typeid(*this).name() << '\n';
		cout << "I have been called from: " << typeid(*this).name() << '\n';
	}


	void show()
	{
		cout << '\n' << "That object  " << typeid(*this).name() << " have access to: " << "d1_ = " << d1_ << '\n';
		cout << "                                            d2_ = " << d2_ << '\n';
		cout << "                                             e_ = " << e_ << '\n';
	}



};

int main()
{
	// Давайте поиграем.

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';
	
	// Создание прародителя
	
	class_A A_0(56); A_0.print();
	
	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';
	
	class_B1 B_0(3589239);

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Создание наследника первого уровня, наследование НЕ ВИРТУАЛЬНОЕ.
	// Давайте посмотрим в консоль. Мы увидим, что вызывается два конструктора 
	// базового класса A(вызванные через B1 и через B2).
	// Т.е. было создано два объекта базового класса, и объекты
	// класса `class_C` будет содержать два подобъекта родительского класса `class_A`
	// Методами определенными в классе `class_C` можно пользоваться беспрепятсвенно,
	// они определены однозначно 
	
	class_C C_0; 
	C_0.show(); C_0.print(); 

	// Давайте теперь посмотрим на внутренности объекта `C_0`.
	// Я утверждаю, что там можно найти подобъекты классов `class_B1`, `class_B2` 
	// и 2 подобъекта класса `class_A`. Давайте посмотрим на них.
	// Метод GetMainValue() не переопределен в классах `class_B1` и `class_B2`,
	// поэтому вызывается именно метод родительского класса `class_A`, но через 
	// разных наследников 

	C_0.class_B1::print(); C_0.class_B1::show();
	C_0.class_B1::GetMainValue(); 

	C_0.class_B2::print(); C_0.class_B2::show();
	C_0.class_B2::GetMainValue();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';
	
	// Создание наследника первого уровня, наследование ВИРТУАЛЬНОЕ. 
	// Что теперь мы увидим в консоли? Создан только ОДИН подобъект класса `class_C`
	// Это произошло из-за того, что наследование по ветвям `class_C` <--- `class_D1` и
	// `class_C` <--- `class_D2` ВИРТУАЛЬНОЕ. Мы свободно можем пользоваться методами 
	// класс `class_C` в классе `class_E`. 

	class_E E_0(18); E_0.ssp();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';	

	// Указатели на базовые классы.
	
	class_A A(100);

	class_B1 B1(99); class_B2 B2(89);
	
	class_C C(79);
	
	class_D1 D1(69); class_D2 D2(59);

	class_E E(49);

	class_A* ptr_A = &A; class_C* ptr_C = &C;

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Вызов функции class_A::print()
	
	ptr_A = &A;
	ptr_A->print();

	// Методы классa `class_A` не объявлены виртуальными, поэтому будут вызваны именно они
	
	ptr_A = &B1; ptr_A->print();

	ptr_A = &B2; ptr_A->print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Вызов функции class_C::print()

	ptr_C = &C;
	ptr_C->print();

	// Методы классa `class_C` объявлены виртуальными, поэтому будут вызваны методы классов
	// на которые указывает указатель базоваго класса

	ptr_C = &D1; ptr_C->print(); 

	ptr_C = &D2; ptr_C->print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';



	
	return 0;
}