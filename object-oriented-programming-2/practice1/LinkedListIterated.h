#pragma once
#include "LinkedList.h"
#include "ListIterator.h"

template<class Type> using ILLLT = LinkedList::ListIterator<Type>;

template<class Type> class LinkedListIterated : public LinkedList<Type> {
public:
	LinkedListIterated() : LinkedList<Type>();
	
	virtual ~LinkedListIterated();



	LLLIT<Type> begin() {
		LLLIT<Type> iterator = LinkedList<Type>::_begin;
		
		
		return it;
	}
	LLLIT<Type> end() {
		LLLIT<Type> iterator = LinkedList<Type>::_end;
		
		
		return it;
	}
};