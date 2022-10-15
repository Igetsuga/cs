#pragma once
#include "LinkedList.h"
#include "Iterator.h"

template<class Type> using IT = LList::Iterator<Type>;


template<class Type> class LinkedListIterated : public LinkedList<Type> {
public:


	LinkedListIterated();

	virtual ~LinkedListIterated();


	/**
	 * Метод позволяет получить итератор начала контейнера.
	 *
	 * \return Итератор начала контейнера.
	 */
	template<class otherType> IT<Type> begin() {
		IT<Type> iterator = LinkedList<Type>::_begin;
	
	
		return iterator;
	}

	/**
	 * Метод позволяет получить итератор конца контейнера.
	 *
	 * \return Итератор конца контейнера.
	 */
	template<class otherType> IT<Type> end() {
		IT<Type> iterator = LinkedList<Type>::_end;


		return iterator;
	}
};


//using namespace std;
//
//template<typename> struct IT {};
//
//template<class Type> class LinkedListIterated {
//public:
////-----------------vvvvvvv-------------------->changed this to NewType
//	template<class NewType> IT<Type> begin();
//
//
//};
////this is how you defined the memeber function template begin
//template<class Type>
//template<class NewType>
//IT<Type> LinkedListIterated<Type>::begin() {
//   //code here
//
//	return {};
//}