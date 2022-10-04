#include "LinkedListIterated.h"

template<class Type> using LLIT = LinkedListIterated<Type>;

//template<class Type>
//LinkedListIterated::LinkedListIterated<Type>() : LinkedList<Type>() {};

template<class Type>
LinkedListIterated<Type>::~LinkedListIterated() {};

/**
 * Метод позволяет получить итератор начала контейнера.
 *
 * \return Итератор начала контейнера.
 */
template<class Type>
LinkedList::Iterator<Type> LinkedListIterated<Type>::begin() {
	LinkedList::Iterator<Type> iterator = LinkedList<Type>::_begin;


	return iterator;
}

/**
 * Метод позволяет получить итератор конца контейнера.
 *
 * \return Итератор конца контейнера.
 */
template<class Type>
IT<Type> LinkedListIterated<Type>::end() {
	IT<Type> iterator = LinkedList<Type>::_end;


	return iterator;
}