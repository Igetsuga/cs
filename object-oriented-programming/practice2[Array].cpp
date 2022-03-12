// Сиразетдинов Рустем КМБО-01-21 Вариант- 24
// 
// quantity и capacity, должны быть по разному устроены: quantity- количество элементов в массиве
// capacity- память для этих элементов в байтах, тогда capacity = sizeof(type) * quantity
// 
// не понятно как работает double* ptr; 
// 
// не понятно как работает ptr = new double[Dimension]
// 
// строка 66- деконструктор, если бы мы не проверяли условие (ptr != NULL), то 
// что тогда удаляла бы функция delete ?

// количество элементов в массиве int arrSize = sizeof(arr)/sizeof(arr[0]);
// или std::array::size 

#include <iostream>
#include <vector>

using namespace std;

class ArrayParent
{
protected:

	int capacity; // количество памяти для массива

	int quantity; // количество элементов в массиве - сколько памяти используем

	double* ptr; // указатель на ячейки в памити, которые все вместе образуют массив
	// поскольку для массива необходима непрерывная область памяти, то где гарнтия, что указатель ptr
	// дает нам именно последовательные ячейки памяти?

public:
	//конструкторы и деструктор
	
	// default constructor --> capacity = 100; quantity = 0; 
	ArrayParent(int Dimension = 100)
	{
		cout << "\n" << "ArrayParent constructor";

		capacity = Dimension;
		quantity = 0;
		ptr = new double[Dimension]; // new- выделение оперативной памяти delete- удаление элементов из памяти
	}


	// конструктор принимает существующий массив --> создает копию массива, но с большей capacity
	ArrayParent(double* array_exist, int len)
	{

		cout << "\n" << "ArrayParent constructor";

		capacity = (len >= 1000) ? 2 * len : 1000; // увеличиваем выделяемую память для того, чтобы потом
												   // можно было добавить в него элементы
		ptr = new double[capacity];

		for (int itt = 0; itt < len; itt++)
		{
			ptr[itt] = array_exist[itt];
		}
	}

	// консруктор копии существующего массива
	ArrayParent(const ArrayParent& P)
	{
		capacity = P.capacity;
		quantity = P.quantity;
		ptr = new double[capacity];
		for (int itt = 0; itt < P.quantity; itt++)
		{
			ptr[itt] = P.ptr[itt];
		}
	}

	// деструктор
	// NUll - такой указатель при сравнении не будет равен любому «корректному»
	// указателю. То есть, можно считать, что нулевой указатель не содержит корректного 
	// адреса в памяти, но поскольку NULL разворачивается в 0, то будем использвать nullptr
	~ArrayParent()
	{
		cout << "\n" << "ArrayParent destructor";
		if (ptr != nullptr) // если под массив была выделена памиять через type* ptr; то ptr != NULL
		{
			delete[] ptr; // очищение памяти, которая ранее была занята элементами массива
			ptr = nullptr;
		}
	}

	//обращение к полям
	int get_сapacity() { return capacity; }

	int get_size() { return quantity; }

	double get_element(int index)
	{
		if (index >= 0 && index < quantity) { return ptr[index]; }
		else {
			//сгенерировать исключение, если индекс неправильный
			return -1;
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity) { ptr[index] = value; }
		else {
			//сгенерировать исключение, если индекс неправильный
		}
	}


	//добавление в конец нового значения
	void push(double value) 
	{
		if (sizeof(value) == sizeof(ptr[0])) {

			if (quantity < capacity) // нужно реализовать другую проверку через занятую память строки 2-4
			{
				ptr[quantity++] = value;
				//quantity++;
			}
			else {
				capacity += sizeof(value);
				ptr[quantity++] = value;
			}
		}
	}

	//удаление элемента с конца
	void remove_last_element()
	{
		if (quantity >= 0) {
			ptr[--quantity] = 0; // именно --quantity
			quantity--;
		}
		//что делать, если паямть не 
		//что делаем, если пуст?
	}

	double& operator[](int index) // почему ссылка?
	{
		if (index < quantity) { return ptr[index]; }
		// else { return -1; }
		//перегрузка оператора []
	}

	ArrayParent& operator=(const vector<double>& vector) // что делать, = идет последовательно
	{
		ArrayParent(sizeof(vector));
		capacity = sizeof(vector) / sizeof(vector[0]) * vector.size();
		quantity = vector.size();
		for (int itt = 0; itt < quantity; itt++) {
			ptr[itt] = vector[itt];
		}
		return *this;
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
	}

	ArrayParent(const vector<double>& vector) // не понятно
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	}

	void print()
	{
		cout << "\n" << "MyArrParent, size: " << quantity << ", values: {";
		for (int itt = 0; itt < quantity; itt++)
		{
			cout << ptr[itt];
			if (itt != quantity - 1)
				cout << ", ";
		}
		cout << "}";
	}

	ArrayParent operator=(const ArrayParent& P) //ArrayParent& operator=(const ArrayParent& P)
	{
		if (capacity == P.capacity)
		{
			quantity = P.quantity;
			for (int itt = 0; itt < quantity; itt++)
			{
				ptr[itt] = P.ptr[itt];
			}
		} else { 
			capacity += ( P.capacity - capacity );

			quantity = P.quantity;
			for (int itt = 0; itt < quantity; itt++)
			{
				ptr[itt] = P.ptr[itt];
			}
		}
		return (*this);
	}

};

class MyArrayChild : public ArrayParent //
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : ArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	//void RemoveAt(int index = -1);

	//поиск элемента
	int IndexOf(double value, bool FindFromStart = true)
	{
		if (FindFromStart)
		{
			for (int i = 0; i < quantity; i++)
			{
				if (value == ptr[i]) { return i; }
			}
		}
		else
		{
			for (int i = quantity - 1; i > 0; i--)
			{
				if (value == ptr[i]) { return i; }
			}
		}
		return -1;
	}

	//вставка элемента
	void InsertAt(double value, int index = -1)
	{
		if (index == -1 || index >= quantity) { push(value); }
		else
		{

			for (int i = quantity; i > index; i--)
			{
				ptr[i] = ptr[i - 1];
			}
			ptr[index] = value;
			quantity++;
		}
	}
}

//выделение подпоследовательности
//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

//добавление элемента в конец
//operator + ?

};

int main()
{
	ArrayParent arr;
	if (true)
	{
		MyArrayChild arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			arr.push(i + 1);
		}
		arr.print();
		cout << "\n";
		//cout << "\n" << sp << "\n";
	}
	char c; cin >> c;
	return 0;
}

