#pragma once

#include "BinaryTree.h"
#include "TreeIterator.h"

template<class Type> class BinaryTreeIterated : public BinaryTree<Type> {
public:

	TreeIterator() : BinaryTree<Type>();

	~TreeIterator();

	//TreeIterator() { ptr = NULL; T = NULL; }
	TreeIterator(Tree<Type> *t, Node<Type> *p) { ptr = p, T = t; }
	TreeIterator(const TreeIterator<Type> &it) { ptr = it.ptr; T = it.T; }

	TreeIterator<Type> begin() const {
		TreeIterator<Type> b TreeIterator<Type>(this, Tree<T>::min());
		return b;
	}
	TreeIterator<Type> end() const {
		TreeIterator<Type> e TreeIterator<Type>(this, Tree<T>::max());
		return e;
	}

	TreeIterator<Type> &operator= (const TreeIterator &it) { ptr = it.ptr; T = it.T; return *this; }
	TreeIterator<Type> &operator= (Node<Type> *p) { ptr = p; return *this; }

	bool operator!= (TreeIterator<Type> const &other) const { return ptr != other.ptr; };
	bool operator== (TreeIterator<Type> const &other) const { return ptr == other.ptr; };

	Node<Type> &operator*(); // возвращать пару ключ - значение

	// следующий по возрастанию
	TreeIterator<Type> &operator++() const;
	
	TreeIterator<Type> &operator++(int v) const;

	TreeIterator<Type> &operator--() const;

protected:
	Node<Type> *ptr;
	BinaryTree<Type> *T;
};