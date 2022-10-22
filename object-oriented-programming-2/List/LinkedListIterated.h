#pragma once


#include "LinkedList.h"
#include <iterator>


template<class Type> class LinkedListIterated : public LinkedList<Type>
{
public:
    
    class Iterator() : public std::iterator<std::input_iterator_tag, Type>{
    public:
        
        Iterator() {
            _node = nullptr;
        }


        Iterator (Node<Type> *node) {
            _node = node;
        }


        Iterator (const Type &data) {
            _node = new Node<Type>(data);
        }


        ~Iterator() {
            delete node;
        }



    protected:
        Node<Type> *_node;
    }


    LinkedListIterated() {
        std::cout << "LinkedListIterated had been created";
    }


    virtual ~LinkedListIterated() = default;

};

