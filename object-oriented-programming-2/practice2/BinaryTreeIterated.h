#pragma once

#include "BinaryTree.h"
#include "TreeIterator.h"

template<class Type> class BinaryTreeIterated : public BinaryTree<Type> {
public:
	
	BinaryTreeIterated() : BinaryTree<Type>() {};

	~BinaryTreeIterated();

	TreeIterator<Type> begin() const;
	TreeIterator<Type> end() const;
};