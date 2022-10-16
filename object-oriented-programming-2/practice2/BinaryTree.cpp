#include "BinaryTree.h"


template<class Type> BinaryTree<Type>::BinaryTree() { _root = nullptr; }

// TODO: destructor
template<class Type> BinaryTree<Type>::~BinaryTree() {

}


template<class Type> const Node<Type> *BinaryTree<Type>::getRoot() const noexcept {
    return _root;
}


template<class Type> const Node<Type> *BinaryTree<Type>::push (const Node<Type> *node) noexcept {
    return push_R(node, _root);
}


template<class Type> const Node<Type> *BinaryTree<Type>::push (const Type &data) noexcept {
    Node<Type> *node = new Node<Type>(data);


    return push_R(node, _root);
}

// TODO: pop
template<class Type> void BinaryTree<Type>::pop (const Node<Type> *node) noexcept {

}


template<class Type> Node<Type> *BinaryTree<Type>::min (Node<Type> *node) const noexcept {
	if ( _root == nullptr ) { return nullptr; }

	if ( node == nullptr ) {
		node = _root;
	}


	Node<Type> *nodeNextLeft(node->getLeft());

	while ( nodeNextLeft != nullptr ) {
		node = nodeNextLeft;
		nodeNextLeft = node->getLeft();
	}


	return node;
}


template<class Type> Node<Type> *BinaryTree<Type>::max (Node<Type> *node) const noexcept {
	if ( _root == nullptr ) { return nullptr; }

	if ( node == nullptr ) {
		node = _root;
	}


	Node<Type> *nodeNextRight(node->getRight());

	while ( nodeNextRight != nullptr ) {
		node = nodeNextRight;
		nodeNextRight = node->getRight();
	}


	return node;
}


template<class Type> Node<Type> *BinaryTree<Type>::find (const Type &data) const noexcept {
	return find_R(data, _root);
}

// TODO: preOrder
template<class Type> void BinaryTree<Type>::PreOrder (Node<Type> *N, void (*f)(Node<Type> *)) const noexcept {
	if ( N != nullptr )
		f(N);
	if ( N != nullptr && N->getLeft() != nullptr )
		PreOrder(N->getLeft(), f);
	if ( N != nullptr && N->getRight() != nullptr )
		PreOrder(N->getRight(), f);
}

// TODO: inOrder
template<class Type> void BinaryTree<Type>::InOrder (Node<Type> *N, void (*f)(Node<Type> *)) const noexcept {
	if ( N != nullptr && N->getLeft() != nullptr )
		InOrder(N->getLeft(), f);
	if ( N != nullptr )
		f(N);
	if ( N != nullptr && N->getRight() != nullptr )
		InOrder(N->getRight(), f);
}

// TODO: postOrder
template<class Type> void BinaryTree<Type>::PostOrder (Node<Type> *N, void (*f)(Node<Type> *)) const noexcept {
	if ( N != nullptr && N->getLeft() != nullptr )
		PostOrder(N->getLeft(), f);
	if ( N != nullptr && N->getRight() != nullptr )
		PostOrder(N->getRight(), f);
	if ( N != nullptr )
		f(N);
}

// TODO: push_R
template<class Type> Node<Type> *BinaryTree<Type>::push_R (Node<Type> *N, Node<Type> *Current) noexcept {
	if ( N == nullptr ) return nullptr;
	if ( _root == nullptr ) {
		_root = N;
		return N;
	}

	if ( Current->getData() > N->getData() ) {
		//идем влево
		if ( Current->getLeft() != nullptr )
			Current->setLeft(push_R(N, Current->getLeft()));
		else
			Current->setLeft(N);
		Current->getLeft()->setParent(Current);
	}
	if ( Current->getData() < N->getData() ) {
		//идем вправо
		if ( Current->getRight() != nullptr )
			Current->setRight(push_R(N, Current->getRight()));
		else
			Current->setRight(N);
		Current->getRight()->setParent(Current);
	}
	if ( Current->getData() == N->getData() )
		//нашли совпадение
		;
	//для несбалансированного дерева поиска
	return N;
}

// TODO: find_R
template<class Type> Node<Type> *BinaryTree<Type>::find_R (Type data, Node<Type> *Current) const noexcept {
	//база рекурсии
	if ( Current == nullptr ) return nullptr;

	if ( Current->getData() == data ) return Current;

	//рекурсивный вызов
	if ( Current->getData() > data ) return find_R(data, Current->getLeft());

	if ( Current->getData() < data ) return find_R(data, Current->getRight());


}
