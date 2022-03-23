// ������������ ������ ����-01-21 �������- 24


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
	ArrayMaster(double* array_existing, int len) // ��� ��� ���������� �� 60 �������
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
	ArrayMaster(const vector<double>& vector) // �� �������
	{
		//�������� ����� ������� - � ��������, ��� ����������� ���������� �� ������� / �������� ���������� � �������
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
	int get_�apacity() { return capacity; }

	int get_size() { return quantity; }

	double get_element(int index)
	// double& get_element(int index), �.�. ptr[index] ��� ������?
	{
		if (index >= 0 && index < quantity) { return ptr[index]; }
		else {
			// throw OutOfBounds(index);
			//������������� ���������� { ������ ��������� ������� ������� } 
			return -1;
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity) { ptr[index] = value; }
		else {
			//������������� ���������� { ��������� `capacity` � `quantity` --> ������� ��� ��� ���� ����� }
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
			// ������������� ���������� { ��������� `capacity` --> ��� ��� ������� ���� ����� }
		}
		// ������������� ���������� { ������� �������� � ���������������� ���� --> ������� ����
	    // ����� ��� ��� � ���������� ����� ��������� }
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
		// if (index < quantity) { return ptr[index]; } // ����� ������� ��������� ���������� ������, ���� ��� ����� ���� double
		// if (index < quantity) { double& ref_prt_id = ptr[index]; return ref_prt_id; }
		// � ��� �������? { return get_element(index); } 
		// � ���, ��� ������ ������� ���������� ������?
		// � 126 ������� ������������ �������� ���������, ��� &, �� �� �� ���������� �����, ��� 
		// �� ���������� ������, �.�. ptr ��� ��������� �� ������������������ ������� �����?
		// else { return -1; } 
		// 
		//������������� ���������� { ������ ��������� ������� ������� }
	}

	ArrayMaster& operator=(const vector<double>& vector)
	{
		// ArrayMaster( sizeof(vector) ); ������ ���� ArrayMaster ��� ����������
		capacity = sizeof(vector);
		quantity = vector.size();

		for (int itt = 0; itt < vector.size(); itt++) {
			ptr[itt] = vector[itt];
		}
		return (*this);
		//arr1 = arr2 = arr3; ��� arr_i - ������� ������ ������ (�� ������� ����������)
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
			cout << ptr[itt]; // ������ �� cout << *ptr[itt];
			if (itt != quantity - 1)
				cout << " : ";
		}
		cout << "}";
	}

	

};

class MyArrayChild : public ArrayMaster //
{
public:
	//���������� ����������� ��������. ����� �� ���-�� ���?
	MyArrayChild(int Dimension = 100) : ArrayMaster(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//�������� ��������
	//void RemoveAt(int index = -1);

	//����� ��������
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

	//������� ��������
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

//��������� ���������������������
//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

//���������� �������� � �����
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

