#pragma once
#include "Node.h"


template<class Type> class BinaryTree {
public:

	BinaryTree<Type>();

	~BinaryTree<Type>();



	virtual const Node<Type> *getRoot() const noexcept;


	virtual const Node<Type> *push (const Node<Type> *node) noexcept;


	virtual const Node<Type> *push (const Type &data) noexcept;


	virtual void pop (const Node<Type> *node) noexcept;


	virtual Node<Type> *min (Node<Type> *node = nullptr) const noexcept;


	virtual Node<Type> *max (Node<Type> *node = nullptr) const noexcept;


	virtual Node<Type> *find (const Type &data) const noexcept;

	//три обхода дерева
	virtual void PreOrder (Node<Type> *N, void (*f)(Node<Type> *)) const noexcept;

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder (Node<Type> *N, void (*f)(Node<Type> *)) const noexcept;


	virtual void PostOrder (Node<Type> *N, void (*f)(Node<Type> *)) const noexcept;


protected:
	virtual Node<Type> *push_R (Node<Type> *N, Node<Type> *Current) noexcept;

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<Type> *find_R (Type data, Node<Type> *Current) const noexcept;
	
	Node<Type> *_root;
};

