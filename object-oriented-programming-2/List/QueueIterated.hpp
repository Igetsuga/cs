#pragma once

#include "LinkedListIterated.hpp"

template<class Type> class QueueIterated : public LinkedListIterated<Type> 
{
    //template<class Type> using Iterator = LinkedList<Type>::Iterator;
public:

    QueueIterated() = default;
    
    virtual ~QueueIterated() = default;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual LinkedListIterated<Type>::Iterator insert (const Type &data) {

        LinkedListIterated<Type>::push_back(data);
        
        return LinkedListIterated<Type>::Iterator(this->end());
    }

    virtual LinkedListIterated<Type>::const_iterator erase() {
        
        auto itt = LinkedListIterated<Type>::erase(this->begin());
        
        return itt;
    }
};

