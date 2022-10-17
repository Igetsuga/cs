/*****************************************************************//**
 * \file    Iterator.h
 * \brief   Заголовочный файл с объявлением класса `Iterator`.
 * 
 * \author  Sirazetdinov Rustem
 * \version
 * \date    October 2022
 *********************************************************************/
#pragma once
#include <iterator>
#include "Node.h"


template<class Type>
class Iterator : public std::iterator<std::input_iterator_tag, Type> {
public:


	Iterator();

	Iterator(Node<Type> *node);

	Iterator(const Iterator<Type> &iterator);

	~Iterator();


	Node<Type> *getNode();


	Iterator<Type> &operator= (const Iterator<Type> &iterator) noexcept;

	Iterator<Type> &operator= (const Node<Type> &node) noexcept;



	bool operator!= (Iterator<Type> const &iterator) const noexcept;
	bool operator== (Iterator<Type> const &iterator) const noexcept;



	Node<Type> &operator*();

	Iterator<Type> &operator++();
	
	Iterator<Type> &operator--();

	Iterator<Type> &operator++ (int steps_move);

private:
	Node<Type> *_iterator;
};

