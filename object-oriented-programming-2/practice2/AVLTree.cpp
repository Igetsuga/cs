#include "AVLTree.h"


template<class Type> Node<Type> *AVLTree<Type>::push (Node<Type> *node) {
    return push_R(node, BinaryTree<Type>::_root);
}


template<class Type> Node<Type> *AVLTree<Type>::push_R (const Node<Type> *node, const Node<Type> *Current) {
	//вызываем функцию push_R из базового класса
	Node<Type> *pushedNode = BinaryTree<Type>::push_R(node, Current);
	//применяем к добавленному узлу балансировку
	return Balance(Current);
}


template<class Type> Node<Type> *AVLTree<Type>::push (const Type &data) {
	Node<Type> *node = new Node<Type>;
	node->setData(data);
	return push_R(node, BinaryTree<Type>::_root);
}


template<class Type> void AVLTree<Type>::pop (const Node<Type> *node) {};


template<class Type> const int AVLTree<Type>::bfactor (const Node<Type> *node) const noexcept {
	int hl = 0;
	int hr = 0;
	if ( p->getLeft() != NULL )
		hl = p->getLeft()->getHeight();
	if ( p->getRight() != NULL )
		hr = p->getRight()->getHeight();
	return (hr - hl);
}


template<class Type> void AVLTree<Type>::fixHeight (const Node<Type> *node) noexcept {
	int hl = 0;
	int hr = 0;
	if ( p->getLeft() != NULL )
		hl = p->getLeft()->getHeight();
	if ( p->getRight() != NULL )
		hr = p->getRight()->getHeight();
	p->setHeight((hl > hr ? hl : hr) + 1);
}


template<class Type> const Node<Type> *AVLTree<Type>::RotateLeft (Node<Type> *q) noexcept {
	Node<Type> *p = q->getRight();

	q->setRight(p->getLeft());
	p->setLeft(q);

	if ( q != BinaryTree<Type>::root ) {

		if ( q->getParent()->getLeft() == q ) {
			q->getParent()->setLeft(p);
		}
		else {
			q->getParent()->setRight(p);
		}

	}
	else {
		BinaryTree<Type>::root = p;
	}

	p->setParent(q->getParent());
	q->setParent(p);
	q->getRight()->setParent(q);

	fixHeight(q);
	fixHeight(p);


	return p;
}


template<class Type> const Node<Type> *AVLTree<Type>::RotateRight (Node<Type> *p) noexcept {
	Node<Type> *q = p->getLeft();

// change children
	p->setLeft(q->getRight());
	q->setRight(p);

	if ( p != BinaryTree<Type>::root ) {

		if ( p->getParent()->getLeft() == p ) {
			p->getParent()->setLeft(q);
		}
		else {
			p->getParent()->setRight(q);
		}

	}
	else {
		BinaryTree<Type>::root = q;
	}

	// change parents
	q->setParent(q->getParent());
	p->setParent(q);
	if ( p->getLeft() != nullptr ) { p->getLeft()->setParent(p); }


	fixHeight(p);
	fixHeight(q);
	return q;
}


template<class Type> const Node<Type> *AVLTree<Type>::Balance ( Node<Type> *node) noexcept {
	fixHeight(p);
	if ( bfactor(p) == 2 ) {
		if ( bfactor(p->getRight()) < 0 ) {
			RotateRight(p->getRight());
		}
		return RotateRight(p);

	}
	if ( bfactor(p) == -2 ) {
		if ( bfactor(p->getLeft()) < 0 ) {
			RotateLeft(p->getLeft());
		}
		return RotateRight(p);
	}


	return p; // балансировка не нужна
}
