// Сиразетдинов Рустем КМБО-01-21 Вариант- 24


#include <iostream>
#include <vector>

using namespace std;

class ArrayMaster
{
protected:

	int capacity_; // amount of memory for the array

	int quantity_; // number of elements in the array < `capacity_` 

	double* ptr_; // a pointer to the cells in memory that all together form an array

public:
	
	// default constructor --> `capacity_` = 100; `quantity_` = 0; 
	ArrayMaster(int Dimension = 100)
	{
		cout << "\n" << "default constructor";

		capacity_ = Dimension;
		quantity_ = 0;
		ptr_ = new double[Dimension]; 
	}

	// default constructor --> `capacity_` = 100; `quantity_` = 100; ptr_[itt] = 0 for all itt in 
	ArrayMaster(int quantity = 100, double value = 0)
	{
		cout << "\n" << "default constructor";

		capacity_ = quantity;
		quantity_ = quantity;
		ptr_ = new double[quantity];

		for (int itt = 0; itt < quantity_; itt++)
		{
			ptr_[itt] = value;
		}
	}

	// constructor_copy : ArrayMaster::array_1 --> ArrayMaster::(copy of array_1)
	ArrayMaster(const ArrayMaster& array_existing)
	{
		capacity_ = array_existing.capacity_;
		quantity_ = array_existing.quantity_;
		ptr_ = new double[capacity_];

		for (int itt = 0; itt < array_existing.quantity_; itt++)
		{
			ptr_[itt] = array_existing.ptr_[itt];
		}
	}

	// constructor_1 : double _name_ [_amount_] --> ArrayMaster
	ArrayMaster(double* array_existing, int len) 
	{

		cout << "\n" << "constructor_1";

		capacity_ = (len >= 1000) ? 2 * len : 1000; // increase `capacity_` to adding elements after

		ptr_ = new double[capacity_];

		for (int itt = 0; itt < len; itt++)
		{
			ptr_[itt] = array_existing[itt];
		}
	}
	
	// constructor_2 : vector --> ArrayMaster
	ArrayMaster(const vector<double>& vector) 
	{
		cout << "\n" << "constructor_2";
		capacity_ = sizeof(vector);
		quantity_ = vector.size();
		ptr_ = new double[capacity_];

		for (int itt = 0; itt < vector.size(); itt++)
		{
			ptr_[itt] = vector[itt];
		}
	}



	// destructor
	~ArrayMaster()
	{
		cout << "\n" << "ArrayMaster has been deleted";

		if (ptr_ != nullptr) 
		{
			delete[] ptr_; 
			ptr_ = nullptr;
		}
	}




	// get... & set...
	int get_сapacity() { return capacity_; }

	int get_size() { return quantity_; }

	double get_element(int index) // double& get_element(int index)
	{
		if (index >= 0 && index < quantity_) { return ptr_[index]; }
		else {
			// throw OutOfBounds(index);
			//сгенерировать исключение { выдать последний элемент массива } 
			return -1;
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity_) { ptr_[index] = value; }
		else {
			//сгенерировать исключение { увеличить `capacity_` и `quantity_` --> заполнить значения 0 -->
			// --> вызвать еще раз этот метод }
		}
	}




	// add an element in the end 
	void push_back(double value) 
	{
		if ( sizeof(value) == sizeof(ptr_[0]) ) {

			if ( quantity_ < capacity_ ) 
			{
				ptr_[quantity_++] = value; // ...; quantity_++;
			}
			else {
				capacity_ += (quantity_ - capacity_) + 1;
				ptr_[quantity_++] = value;
			} 
			// сгенерировать исключение { увиличить `capacity_` --> еще раз вызвать этот метод }
		}
		// сгенерировать исключение { првести значение к соответствующему типу --> вызвать этот
	    // метод еще раз с правильным типом аргумента }
	}

	// delete the last element
	void remove_last_element()
	{
		if (quantity_ > 0) 
		{
			ptr_[--quantity_] = 0;
			quantity_--;
		}
	}




	double& operator[](int index)
	{
		// if (index < quantity_) { return ptr_[index]; } // каким образом программа возвращает ссылку, если это число типа double
		// if (index < quantity_) { double& ref_prt_id = ptr_[index]; return ref_prt_id; }
		// в чем разница? { return get_element(index); } 
		// в том, что первый вариант возвращает ссылку?
		// в 126 строчке возвращаемое значение объявлено, как &, но мы же возвращаем число, или 
		// мы возыращаем ссылку, т.к. ptr_ это указатель на последовательности адресов ячеек?
		// else { return -1; } 
		// 
		//сгенерировать исключение { выдать последний элемент массива }/
	}

	// array::ArrayMaster = vector::vector --> array(=vector)::ArrayMaster
	ArrayMaster& operator=(const vector<double>& vector)
	{
		capacity_ = sizeof(vector);
		quantity_ = vector.size();

		for (int itt = 0; itt < vector.size(); itt++) {
			ptr_[itt] = vector[itt];
		}
		return (*this);
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса (не понимаю комметарий)
	}

	// array::ArrayMaster = array::C --> array(=vector)::ArrayMaster
	ArrayMaster operator=(const ArrayMaster& array_existing) //ArrayMaster& operator=(const ArrayMaster& P)
	{
		capacity_ = array_existing.capacity_;
		quantity_ = array_existing.quantity_;
		for (int itt = 0; itt < quantity_; itt++)
		{
			ptr_[itt] = array_existing.ptr_[itt];
		}

		return (*this);
	}



	void print()
	{
		cout << "\n" << typeid(*this).name() << " size: " << quantity_ << ", elements: { :";
		for (int itt = 0; itt < quantity_; itt++)
		{
			cout << ptr_[itt]; 
			if (itt != quantity_ - 1)
				cout << " : ";
		}
		cout << "}";
	}

	

};

class MyArrayChild : public ArrayMaster 
{
public:
	// Что-то нужно еще, я не знаю?
	MyArrayChild(int Dimension = 100) : ArrayMaster(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	//void RemoveAt(int index = -1);

	//поиск элемента
	int IndexOf(double value, bool FindFromStart = true)
	{
		if (FindFromStart)
		{
			for (int i = 0; i < quantity_; i++)
			{
				if (value == ptr_[i]) { return i; }
			}
		}
		else
		{
			for (int i = quantity_ - 1; i > 0; i--)
			{
				if (value == ptr_[i]) { return i; }
			}
		}
		return -1;
	}

	//вставка элемента
	void InsertAt(double value, int index = -1)
	{
		if (index == -1 || index >= quantity_) { ArrayMaster::push_back(value); }
		else
		{

			for (int i = quantity_; i > index; i--)
			{
				ptr_[i] = ptr_[i - 1];
			}
			ptr_[index] = value;
			quantity_++;
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

