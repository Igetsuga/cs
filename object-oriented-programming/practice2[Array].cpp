// Сиразетдинов Рустем КМБО-01-21 Вариант- 24


#include <iostream>
#include <vector>

using namespace std;

class ArrayMaster
{
protected:

	int capacity; // amount of memory for the array

	int quantity; // number of elements in the array < `capacity` 

	double* ptr; // a pointer to the cells in memory that all together form an array

public:
	
	// default constructor --> `capacity` = 100; `quantity` = 0; 
	ArrayMaster(int Dimension = 100)
	{
		cout << "\n" << "default constructor";

		capacity = Dimension;
		quantity = 0;
		ptr = new double[Dimension]; 
	}

	// constructor_of_copy --> copy of array 
	ArrayMaster(const ArrayMaster& array_existing)
	{
		capacity = array_existing.capacity;
		quantity = array_existing.quantity;
		ptr = new double[capacity];

		for (int itt = 0; itt < array_existing.quantity; itt++)
		{
			ptr[itt] = array_existing.ptr[itt];
		}
	}

	// constructor_1 --> copy but `capacity` is bigger
	ArrayMaster(double* array_existing, int len) // чем это отличается от 60 строчки
	{

		cout << "\n" << "constructor_1";

		capacity = (len >= 1000) ? 2 * len : 1000; // increase `copy.capacity` to adding elements after

		ptr = new double[capacity];

		for (int itt = 0; itt < len; itt++)
		{
			ptr[itt] = array_existing[itt];
		}
	}

	// constructor_2 --> copy of array
	ArrayMaster(const vector<double>& vector) // не понятно
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
		cout << "\n" << "constructor_2";
		capacity = sizeof(vector);
		quantity = vector.size();
		ptr = new double[capacity];

		for (int itt = 0; itt < vector.size(); itt++)
		{
			ptr[itt] = vector[itt];
		}

		// return (*this); ????
	}



	// destructor
	~ArrayMaster()
	{
		cout << "\n" << "ArrayMaster has been deleted";

		if (ptr != nullptr) 
		{
			delete[] ptr; 
			ptr = nullptr;
		}
	}




	// get... & set...
	int get_сapacity() { return capacity; }

	int get_size() { return quantity; }

	double get_element(int index)
	// double& get_element(int index), т.к. ptr[index] это ссылка?
	{
		if (index >= 0 && index < quantity) { return ptr[index]; }
		else {
			// throw OutOfBounds(index);
			//сгенерировать исключение { выдать последний элемент массива } 
			return -1;
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity) { ptr[index] = value; }
		else {
			//сгенерировать исключение { увеличить `capacity` и `quantity` --> вызвать еще раз этот метод }
		}
	}




	// add an element in the end 
	void push_back(double value) 
	{
		if ( sizeof(value) == sizeof(ptr[0]) ) {

			if ( quantity < capacity ) 
			{
				ptr[quantity++] = value;
				//quantity++;
			}
			else {
				capacity += (quantity - capacity) + 1;
				ptr[quantity++] = value;
			} 
			// сгенерировать исключение { увиличить `capacity` --> еще раз вызвать этот метод }
		}
		// сгенерировать исключение { првести значение к соответствующему типу --> вызвать этот
	    // метод еще раз с правильным типом аргумента }
	}

	// delete the last element
	void remove_last_element()
	{
		if (quantity >= 0) 
		{
			ptr[--quantity] = 0;
			quantity--;
		}
	}

	double& operator[](int index)
	{
		// if (index < quantity) { return ptr[index]; } // каким образом программа возвращает ссылку, если это число типа double
		// if (index < quantity) { double& ref_prt_id = ptr[index]; return ref_prt_id; }
		// в чем разница? { return get_element(index); } 
		// в том, что первый вариант возвращает ссылку?
		// в 126 строчке возвращаемое значение объявлено, как &, но мы же возвращаем число, или 
		// мы возыращаем ссылку, т.к. ptr это указатель на последовательности адресов ячеек?
		// else { return -1; } 
		// 
		//сгенерировать исключение { выдать последний элемент массива }/
	}

	ArrayMaster& operator=(const vector<double>& vector)
	{
		// ArrayMaster( sizeof(vector) ); массив типа ArrayMaster уже существует
		capacity = sizeof(vector);
		quantity = vector.size();

		for (int itt = 0; itt < vector.size(); itt++) {
			ptr[itt] = vector[itt];
		}
		return (*this);
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса (не понимаю комметарий)
	}

	ArrayMaster operator=(const ArrayMaster& array_existing) //ArrayMaster& operator=(const ArrayMaster& P)
	{
		capacity = array_existing.capacity;
		quantity = array_existing.quantity;
		for (int itt = 0; itt < quantity; itt++)
		{
			ptr[itt] = array_existing.ptr[itt];
		}

		return (*this);
	}



	void print()
	{
		cout << "\n" << typeid(*this).name() << " size: " << quantity << ", elements: { :";
		for (int itt = 0; itt < quantity; itt++)
		{
			cout << ptr[itt]; // почесу не cout << *ptr[itt];
			if (itt != quantity - 1)
				cout << " : ";
		}
		cout << "}";
	}

	

};

class MyArrayChild : public ArrayMaster //
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : ArrayMaster(Dimension) { cout << "\nMyArrayChild constructor"; }

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
		if (index == -1 || index >= quantity) { ArrayMaster::push_back(value); }
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
	ArrayMaster arr;
	if (true)
	{
		MyArrayChild arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			// arr.ArrayMaster::push_back(i + 1);
			arr.push_back(i + 1);
		}
		arr.print();
		cout << "\n";
		//cout << "\n" << sp << "\n";
	}
	char c; cin >> c;
	return 0;
}

