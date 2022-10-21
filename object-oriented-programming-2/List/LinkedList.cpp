#include "LinkedList.h"



template<class Type> LinkedList<Type>::LinkedList() {
    std::cout << "LinkedList had been created" << nline;
}


template<class Type> LinkedList<Type>::LinkedList (const LinkedList<Type> &otherList) noexcept {
	std::cout << '\n' << "LinkedList copy constructor " << '\n';

	if ( otherList._size != 0 ) {
		_begin = new Node<Type>(otherList._begin->getData());

		Node<Type> *ptrCurrent = _begin;
		Node<Type> *ptrCurrentOther = otherList._begin;

		while ( ptrCurrentOther != otherList._end ) {

			Node<Type> *ptrCurrentNext = new Node<Type>((ptrCurrentOther->getSucessor())->getData(), nullptr, ptrCurrent);

			ptrCurrent->setSucessor(ptrCurrentNext);

			ptrCurrent = ptrCurrentNext;
			ptrCurrentOther = ptrCurrentOther->getSucessor();
		}
		_end = ptrCurrent;
	}
	else {
		_begin = _end = nullptr;
	}

	_size = otherList._size;
}


template<class Type> LinkedList<Type> &LinkedList<Type>::operator= (const LinkedList<Type> &otherList) noexcept {
	this->clear();

	_size = otherList._size;
	_begin = nullptr;
	
	if ( _size > 0 ) {
		Node<Type> *nodeOther = otherList._begin;
		Node<Type> *nodeThis = new Node(nodeOther->_data);
		Node<Type> *nextToThis = nullptr;
		
		_begin = nodeThis;
		nodeOther = nodeOther->_sucessor;

		while ( nodeOther != nullptr ) {
			nextToThis = new Node(nodeOther->_data);
			nodeThis->_sucessor = nextToThis;
			nodeThis = nextToThis;
			nodeOther = nodeOther->_sucessor;
		}
	}


	return *this;
}

template<class Type> LinkedList<Type>::~LinkedList() {
	Node<Type> *nodeToDelete = _begin;

	while ( nodeToDelete != nullptr ) {
		Node<Type> *nodeToDelete = _begin->getSucessor();
		delete _begin; _begin = nodeToDelete;
	}
	_size = 0;
}


template<class Type> Node<Type> *LinkedList<Type>::getBegin() const noexcept {
	return _begin;
}


template<class Type> Node<Type> *LinkedList<Type>::getEnd() const noexcept {
	return _end;
}


template<class Type> const size_t &LinkedList<Type>::size() const noexcept {
	return _size;
}


template<class Type> void LinkedList<Type>::setBegin (const Node<Type> *begin) noexcept {
	_begin = begin;
}


template<class Type> void LinkedList<Type>::setEnd (const Node<Type> *end) noexcept {
	_end = end;
}


template<class Type> void LinkedList<Type>::insert (const Type &data, const int &pos) {
	if ( pos <= 0 ) { 
		throw std::out_of_range("LinkedList<Type>::insert: pos out of range");
	} 
	

	/*if ( pos == 1 ) {
		this->pushFront(data);
	}
	else if ( pos == size_ + 1 ) {
		this->pushBack(data);
	}
	else {
		Object *objectCurrent = head_;

		for ( int position = 1; position < pos - 1; position++ ) {
			objectCurrent = objectCurrent->getSucessor();
		}

		Object *objectInsert = new Object(data, objectCurrent->getSucessor(), objectCurrent);

		objectCurrent->setSucessor(objectInsert);
		(objectInsert->getSucessor())->setPredecessor(objectInsert);

		size_++;
	}*/
}


template<class Type> void LinkedList<Type>::push (const Type &data) {
	_begin = new Node<Type>(data, _begin);

	if ( _size == 0 ) {
		_end = _begin;
	}
	else {
		(_begin->getSucessor())->setPredecessor(_begin);
	}

	_size++;
}


template<class Type> const Node<Type> *LinkedList<Type>::remove (const int &pos) {

}


template<class Type> const Node<Type> *LinkedList<Type>::pop() {

}


template<class Type> const Node<Type> *LinkedList<Type>::operator[] (const int &pos) const {
	if ( pos < 0 || pos >= _size ) {
		throw std::out_of_range("Method LinkedList<Type>::operator[] : pos out of range");
	}
	
	Node<Type> *nodeOther = _begin;

	for ( int i = 0; i < pos; i++ ) {
		nodeOther = nodeOther->getSucessor();
	}


	return nodeOther;
}


template<class Type> void LinkedList<Type>::clear() {
	Node<Type> *nodeToDelete = _begin;

	while ( nodeToDelete != nullptr ) {
		Node<Type> *nodeToDelete = _begin->getSucessor();
		delete _begin; _begin = nodeToDelete;
	}
	_size = 0;
}


template<class Type> void LinkedList<Type>::print() const noexcept {
	Node<Type> *current = _begin;

	std::cout << nline << "{ : ";

	for ( int i = 0; i < _size; i++ ) {
		std::cout << current->getData() << " : ";
		current = current->getSucessor();
	}

	std::cout << "}; " << nline;
}


template<class Type> std::ostream &operator<< (std::ostream &output,
											   LinkedList<Type> &list) {
	if ( list._size != 0 ) {
		Node<Type> *nodeCurrent = list.getBegin();

		if ( typeid(output).name() == typeid(std::ofstream).name() ) {
			if ( output.fail() ) {
				throw std::ios_base::failure("LinkedList<Type>::operator<< : could not open the file");
			}
			output << list.size() << nline;

			while ( nodeCurrent != nullptr ) {
				output << nodeCurrent->_data << " ";
				nodeCurrent = nodeCurrent->getSucessor();
			}
		}
		else {
			output << nline << "Size: " << list._size << nline;

			int it = 0;
			while ( nodeCurrent != nullptr ) {
				output << "[" << it << "] = " << nodeCurrent->_data << nline;
			}
		}
	}


	return output;
}
