#pragma once
#include "LinkedList.h"



template<class Type> class LinkedListIterated : public LinkedList<Type> {

public:
	LinkedListIterated() : LinkedList<Type>() {
		cout <<
			"\nIteratedLinkedList constructor";
	}
	virtual ~LinkedListIterated() {
		cout <<
			"\nIteratedLinkedList destructor";
	}
	ListIterator<T> iterator;
	ListIterator<T> begin() {
		ListIterator<T> it =
			LinkedList<Type>::head; return it;
	}
	ListIterator<T> end() {
		ListIterator<T> it =
			LinkedList<Type>::tail; return it;
	}
};