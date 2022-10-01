#pragma once
#include <iterator>
#include "Node.h"

namespace LinkedList {

template<class Type>
class Iterator : public std::iterator<std::input_iterator_tag, Type> {
public:


	Iterator();

	Iterator(Node<Type> *node);

	Iterator(const Iterator<Type> *iterator);



	Iterator<Type> &operator=(const Iterator *iterator) noexcept;

	Iterator<Type> &operator=(const Node<Type> &node) noexcept;



	bool operator!=(Iterator<Type> const &iterator) const noexcept;
	bool operator==(Iterator<Type> const &iterator) const noexcept;



	const Node<Type> &operator*();

	Iterator<Type> *operator++();

	Iterator<Type> *operator++(int steps_move);

private:
	Node<Type> *_iterator;
};
}
