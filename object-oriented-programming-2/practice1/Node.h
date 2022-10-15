/*****************************************************************//**
 * \file   Node.h
 * \brief  Заголовочный файл объявления класса `Node`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера. Класс реализован через указатели.
 * Опеределение класса смотри в файле `Node.cpp`.
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
		  Node<Type> *sucessor = nullptr,
		  Node<Type> *predecessor = nullptr);

	~Node ();



	const Node<Type> *GetSucessor() const noexcept;
	const Node<Type> *GetPredecessor() const noexcept;
	const Type &GetData() const noexcept;



	void SetSucessor (const Node<Type> *sucessor) noexcept;
	void SetPredecessor (const Node<Type> *predecessor) noexcept;
	void SetData (const Type &data) noexcept;


	bool DeepEqual (const Node<Type> &node) const noexcept;

	Node<Type> &operator= (const Node<Type> &node);

	bool operator== (const Node<Type> &node) const noexcept;

	bool operator!= (const Node<Type> &node) const noexcept;

	const Type &operator*() const;

	template<class Type> friend std::ostream &operator<< (std::ostream &output,
														  const Node<Type> &node);
private:
	Node<Type> *_sucessor;
	Node<Type> *_predecessor;
	Type        _data;
};

