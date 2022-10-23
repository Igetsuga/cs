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
        if ( LinkedList<Type>::_size != 0 ) {
            while ( it_pos != this->end() ) {
                if ( *it_pos >= data ) { std::cout << "break"; break; }
                it_pos++; std::cout << "+";
            }

            return this->LinkedListIterated<Type>::insert(it_pos, data);
        }
        else {
            LinkedList<Type>::push_front(data);
            return this->begin();
        }
    }
};

