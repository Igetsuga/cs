/*****************************************************************//**
 * \file   Node.h
 * \brief  Файл реализации параметризованного класса `Node`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    September 2022
 *********************************************************************/
#pragma once
#include <iostream>
#define nline '\n'

/**
* /brief Класс представляет собой обочку, которая покрывает каждый элемент
*  контейнера.
*
* Реализация через указатели.
*/
template<class Type> class Node
{
public:

	Node (const Type &data,
		  Node<Type> *sucessor = nullptr,
		  Node<Type> *predecessor = nullptr);

	~Node ();


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------


	Node<Type> *getSucessor() const noexcept;
	
	Node<Type> *getPredecessor() const noexcept;
	
	const Type &getData() const noexcept;


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------


	void setSucessor (Node<Type> *sucessor) noexcept;
	
	void setPredecessor (Node<Type> *predecessor) noexcept;
	
	void setData (const Type &data) noexcept;


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------

	
	bool isEqualDeep (const Node<Type> &node) const noexcept;

	Node<Type> &operator= (const Node<Type> &node);

	Node<Type> &operator= (const Type &data);
	
	bool operator> (const Node<Type> &node) const noexcept;
	
	bool operator< (const Node<Type> &node) const noexcept;
	
	bool operator== (const Node<Type> &node) const noexcept;

	bool operator!= (const Node<Type> &node) const noexcept;

	bool operator>= (const Node<Type> &node) const noexcept;

	bool operator<= (const Node<Type> &node) const noexcept;

	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------


	template<class otherType> friend std::ostream &operator<< (std::ostream &output,
															   const Node<otherType> &node);


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------


protected:
	Node<Type> *_sucessor;
	Node<Type> *_predecessor;
	Type        _data;
};


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> Node<Type>::Node (const Type &data,
									   Node<Type> *sucessor,
									   Node<Type> *predecessor) {
	_sucessor = sucessor;
	_predecessor = predecessor;
	_data = data;
}

template<class Type> Node<Type>::~Node () = default;


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
Node<Type> *Node<Type>::getSucessor() const noexcept {
	return _sucessor;
}


template<class Type>
Node<Type> *Node<Type>::getPredecessor() const noexcept {
	return _predecessor;
}


template<class Type>
const Type &Node<Type>::getData() const noexcept {
	return _data;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
void Node<Type>::setSucessor (Node<Type> *sucessor) noexcept {
	_sucessor = sucessor;
}


template<class Type>
void Node<Type>::setPredecessor (Node<Type> *predecessor) noexcept {
	_predecessor = predecessor;
}


template<class Type>
void Node<Type>::setData (const Type & data) noexcept {
	_data = data;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
bool Node<Type>::isEqualDeep (const Node<Type> &node) const noexcept {
	if ( _data == node._data &&
		_sucessor->getData() == node._sucessor->getData() &&
		_predecessor->getData() == node._predecessor->getData() ) {
		return true;
	}


	return false;
}


template<class Type>
Node<Type> &Node<Type>::operator= (const Node<Type> &node) {
	_sucessor = node._sucessor;
	_predecessor = node._predecessor;
	_data = node._data;
}


template<class Type>
Node<Type> &Node<Type>::operator= (const Type & data) {
	_data = data;
}


template<class Type>
bool Node<Type>::operator> (const Node<Type> &node) const noexcept {
	return _data > node._data;
}


template<class Type>
bool Node<Type>::operator< (const Node<Type> &node) const noexcept {
	return _data < node._data;
}


template<class Type>
bool Node<Type>::operator== (const Node<Type> &node) const noexcept {
	return _data == node._data;
}


template<class Type>
bool Node<Type>::operator!= (const Node<Type> &node) const noexcept {
	return !(*this == node);
}


template<class Type>
bool Node<Type>::operator>= (const Node<Type> &node) const noexcept {
	return (_data == node._data) || (_data > node._data);
}


template<class Type>
bool Node<Type>::operator<= (const Node<Type> &node) const noexcept {
	return (_data == node._data) || (_data < node._data);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> std::ostream &operator<< (std::ostream &output,
											   const Node<Type> &node) {
	output << node._data;


	return output;
}