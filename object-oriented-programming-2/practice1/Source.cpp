// AbstractClassList.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>


using namespace std;


template <class T>
class LinkedListParent {
protected:
	//���������� ������� ������ � �����
	Element<T> *head;
	Element<T> *tail;
	//��� �������� ������ ���������� ���������
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T> *getBegin() { return head; }

	virtual Element<T> *getEnd() { return tail; }

	LinkedListParent()
	{
		//����������� ��� ����������
		cout << "\nParent constructor";
		head = NULL;
		num = 0;
	}

	//����� ����������� �������: ���� �� ����������� � ����� ������, �� ������ ����������� ����������
	virtual Element<T> *push(T value) = 0;

	//����� ����������� �������: ���� �� ����������� � ����� ������, �� ������ ����������� ��������
	virtual Element<T> *pop() = 0;

	virtual ~LinkedListParent()
	{
		//���������� - ������������ ������
		cout << "\nParent destructor";
	}

	//��������� �������� �� ������� - ������ ��������������� ������ ����� ��������?
	virtual Element<T> *operator[](int i)
	{
		//����������
		if ( i<0 || i>num ) return NULL;
		int k = 0;

		//���� i-� ������� - ������� � ������ � ����������� i ����� ������
		Element<T> *cur = head;
		for ( k = 0; k < i; k++ ) {
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream &operator<< (ostream &ustream, LinkedListParent<T> &obj);
	template<class T> friend istream &operator>> (istream &ustream, LinkedListParent<T> &obj);
};
template<class T>
ostream &operator << (ostream &ustream, LinkedListParent<T> &obj)
{
	if ( typeid(ustream).name() == typeid(ofstream).name() ) {
		ustream << obj.num << "\n";
		for ( Element<T> *current = obj.getBegin(); current != NULL; current = current->getNext() )
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for ( Element<T> *current = obj.getBegin(); current != NULL; current = current->getNext(), i++ )
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}
template<class T>
istream &operator >> (istream &ustream, LinkedListParent<T> &obj)
{
	//������ �� ����� � ������� ���������
	int len;
	ustream >> len;
	//����� ���� �������� ������ ��� obj, ���������� obj.num = 0
	double v = 0;
	for ( int i = 0; i < len; i++ ) {
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}











//����� ����������� ������ - ��������� �������� ������, �������� ��� ������� � �����
template <class T>
class IteratedLinkedList : public LinkedListParent<T> {
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> iterator;

	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }
};

template <class Type>
class Queue : public IteratedLinkedList<Type> {
public:
	Queue() : IteratedLinkedList() { cout << "dsl;fj"; }
	virtual ~Queue() = default;

	virtual Element<Type> *push (Type value) {
		// ���������� ��� ����� ��� `new`
		Element<Type> *temp = new Element<Type> (value);
		if ( LinkedListParaent<Type>::num != 0 ) {
			LinkedListParaent<Type>::tail->setNext(temp);
			LinkedListParaent<Type>::temp->setPrevious(LinkedListParaent<Type>::tail);
		}
		else {
			LinkedListParaent<Type>::head = temp;
		}
		LinkedListParaent<Type>::tail = temp;
		LinkedListParaent<Type>::num++;



		return temp;
	}

	virtual Element<Type> *pop() {



		if ( LinkedListParaent<Type>::num == 0 ) { // ������ ������ 
			return nullptr;
		}


		auto objectDelete = LinkedListParaent<Type>::head;
		LinkedListParaent<Type>::num--;

		if ( LinkedListParaent<Type>::head == LinkedListParaent<Type>::tail ) { // num == 1
			LinkedListParaent<Type>::head = LinkedListParaent<Type>::tail = nullptr;
		}
		else {
			LinkedListParaent<Type>::head = LinkedListParaent<Type>::head->getNext();
			(LinkedListParaent<Type>::head)->setPrevious(nullptr);
			objectDelete->setNext(nullptr); // ����� ���� �� ���������� ����� ����� ���������� ������

		}



		return objectDelete;
	}
};

int main()
{

	//Queue<int> S;
	/*S.push(1);
	S.push(2);
	S.push(3);
	cout << S;
	cout << "\n";
	Element *e1 = S.pop();
	cout << "\nElement = " << e1->getValue();
	cout << S;*/
	//cout << "\nIndex in the Stack class: " << S[1]->getValue();

	/*cout << S;
	cout << "\nIterators:\n";
	S.iterator = S.begin();
	while (S.iterator != S.end())
	{
		cout << *S.iterator << " ";
		S.iterator++;
	}
	cout << *S.iterator << " ";

	char c; cin >> c;*/
	return 0;
}

