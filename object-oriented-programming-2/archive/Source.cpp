#define nline '\n'
#include <iostream>
#include <fstream>


#include <list>
#include <iterator>
#include <algorithm>



#include <iostream>
#include <fstream>


using namespace std;
template <class T>
class Element {
//������� �������� ������
private:
//��������� �� ���������� � ��������� �������
	Element *next;
	Element *prev;
	//����������, �������� � ����
	T field;
public:
	Element(T value = 0, Element<T> *next_ptr = NULL, Element<T> *prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev - prev_ptr;
	}
	//������ � ���� *next
	virtual Element *getNext() { return next; }
	virtual void setNext(Element *value) { next = value; }
	//������ � ���� *prev
	virtual Element *getPrevious() { return prev; }
	virtual void setPrevious(Element *value) { prev = value; }
	//������ � ���� � �������� ����������� field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }
	template<class T> friend ostream &operator<< (ostream &
												  ustream, Element<T> &obj);
};
template<class T>
ostream &operator << (ostream &ustream, Element<T> &obj)
{
	ustream << obj.field;
	return ustream;
}
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
	//����� ����������� �������: ���� �� ����������� � �����
	������, �� ������ ����������� ����������
		virtual Element<T> *push(T value) = 0;
		//����� ����������� �������: ���� �� ����������� � �����
	������, �� ������ ����������� ��������
		virtual Element<T> *pop() = 0;
	virtual ~LinkedListParent()
	{
	//���������� - ������������ ������
		cout << "\nParent destructor";
	}
//��������� �������� �� ������� - ������ ���������������
	������ ����� �������� ?
		virtual Element<T>*operator[](int i)
	{
	//����������
		if ( i<0 || i>num ) return NULL;
		int k = 0;
		//���� i-� ������� - ������� � ������ � ����������� i
		����� ������
			Element<T> *cur = head;
		for ( k = 0; k < i; k++ ) {
			cur = cur->getNext();
		}
		return cur;
	}
	template<class T> friend ostream &operator<< (ostream &
												  ustream, LinkedListParent<T> &obj);
	template<class T> friend istream &operator>> (istream &
												  ustream, LinkedListParent<T> &obj);
};
template<class T>
ostream &operator << (ostream &ustream, LinkedListParent<T> &
					  obj)
{
	if ( typeid(ustream).name() == typeid(ofstream).name() ) {
		ustream << obj.num << "\n";
		for ( Element<T> *current = obj.getBegin(); current !=
			 NULL; current = current->getNext() )
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for ( Element<T> *current = obj.getBegin(); current != NULL;
		 current = current->getNext(), i++ )
		ustream << "arr[" << i << "] = " << current->getValue()
		<< "\n";
	return ustream;
}
template<class T>
istream &operator >> (istream &ustream, LinkedListParent<T> &
					  obj)
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
template<typename ValueType>
class ListIterator : public
	std::iterator<std::input_iterator_tag, ValueType> {
private:
public:
	ListIterator() { ptr = NULL; }
	//ListIterator(ValueType* p) { ptr = p; }
	ListIterator(Element<ValueType> *p) { ptr = p; }
	ListIterator(const ListIterator &it) { ptr = it.ptr; }
	bool operator!=(ListIterator const &other) const {
		return
			ptr != other.ptr;
	}
	bool operator==(ListIterator const &other) const {
		return
			ptr == other.ptr;
	}//need for BOOST_FOREACH
	Element<ValueType> &operator*()
	{
		return *ptr;
	}
	ListIterator &operator++() {
		ptr = ptr->getNext(); return
			*this;
	}
	ListIterator &operator++(int v) {
		ptr = ptr->getNext(); re -
			turn * this;
	}
	ListIterator &operator=(const ListIterator &it) {
		ptr =
			it.ptr; return *this;
	}
	ListIterator &operator=(Element<ValueType> *p) {
		ptr = p;
		return *this;
	}
private:
	Element<ValueType> *ptr;
};
template <class T>
class IteratedLinkedList : public LinkedListParent<T> {
public:
	IteratedLinkedList() : LinkedListParent<T>() {
		cout <<
			"\nIteratedLinkedList constructor";
	}
	virtual ~IteratedLinkedList() {
		cout <<
			"\nIteratedLinkedList destructor";
	}
	ListIterator<T> iterator;
	ListIterator<T> begin() {
		ListIterator<T> it =
			LinkedListParent<T>::head; return it;
	}
	ListIterator<T> end() {
		ListIterator<T> it =
			LinkedListParent<T>::tail; return it;
	}
};
