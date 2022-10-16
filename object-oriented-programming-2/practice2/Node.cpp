/*****************************************************************//**
 * \file   Node.cpp
 * \brief  Файл определения класса `Node`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера. Класс реализован через указатели.
 * Объявление класса смотри в файле `Node.h`.
 *
 * \author Sirazetdinov Rustem
 * \version
 * \date   September 2022
 *********************************************************************/
#include "Node.h"

template<class Type> Node<Type>::Node (const Type &data,
									   unsigned char     &height,
									   Node<Type> *parent,
									   Node<Type> *left,
									   Node<Type> *right) {
	_parent = parent;
	_left = left;
	_right = right;
	_data = data;
	_height = height;
}

template<class Type> Node<Type>::Node (const Node<Type> &node) {
	_parent = node._parent;
	_left = node._left;
	_right = node._right;
	_data = node._data;
	_height = node._height;
}

template<class Type> Node<Type>::~Node () = default;

template<class Type> const Node<Type> *Node<Type>::getParent() const noexcept {
	return _parent;
}


template<class Type> const Node<Type> *Node<Type>::getLeft() const noexcept {
	return _left;
}


template<class Type> const Node<Type> *Node<Type>::getRight() const noexcept {
	return _right;
}


template<class Type> const Type &Node<Type>::getData() const noexcept {
	return _data;
}


template<class Type> const unsigned char &Node<Type>::getHeight() const noexcept {
	return _height;
}



template<class Type> void Node<Type>::setParent (const Node<Type> *parent) noexcept {
	_parent = parent;
}


template<class Type> void Node<Type>::setLeft (const Node<Type> *left) noexcept {
	_left = left;
}


template<class Type> void Node<Type>::setData (const Type &data) noexcept {
	_data = data;
}


template<class Type> void Node<Type>::setHeight (const unsigned char &height) {
	if ( height < 0 ) {
		throw std::invalid_argument("Method Node::setHeight() cant apply negative numbers");
	}
	
	_height = height;
}





/**
 * Перегрузка оператора `operator<<`.
 *
 * \param output
 * \param node
 * \return Ссылку на стандартный поток вывода.
 */
template<class Type> std::ostream &operator<< (std::ostream & output,
											   const Node<Type> &node) {
	output << node._data;


	return output;
}
