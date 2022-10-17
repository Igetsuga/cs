#pragma once
#include "LinkedList.h"
#include "Iterator.h"


template<class Type> class LinkedListIterated : public LinkedList<Type> {
public:
	
	friend class Iterator<Type>;

	LinkedListIterated() {
		std::cout << '\n' << "LinkedListIterated has been created" << '\n';
	}

	~LinkedListIterated() {
		std::cout << "cool destructor";
	}
	

	/**
	 * Метод позволяет получить итератор начала контейнера.
	 *
	 * \return Итератор начала контейнера.
	 */
	Iterator<Type> begin() {
		Iterator<Type> iterator = LinkedList<Type>::_begin;
	
	
		return iterator;
	}

	/**
	 * Метод позволяет получить итератор конца контейнера.
	 *
	 * \return Итератор конца контейнера.
	 */
	Iterator<Type> end() {
		Iterator<Type> iterator = LinkedList<Type>::_end;


		return iterator;
	}
};


//using namespace std;
//
//template<typename> struct Iterator {};
//
//template<class Type> class LinkedListIterated {
//public:
////-----------------vvvvvvv-------------------->changed this to NewType
//	template<class NewType> Iterator<Type> begin();
//
//
//};
////this is how you defined the memeber function template begin
//template<class Type>
//template<class NewType>
//Iterator<Type> LinkedListIterated<Type>::begin() {
//   //code here
//
//	return {};
//}