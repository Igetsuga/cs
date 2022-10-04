#pragma once
#include "LinkedList.h"
#include "Iterator.h"

template<class Type> using IT = LinkedList::Iterator<Type>;

template<class Type> class LinkedListIterated : public LinkedList<Type> {
public:

	typedef LinkedList<Type>

	//template<class Type>
		LinkedListIterated<Type>() : LinkedList<Type>() = default;

	virtual ~LinkedListIterated();


	template<class Type>
	LinkedList::Iterator<Type> begin();

	template<class Type>
	IT<Type> end();
};