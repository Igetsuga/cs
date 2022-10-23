#pragma once

#include "QueueIterated.hpp"

template<class Type> class Container : public QueueIterated<Type> 
{
public:

    Container();
    
    ~Container();

    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------

    virtual LinkedListIterated<Type>::Iterator insert (const Type &data) final;
};


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
Container<Type>::Container() = default;


template<class Type>
Container<Type>::~Container() = default;

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type>
typename LinkedListIterated<Type>::Iterator Container<Type>::insert (const Type & data) {

    Container<Type>::template Iterator it_pos = this->begin();
    if ( LinkedList<Type>::_size == 0 ) {
        this->push_back(data);
        return this->begin();
    }
    else {
        while ( *it_pos < data ) {
            if ( it_pos.getNode()->getSucessor() == nullptr ) {
                this->push_back(data);
                return this->end();
            }
            else {
                ++it_pos;
            }
        }
        return this->LinkedListIterated<Type>::insert(it_pos, data);

    }
}
