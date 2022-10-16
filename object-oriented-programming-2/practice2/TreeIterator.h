#pragma once
#include <iterator>

#include "Node.h"

// TODO: TreeIterator
template<class Type>
class TreeIterator : public std::iterator<std::input_iterator_tag, Type> {
public:
	
	TreeIterator();// { _iterator = nullptr;}
	
	TreeIterator (Node<Type> *node);
	
	TreeIterator (const TreeIterator<Type> &iterator);



	TreeIterator &operator= (const TreeIterator<Type> &iterator) const noexcept;
	
	TreeIterator &operator= (Node<Type> *node) const noexcept;

	bool operator!= (TreeIterator<Type> const &other) const noexcept;
	
	bool operator== (TreeIterator<Type> const &other) const noexcept;
	
	const Node<Type> &operator*() const noexcept;
	
	const TreeIterator &operator++() const noexcept;
	
	const TreeIterator &operator++ (int v) const noexcept;

private:
	Node<Type> *_iterator;
};

