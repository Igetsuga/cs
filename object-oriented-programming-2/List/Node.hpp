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
		  Node<Type> *predecessor = nullptr) {
		_sucessor = sucessor;
		_predecessor = predecessor;
		_data = data;
	}

	~Node () = default;


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------


	Node<Type> *getSucessor() const noexcept {
		return _sucessor;
	}
	
	Node<Type> *getPredecessor() const noexcept {
		return _predecessor;
	}
	
	const Type &getData() const noexcept {
		return _data;
	}


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------


	void setSucessor (Node<Type> *sucessor) noexcept {
		_sucessor = sucessor;
	}
	
	void setPredecessor (Node<Type> *predecessor) noexcept {
		_predecessor = predecessor;
	}
	
	void setData (const Type &data) noexcept {
		_data = data;
	}


	// ----------------------------------------------------------------------
	// ----------------------------------------------------------------------

	// TODO: refactoring
	bool isShallowEqual (const Node<Type> &node) const noexcept {
		if ( _data == node._data &&
			_sucessor == node._sucessor &&
			_predecessor == node._predecessor ) {
			return true;
		}


		return false;
	}

	Node<Type> &operator= (const Node<Type> &node) {
		_sucessor = node._sucessor;
		_predecessor = node._predecessor;
		_data = node._data;
	}

	Node<Type> &operator= (const Type &data) {
		_data = data;
	}
	
	bool operator> (const Node<Type> &node) const noexcept {
		return _data > node._data;
	}
	
	bool operator< (const Node<Type> &node) const noexcept {
		return _data < node._data;
	}
	
	bool operator== (const Node<Type> &node) const noexcept {
		return _data == node._data;
	}

	bool operator!= (const Node<Type> &node) const noexcept {
		return !(*this == node);
	}

	bool operator>= (const Node<Type> &node) const noexcept {
		return (_data == node._data) || (_data > node._data);
	}

	bool operator<= (const Node<Type> &node) const noexcept {
		return (_data == node._data) || (_data < node._data);
	}

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


template<class Type> std::ostream &operator<< (std::ostream &output,
											   const Node<Type> &node) {
	output << node._data;


	return output;
}
