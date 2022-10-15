#pragma once
#include "LinkedListIterated.h"

template<class Type>
class QueueIterated : public LinkedListIterated<Type> {


    QueueIterated() : LinkedListIterated<Type>() {};

    virtual ~QueueIterated() = default;



    template<class Type>
    void LinkedList<Type>::push(const Type &data) {
        IT<Type> iteratorCurrent = QueueIterated<Type>::LinkedListIterated.begin();

        for ( int it = 0; it < _size; it++ ) {
            iteratorCurrent++();
        }

        Node<Type> *newLastNode = new Node<Type>(data, nullptr, *iteratorCurrent);
        (*iteratorCurrent)->SetSucessor(newLastNode);
        
        LinkedList<Type>::_size++;
    }

    
    template<class Type>
    const Node<Type> *LinkedList<Type>::pop() {
        IT<Type> iteratorCurrent = QueueIterated<Type>::LinkedListIterated.begin();

        Node<Type> *newFirstNode = (*iteratorCurrent)->GetSucessor();
        newFirstNode->SetPredecessor(nullptr);
        
        delete *iteratorCurrent;

        LinkedList<Type>::_size--;
    }

};

