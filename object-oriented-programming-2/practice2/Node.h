/*****************************************************************//**
 * \file   Node.h
 * \brief  Заголовочный файл объявления класса `Node`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера. Класс реализован через указатели.
 * Определение класса смотри в файле `Node.cpp`.
 *
 * \author Sirazetdinov Rustem
 * \version
 * \date   September 2022
 *********************************************************************/
#pragma once
#include <iostream>

/**
* /brief Класс представляет собой обочку, которая покрывает все элементы связного списка.
*
* Класс реализован через обычные указатели.
*/
template<class Type> class Node {
public:

	Node (const Type &data,
		  size_t     &height,
		  Node<Type> *parent = nullptr,
		  Node<Type> *left = nullptr,
		  Node<Type> *right = nullptr
			);

	~Node ();



	const Node<Type> *getParent() const noexcept;
	const Node<Type> *getLeft() const noexcept;
	const Node<Type> *getRight() const noexcept;
	const Type &getData() const noexcept;
	const size_t &getHeight() const noexcept;

	
	void setParent (const Node<Type> *parent) noexcept;
	void setLeft (const Node<Type> *left) noexcept;
	void setRight (const Node<Type> *right) noexcept;
	void setData (const Type &data) noexcept;
	void setHeight (const size_t &height);
	

	friend std::ostream &operator<< (std::ostream &output,
														  const Node<Type> &node);
private:
	Node<Type> *_left;
	Node<Type> *_right;
	Node<Type> *_parent;
	Type        _data;
	size_t      _height;
};


