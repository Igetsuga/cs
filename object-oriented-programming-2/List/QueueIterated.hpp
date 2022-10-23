#pragma once

#include "LinkedListIterated.hpp"

template<class Type> class QueueIterated : public LinkedListIterated<Type> 
{
public:

    QueueIterated();
    
    virtual ~QueueIterated();


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual LinkedListIterated<Type>::Iterator insert (const Type &data);

    virtual LinkedListIterated<Type>::const_iterator erase();
};


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
QueueIterated<Type>::QueueIterated() = default;


template<class Type>
QueueIterated<Type>::~QueueIterated() = default;


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
typename LinkedListIterated<Type>::Iterator QueueIterated<Type>::insert (const Type & data) {

    LinkedListIterated<Type>::push_back(data);

    return LinkedListIterated<Type>::Iterator(this->end());
}


template<class Type>
typename LinkedListIterated<Type>::const_iterator QueueIterated<Type>::erase() {

    auto itt = LinkedListIterated<Type>::erase(this->begin());

    return itt;
}
