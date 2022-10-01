#pragma once
#include <iterator>
#include "Node.h"

namespace LinkedList {

	template<class Type>
	class ListIterator : public std::iterator<std::input_iterator_tag, Type> {
	public:


		ListIterator(); 
		
		ListIterator(Node<Type> *node);
		
		ListIterator(const ListIterator<Type> *iterator);

		
		
		ListIterator<Type> &operator=(const ListIterator *iterator) noexcept; 
		
		ListIterator<Type> &operator=(const Node<Type> &node) noexcept; 

		

		bool operator!=(ListIterator<Type> const &iterator) const noexcept;
		bool operator==(ListIterator<Type> const &iterator) const noexcept;
	


		const Node<Type> &operator*();
		
		ListIterator<Type> *operator++();

		ListIterator<Type> *operator++(int steps_move);

	private:
		Node<Type> *_iterator;
	};
}
