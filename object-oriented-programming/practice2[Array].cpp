// ������������ ������ ����-01-21 �������- 24
// 
// quantity � capacity, ������ ���� �� ������� ��������: quantity- ���������� ��������� � �������
// capacity- ������ ��� ���� ��������� � ������, ����� capacity = sizeof(type) * quantity
// 
// �� ������� ��� �������� double* ptr; 
// 
// �� ������� ��� �������� ptr = new double[Dimension]
// 
// ������ 66- �������������, ���� �� �� �� ��������� ������� (ptr != NULL), �� 
// ��� ����� ������� �� ������� delete ?

// ���������� ��������� � ������� int arrSize = sizeof(arr)/sizeof(arr[0]);
// ��� std::array::size 

#include <iostream>
#include <vector>

using namespace std;

class ArrayParent
{
protected:

	int capacity; // ���������� ������ ��� �������

	int quantity; // ���������� ��������� � ������� - ������� ������ ����������

	double* ptr; // ��������� �� ������ � ������, ������� ��� ������ �������� ������
	// ��������� ��� ������� ���������� ����������� ������� ������, �� ��� �������, ��� ��������� ptr
	// ���� ��� ������ ���������������� ������ ������?

public:
	//������������ � ����������
	
	// default constructor --> capacity = 100; quantity = 0; 
	ArrayParent(int Dimension = 100)
	{
		cout << "\n" << "ArrayParent constructor";

		capacity = Dimension;
		quantity = 0;
		ptr = new double[Dimension]; // new- ��������� ����������� ������ delete- �������� ��������� �� ������
	}


	// ����������� ��������� ������������ ������ --> ������� ����� �������, �� � ������� capacity
	ArrayParent(double* array_exist, int len)
	{

		cout << "\n" << "ArrayParent constructor";

		capacity = (len >= 1000) ? 2 * len : 1000; // ����������� ���������� ������ ��� ����, ����� �����
												   // ����� ���� �������� � ���� ��������
		ptr = new double[capacity];

		for (int itt = 0; itt < len; itt++)
		{
			ptr[itt] = array_exist[itt];
		}
	}

	// ���������� ����� ������������� �������
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

	// ����������
	// NUll - ����� ��������� ��� ��������� �� ����� ����� ������ ������������
	// ���������. �� ����, ����� �������, ��� ������� ��������� �� �������� ����������� 
	// ������ � ������, �� ��������� NULL ��������������� � 0, �� ����� ����������� nullptr
	~ArrayParent()
	{
		cout << "\n" << "ArrayParent destructor";
		if (ptr != nullptr) // ���� ��� ������ ���� �������� ������� ����� type* ptr; �� ptr != NULL
		{
			delete[] ptr; // �������� ������, ������� ����� ���� ������ ���������� �������
			ptr = nullptr;
		}
	}

	//��������� � �����
	int get_�apacity() { return capacity; }

	int get_size() { return quantity; }

	double get_element(int index)
	{
		if (index >= 0 && index < quantity) { return ptr[index]; }
		else {
			//������������� ����������, ���� ������ ������������
			return -1;
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity) { ptr[index] = value; }
		else {
			//������������� ����������, ���� ������ ������������
		}
	}


	//���������� � ����� ������ ��������
	void push(double value) 
	{
		if (sizeof(value) == sizeof(ptr[0])) {

			if (quantity < capacity) // ����� ����������� ������ �������� ����� ������� ������ ������ 2-4
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

	//�������� �������� � �����
	void remove_last_element()
	{
		if (quantity >= 0) {
			ptr[--quantity] = 0; // ������ --quantity
			quantity--;
		}
		//��� ������, ���� ������ �� 
		//��� ������, ���� ����?
	}

	double& operator[](int index) // ������ ������?
	{
		if (index < quantity) { return ptr[index]; }
		// else { return -1; }
		//���������� ��������� []
	}

	ArrayParent& operator=(const vector<double>& vector) // ��� ������, = ���� ���������������
	{
		ArrayParent(sizeof(vector));
		capacity = sizeof(vector) / sizeof(vector[0]) * vector.size();
		quantity = vector.size();
		for (int itt = 0; itt < quantity; itt++) {
			ptr[itt] = vector[itt];
		}
		return *this;
		//arr1 = arr2 = arr3; ��� arr_i - ������� ������ ������
	}

	ArrayParent(const vector<double>& vector) // �� �������
	{
		//�������� ����� ������� - � ��������, ��� ����������� ���������� �� ������� / �������� ���������� � �������
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
	//���������� ����������� ��������. ����� �� ���-�� ���?
	MyArrayChild(int Dimension = 100) : ArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

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

//��������� ���������������������
//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

//���������� �������� � �����
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

