#pragma once
#include <iostream>
#include <memory>

#include "Node.h"

template<class Type> using uptrNode = std::unique_ptr<Node<Type>>;
template<class Type> using sptrNode = std::shared_ptr<Node<Type>>;
template<class Type> using wptrNode = std::weak_ptr<Node<Type>>;



template <class Type> class LinkedList {
public:

	LinkedList();

	LinkedList (const LinkedList &otherList);

	virtual ~LinkedList();



	virtual void clear() final;

	const size_t size() const noexcept;



	const uptrNode GetBegin() const noexcept;
	const uptrNode GetEnd() const noexcept;

	void SetBegin (wptrNode otherBegin) noexcept;
	void SetEnd (wptrNode otherEnd) noexcept;



	virtual void push (const Type &data) = 0;
	virtual const sptrNode pop() = 0;

	

	virtual sptrNode operator[] (const int &pos);



	template<class Type> friend std::ostream &operator<< (std::ostream &output,
														  LinkedList<Type> &list);
	template<class Type> friend std::istream &operator>> (std::istream &input,
														  LinkedList<Type> &list);

protected:

	sptrNode _begin;
	sptrNode _end;
	  size_t _size;
};

// TODO выбросить исключение
template<class Type> std::ostream &operator<< (std::ostream &output, LinkedList<Type> &list)
{
	if ( list._size != 0 ) {
		Object<Type> *objectCurrent = list.GetBegin();

		if ( typeid(output).name() == typeid(std::ofstream).name() ) {
			output << list.size() << nline;

			while ( objectCurrent != nullptr ) {
				output << objectCurrent->_data << " ";
				objectCurrent = objectCurrent->GetSucessor()
			}
		}
		else {
			output << nline << "Size: " << list._size << nline;

			int it = 0;
			while ( objectCurrent != nullptr ) {
				output << "[" << it << "] = " << objectCurrent->_data << nline;
			}
		}
	}


	return output;
}

template<class Type> std::istream &operator>> (std::istream &input, LinkedList<Type> &list)
{
	int size = 0; input >> size;

	list.clear();

	/// warning: требуется инициализация по умолчанию 
	Object<Type> objectCurrent;
	for ( int it = 0; it < size; it++ ) {
		input >> objectCurrent;
		list.push(objectCurrent);
	}


	return input;
}


