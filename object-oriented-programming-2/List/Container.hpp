#pragma once

#include "QueueIterated.hpp"

template<class Type> class Container : public QueueIterated<Type> 
{
public:

    Container() = default;
    
    ~Container() = default;

    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------

    virtual LinkedListIterated<Type>::Iterator insert (const Type &data) final {
        
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
};

