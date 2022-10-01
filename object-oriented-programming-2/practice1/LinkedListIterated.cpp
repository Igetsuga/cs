#include "LinkedListIterated.h"

template<class Type> using LLIT = LinkedListIterated<Type>;

template<class Type>
LLIT<Type>::LLLIT<Type> begin() {
	LLIT<Type> iterator = LinkedList<Type>::_begin;


	return it;
}
LLLIT<Type> end() {
	LLLIT<Type> iterator = LinkedList<Type>::_end;


	return it;
}