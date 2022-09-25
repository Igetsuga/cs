#include "LinkedList.h"



LinkedList()
{
	_head = _tail = nullptr;
	_size = 0;
	std::cout << nline << "Linked List Constructor" << nline;
}

LinkedList (const LinkedList &other)
{
	if ( other.size_ != 0 ) {
		head_ = new Object(other.head_->GetData()); // c. (*head_).data_ = (*other.head).data_;
													// c. (*head_).sucessor_ = nullptr;
													// c. (*head_).predecessor_ = nullptr;
		Object *this_ptr_current = head_;
		Object *other_ptr_current = other.head_;

		while ( other_ptr_current != other.tail_ ) {
			// c. (*this_ptr_current).data_ = (*other_ptr_current).data_; 
			// c. (*this_ptr_current).sucessor_ = nullptr;

			Object *this_ptr_new_sucessor = new Object((other_ptr_current->GetSucessor())->GetData(), nullptr, this_ptr_current);

			this_ptr_current->SetSucessor(this_ptr_new_sucessor);
			// (this_ptr_current->GetSucessor())->SetPredecessor( this_ptr_current );

			this_ptr_current = this_ptr_current->GetSucessor();
			other_ptr_current = other_ptr_current->GetSucessor();
		}
		tail_ = this_ptr_current;
	}
	else {
		head_ = tail_ = nullptr;
	}

	size_ = other.size_;
}

// destructor.
virtual ~LinkedList()
{
	// forceObjectDelete(_head);
	this->clear();
	std::cout << nline << "Linked List Destructor" << nline;
}

// for destructor. 
virtual void forceObjectDelete (Object *object) final {
	if ( object == nullptr ) { return; }

	Object<Type> *nextObjectDelete = object->GetSucessor();
	delete object;
	_size--;

	forceObjectDelete(nextObjectDelete);
}

virtual void clear() final {
	Object<Type> *next_after_head = _head;

	while ( next_after_head != nullptr ) {
		Object<Type> *next_after_head = _head->GetSucessor();
		delete _head; _head = next_after_head;
	}
	_size = 0;
}



const size_t size() const noexcept { return _size; }


const Object<Type> *GetHead() const noexcept {
	return _head;
}
void SetHead (const Object<Type> newHead) {
	_head = newHead;
}

const Object<Type> *GetTail() const noexcept {
	return _tail;
}
void SetTail (const Object<Type> newTail) {
	_tail = newTail;
}



virtual void push (const Type data) = 0;
virtual const Object<Type> *pop() = 0;

// O(N)
virtual Object<Type> *operator[] (const int &pos) {
	if ( pos < 0 || pos >= _size ) { throw std::out_of_range };

	Object<Type> *objectCurrent = _head;
	for ( int i = 0; i < pos; i++ ) {
		objectCurrent = objectCurrent->GetSucessor();
	}


	return objectCurrent;
}


template<class Type> friend std::ostream &operator<< (std::ostream &output,
														LinkedList<Type> &list);
template<class Type> friend std::istream &operator>> (std::istream &input,
														LinkedList<Type> &list);



// TODO выбросить исключение
template<class Type> std::ostream &operator<< (std::ostream &output, LinkedList<Type> &list)
{
	if ( list._size != 0 ) {
		Object<Type> *objectCurrent = list.GetHead();

		if ( typeid(output).name() == typeid(std::ofstream).name() ) {
			output << list.size() << nline;

			while ( objectCurrent != nullptr ) {
				output << objectCurrent->_data << " ";
				objectCurrent = objectCurrent->GetSucessor()
			}
		}
		else {
			output << nline << "Size: " << list._size << nline;

			int it = 0;
			while ( objectCurrent != nullptr ) {
				output << "[" << it << "] = " << objectCurrent->_data << nline;
			}
		}
	}


	return output;
}

template<class Type> std::istream &operator>> (std::istream &input, LinkedList<Type> &list)
{
	int size = 0; input >> size;

	list.clear();

	/// warning: требуется инициализация по умолчанию 
	Object<Type> objectCurrent;
	for ( int it = 0; it < size; it++ ) {
		input >> objectCurrent;
		list.push(objectCurrent);
	}


	return input;
}


