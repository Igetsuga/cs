#pragma once
#include "LinkedListIterated.h"

template<class Type>
class QueueIterated : public LinkedListIterated<Type> {


    QueueIterated() : LinkedListIterated<Type>() {};

    virtual ~QueueIterated() = default;



    
    void LinkedList<Type>::push (const Type &data) override {
        Iterator<Type> iteratorCurrent = this->LinkedListIterated<Type>::begin();

        if (LinkedList<Type>::_size != 0 )
        for ( int it = 0; it < LinkedList<Type>::_size++; it++ ) {
            iteratorCurrent++;
        }

        Node<Type> *newLastNode = new Node<Type>(data, nullptr, iteratorCurrent._iterator);
        
        if ( LinkedList<Type>::_size == 0 ) {
            LinkedList<Type>::_end = LinkedList<Type>::_begin = newLastNode;
        }
        else {
            iteratorCurrent._iterator->Node<Type>::SetSucessor(newLastNode);
            LinkedList<Type>::_end = newLastNode;
        }
        
        LinkedList<Type>::_size++;
    }

    
    
    const Node<Type> *pop() override {
        if ( LinkedList<Type>::_size == 0 ) {
            throw std::bad_alloc("Method LinkedList<Type>::pop() : size = 0");
        }
        else {
            Iterator<Type> iteratorCurrent = this->LinkedListIterated<Type>::begin();
            Type nodeDeleted = iteratorCurrent._iterator;

            if ( LinkedList<Type>::_size == 1 ) {
                delete LinkedList<Type>::_begin;
                LinkedList<Type>::_begin = LinkedList<Type>::_end = nullptr;
            }
            else {
                Node<Type> *newFirstNode = (iteratorCurrent++)._iterator;
                newFirstNode->SetPredecessor(nullptr);
                
                delete LinkedList<Type>::_begin;
                LinkedList<Type>::_begin = newFirstNode;
            } 
            LinkedList<Type>::_size--;


            return nodeDeleted;
        }
    }

};

