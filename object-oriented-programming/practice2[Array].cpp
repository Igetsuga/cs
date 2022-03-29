// Сиразетдинов Рустем КМБО-01-21 Вариант- 24


#include <iostream>
#include <vector>

using namespace std;

class Exception
{
protected:
	string message_; // error message
public:

	// default constructor
	Exception()
	{
		message_ = "ERROR";
	}

	// constructor_1
	Exception(const string& message)
	{
		message_ = message;
	}

	// constructor_copy
	Exception(const Exception& error)
	{
		message_ = error.message_;
	}

	// destructor
	~Exception() {}

	virtual void print()
	{
		cout << "Exception: " << message_ << '\n';
	}
};

class OutOfBounds : public Exception
{
private: 
	string message_;
public:
	OutOfBounds() { message_ = "Array index out of bounds"; }
	~OutOfBounds() {}
};

class ArrayMaster
{
protected:

	int capacity_; // amount of memory for the array

	int quantity_; // number of elements in the array < `capacity_` 

	double* array_; // a pointer to the cells in memory that all together form an array

public:
	
	// default constructor --> `capacity_` = 100; `quantity_` = 0; 
	ArrayMaster(int Dimension = 256)
	{
		cout << "\n" << "default constructor";

		capacity_ = Dimension;
		quantity_ = 0;
		array_ = new double[Dimension]; 
	}

	/* // default constructor --> `capacity_` = 100; `quantity_` = 100; array_[itt] = 0 for all itt in 
	ArrayMaster(int quantity = 100, double value = 0)
	{
		cout << "\n" << "default constructor";

		capacity_ = quantity;
		quantity_ = quantity;
		array_ = new double[quantity];

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = value;
		}
	} */

	// constructor_copy : ArrayMaster::array_1 --> ArrayMaster::(copy of array_1)
	ArrayMaster(const ArrayMaster& array_existing)
	{
		capacity_ = array_existing.capacity_;
		quantity_ = array_existing.quantity_;
		array_ = new double[capacity_];

		for (int itt = 0; itt < array_existing.quantity_; itt++)
		{
			array_[itt] = array_existing.array_[itt];
		}
	}

	// constructor_1 : double*[] --> ArrayMaster::result
	ArrayMaster(double* array_existing, int len) 
	{

		cout << "\n" << "constructor_1";

		capacity_ = (len >= 1000) ? 2 * len : 1000; // increase `capacity_` to adding elements after
		quantity_ = len;

		array_ = new double[capacity_];

		for (int itt = 0; itt < len; itt++)
		{
			array_[itt] = array_existing[itt];
		}
	}
	
	// constructor_2 : vector::vector --> ArrayMaster::result
	ArrayMaster(const vector<double>& vector) 
	{
		cout << "\n" << "constructor_2";
		capacity_ = (vector.size() > 256) ? vector.size() : 256;
		quantity_ = vector.size();
		array_ = new double[capacity_];

		for (int itt = 0; itt < vector.size(); itt++)
		{
			array_[itt] = vector[itt];
		}
	}



	// destructor
	~ArrayMaster()
	{
		cout << "\n" << "ArrayMaster has been deleted";

		if (array_ != nullptr) 
		{
			delete[] array_; 
			array_ = nullptr;
		}
	}



	// get... & set...
	int get_сapacity() { return capacity_; }

	int get_size() { return quantity_; }

	double get_element(int index) 
	{
		if (index >= 0 && index < quantity_) { return array_[index]; }
		else {
			throw OutOfBounds(); return array_[quantity_ - 1];
			//сгенерировать исключение { выдать последний элемент массива } 
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity_) { array_[index] = value; }
		else {
			throw OutOfBounds(); 
			capacity_ = (capacity_ > index) ? capacity_ : index;
			int itt = quantity_;
			quantity_ = index + 1;
			//(*this).set_element(index, value);
			while (itt < index)
			{
				array_[itt] = (itt == index) ? value : 0;
			}
			//сгенерировать исключение { увеличить `capacity_` и `quantity_` --> заполнить значения 0 -->
			// --> вызвать еще раз этот метод }
		}
	}




	// add an element in the end 
	void push_back(double value) 
	{
		if ( sizeof(value) == sizeof(array_[0]) ) {

			if ( quantity_ < capacity_ ) 
			{
				array_[quantity_++] = value; // ...; quantity_++;
			}
			else {
				capacity_ += (quantity_ - capacity_) + 1;
				array_[quantity_++] = value;
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
			array_[--quantity_] = 0;
			quantity_--;
		}
	}




	double& operator[](int index)
	{
		// if (index < quantity_) { return array_[index]; } // каким образом программа возвращает ссылку, если это число типа double
		// if (index < quantity_) { double& ref_prt_id = array_[index]; return ref_prt_id; }
		// в чем разница? { return get_element(index); } 
		// в том, что первый вариант возвращает ссылку?
		// в 126 строчке возвращаемое значение объявлено, как &, но мы же возвращаем число, или 
		// мы возыращаем ссылку, т.к. array_ это указатель на последовательности адресов ячеек?
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
			array_[itt] = vector[itt];
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
			array_[itt] = array_existing.array_[itt];
		}

		return (*this);
	}



	void print()
	{
		cout << "\n" << typeid(*this).name() << " size: " << quantity_ << ", elements: { :";
		for (int itt = 0; itt < quantity_; itt++)
		{
			cout << array_[itt]; 
			if (itt != quantity_ - 1)
				cout << " : ";
		}
		cout << "}";
	}

	

};

class ArrayDerived : public ArrayMaster
{
public:
	// Что-то нужно еще, я не знаю?

	// 
	ArrayDerived(int Dimension = 100) : ArrayMaster(Dimension) { cout << "\nMyArrayChild constructor"; }



	// destructor
	~ArrayDerived() { cout << "\nMyArrayChild destructor\n"; }



	// find an element --> index or (-1)
	int findElement(double value, bool findFromStart = true)
	{
		if (findFromStart)
		{
			for (int itt = 0; itt < quantity_; itt++)
			{
				if (value == array_[itt]) { return itt; }
			}
		}
		else {
			for (int itt = quantity_ - 1; itt > 0; itt--)
			{
				if (value == array_[itt]) { return itt; }
			}
		}

		return -1;
	}

	// inserting of element
	void InsertAt(double value, int index = -1)
	{
		if (index == -1 || index >= quantity_) { ArrayMaster::push_back(value); }
		else
		{

			for (int i = quantity_; i > index; i--)
			{
				array_[i] = array_[i - 1];
			}
			array_[index] = value;
			quantity_++;
		}
	}

	// removing of element
	void removeElement(int index = -1)
	{
		if (index > quantity_)
		{
			(*this).removeElement(quantity_ - 1);
		} else {
			for (int itt = index; itt < quantity_ - 1; itt++)
			{
				array_[itt] = array_[itt + 1];
			}
			quantity_--;
			capacity_--;
		}
	}

};


//выделение подпоследовательности
//ArrayDerived SubSequence(int StartIndex = 0, int Length = -1)

//добавление элемента в конец
//operator + ?



int main()
{
	ArrayMaster arr;
	if (true)
	{
		ArrayDerived arr;
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

