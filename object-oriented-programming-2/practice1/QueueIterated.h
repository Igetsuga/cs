#pragma once
#include "LinkedListIterated.h"

template<class Type>
class QueueIterated : public LinkedListIterated<Type> {
public:

    friend class Iterator<Type>;

    QueueIterated() {
        std::cout << '\n' << "QueueIterated has been created" << '\n';
    }

    virtual ~QueueIterated() = default;



    void push (const Type &data) override {
        Iterator<Type> iteratorCurrent = this->LinkedListIterated<Type>::begin();

        if (LinkedList<Type>::_size != 0 )
        for ( int it = 0; it < LinkedList<Type>::_size++; it++ ) {
            iteratorCurrent++;
        }

        Node<Type> *newLastNode = new Node<Type>(data, nullptr, iteratorCurrent.getNode());
        
        if ( LinkedList<Type>::_size == 0 ) {
            LinkedList<Type>::_end = LinkedList<Type>::_begin = newLastNode;
        }
        else {
            (iteratorCurrent.getNode())->Node<Type>::SetSucessor(newLastNode);
            LinkedList<Type>::_end = newLastNode;
        }
        
        LinkedList<Type>::_size++;
    }

    
    const Node<Type> *pop() override {
        if ( LinkedList<Type>::_size == 0 ) {
            throw std::invalid_argument("Method LinkedList<Type>::pop() : size = 0");
        }
        else {
            Iterator<Type> iteratorCurrent = this->LinkedListIterated<Type>::begin();
            Node<Type> *nodeDeleted = &(*iteratorCurrent);

            if ( LinkedList<Type>::_size == 1 ) {
                delete LinkedList<Type>::_begin;
                LinkedList<Type>::_begin = LinkedList<Type>::_end = nullptr;
            }
            else {
                Node<Type> *newFirstNode = &( *(iteratorCurrent++) );
                newFirstNode->SetPredecessor(nullptr);
                
                delete LinkedList<Type>::_begin;
                LinkedList<Type>::_begin = newFirstNode;
            } 
            LinkedList<Type>::_size--;


            return nodeDeleted;
        }
    }

};

