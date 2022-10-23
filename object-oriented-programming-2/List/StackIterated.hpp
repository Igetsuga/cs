#pragma once


template<class Type> class StackIterated : public LinkedListIterated<Type> {
public:

    StackIterated();

    virtual ~StackIterated();


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    LinkedListIterated<Type>::Iterator insert (const Type &data);

    LinkedListIterated<Type>::const_iterator erase();
};


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
StackIterated<Type>::StackIterated() = default;


template<class Type>
StackIterated<Type>::~StackIterated() = default;


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
typename LinkedListIterated<Type>::Iterator StackIterated<Type>::insert (const Type & data) {

    LinkedListIterated<Type>::push_front(data);

    return LinkedListIterated<Type>::Iterator(this->end());
}

template<class Type>
typename LinkedListIterated<Type>::const_iterator StackIterated<Type>::erase() {

    auto itt = LinkedListIterated<Type>::erase(this->begin());

    return itt;
}
