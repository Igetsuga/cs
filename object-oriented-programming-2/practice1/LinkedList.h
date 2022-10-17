/*****************************************************************//**
 * \file   LinkedList.h
 * \brief  Заголовочный файл объявления класса `LinkedList`.
 *
 * Реализация контейнера std::list<Type> через указатели.
 * Использован вспомогательный класс `Node`.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    September 2022
 *********************************************************************/
#pragma once
#include <iostream>
#include "Node.h"


template <class Type> class LinkedList {
public:

	LinkedList();

	LinkedList (const LinkedList<Type> &otherList);

	LinkedList<Type> &operator= (const LinkedList<Type> &otherList);

	virtual ~LinkedList();



	virtual void clear() final;

	const size_t size() const noexcept;



	const Node<Type> *GetBegin() const noexcept;
	const Node<Type> *GetEnd() const noexcept;

	void SetBegin (Node<Type> newBegin) noexcept;
	void SetEnd (Node<Type> newEnd) noexcept;


	
	virtual void push (const Type &data) = 0;
	//virtual void insert(const Type &data, const int &pos) = 0;



	virtual const Node<Type> *pop() = 0;
	//virtual const Node<Type> *remove(const int &pos) = 0;



	virtual Node<Type> &operator[](const int &pos) noexcept(false);


	
	virtual void print();

	template<class Type> friend std::ostream &operator<< (std::ostream &output,
														  LinkedList<Type> &list) noexcept(false);

protected:

	Node<Type> *_begin;
	Node<Type> *_end;
	size_t      _size;
};


