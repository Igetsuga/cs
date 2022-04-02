// Сиразетдинов Рустем КМБО-01-21 Вариант- 18

#include <iostream>


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
		std::cout << "I has been called from: " << typeid(*this).name() << '\n';
	}

	virtual void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to:" << "a_ = " << a_ << '\n';
	}

	void GetMainValue() { std::cout << "(" << typeid(*this).name() << ") The Main Value is >> " << a_ << " <<" << '\n'; }
	void SetMainValue(int value) { a_ = value; }

	
};

class class_B1 : public class_A
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
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to: " << "a_ = " << a_ << '\n';
		std::cout << "                                    b1_ = " << b1_ << '\n';
	}

	
};

class class_B2 : public class_A
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
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to: " << "a_ = " << a_ << '\n';
		std::cout << "                                    b2_ = " << b2_ << '\n';
	}


};

class class_C : public class_B1, public class_B2
{
protected:
	int c_;
public:
	class_C(int value = 79) { c_ = value;  std::cout << "class_C has been created" << '\n'; }
	~class_C() { std::cout << '\n' << "class_C has been deleted"; }

	virtual void print()
	{
		std::cout << "\n" << typeid(*this).name() << '\n';
		std::cout << "Protected c_ is equal: " << c_ << '\n';
	}

	void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to: " << "b1_ = " << b1_ << '\n';
		std::cout << "                                    b2_ = " << b2_ << '\n';
	}

	void GetMainValue() { std::cout << "(" << typeid(*this).name() << ") The Main Value is >> " << c_ << " <<" << '\n'; }
	void SetMainValue(int value) { c_ = value; }


};

class class_D1 : virtual public class_C
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
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to: " << "b1_ = " << b1_ << '\n';
		std::cout << "                                     b2_ = " << b2_ << '\n';
		std::cout << "                                      c_ = " << c_ << '\n';
	}


};

class class_D2 : virtual public class_C
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


	void show()
	{
		std::cout << '\n' << "There " << typeid(*this).name() << " have access to: " << "b1_ = " << b1_ << '\n';
		std::cout << "                                     b2_ = " << b2_ << '\n';
		std::cout << "                                      c_ = " << c_ << '\n';
	}



};


int main()
{
	// Тестирование множественного наследования
	
	// Создание прародителя
	class_A parrent(56); parrent.print();
	

	// Создание наследника первого уровня от прародителя. Этот пример демонстрирует, что
	// хоть B1 и наследуется виртуально от прародителя, внутри себя он имеет своего
	// собственного прароделя, отличного от прародителя parrent, поэтому измение внутреннего
	// значения `a_` в B1 никак на внутреннее значение parrent не влияет. Это очевидно, это
	// совсем разные переменные
	class_B1 B1_0; B1_0.print();
	B1_0.SetMainValue(30); B1_0.show(); parrent.GetMainValue();

	std::cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Создание двух наследников первого уровня, которые наследуются НЕ ВИРТУАЛЬНО.
	// В результате сы получим две абсолютно независимые переменные.
	class_B1 B1_1;  class_B2 B2_1;
	B1_1.show(); B2_1.show();

	std::cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	class_C C_0; C_0.show();

	std::cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';
	// Создание двух наследников первого уровня, которые наследуются ВИРТУАЛЬНО.
	// В результате получим наследников с общим полем их базового класса. Т.е. если
	// изменим поле базового класса через один из них, то в другом объекте - наследнике 
	// первого уровня, тоже изменится это поле.
	class_D1 D1_0; D1_0.show();
	class_D2 D2_0; D2_0.show();

	D1_0.class_C::SetMainValue(8888888);

	D1_0.show(); D2_0.show();

	



	return 0;
}