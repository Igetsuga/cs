#pragma once

#include "IList.h"
#include <iostream>
#include <fstream>

template<class Type> class LinkedList : public IList<Type> {
public:
    // checked
    LinkedList() {
        _begin = _end = nullptr;
        _size = 0;
    }
    // checked
    LinkedList (const LinkedList<Type> &otherList) noexcept {
        std::cout << '\n' << "LinkedList copy constructor " << '\n';

        if ( otherList._size != 0 ) {
            _begin = new Node<Type>(otherList._begin->getData());

            Node<Type> *ptrCurrent = _begin;
            Node<Type> *ptrCurrentOther = otherList._begin;

            while ( ptrCurrentOther != otherList._end ) {

                Node<Type> *ptrCurrentNext = new Node<Type>((ptrCurrentOther->getSucessor())->getData(), nullptr, ptrCurrent);

                ptrCurrent->setSucessor(ptrCurrentNext);

                ptrCurrent = ptrCurrentNext;
                ptrCurrentOther = ptrCurrentOther->getSucessor();
            }
            _end = ptrCurrent;
        }
        else {
            _begin = _end = nullptr;
        }

        _size = otherList._size;
    }
    // checked
    LinkedList<Type> &operator= (const LinkedList<Type> &otherList) noexcept {
        this->clear();

        _size = otherList._size;
        _begin = _end = nullptr;

        if ( _size > 0 ) {
            Node<Type> *nodeOther = otherList._begin;
            Node<Type> *nodeThis = new Node<Type>(nodeOther->getData());
            Node<Type> *nextToThis = nullptr;

            _begin = nodeThis;
            nodeOther = nodeOther->getSucessor();

            while ( nodeOther != nullptr ) {
                nextToThis = new Node<Type>(nodeOther->getData(), nullptr, nodeThis);
                nodeThis->setSucessor(nextToThis);
                nodeThis = nextToThis;
                nodeOther = nodeOther->getSucessor();
            }
        }


        return *this;
    }
    // checked
    virtual ~LinkedList() {
        while ( _begin != nullptr ) {
            Node<Type> *nodeToDelete = _begin->getSucessor();
            delete _begin; _begin = nodeToDelete;
        }
        _size = 0;
    }



    Node<Type> *getBegin() const noexcept {
        return _begin;
    }
    Node<Type> *getEnd() const noexcept {
        return _end;
    }
    const size_t &size() const noexcept {
        return _size;
    }


    void setBegin (const Node<Type> *begin) {
        if ( begin->getSucessor() != _begin->getSucessor() ) {
            throw std::invalid_argument("Method LinkedList::setBegin(): pointers to sucessors don't match");
        }
        _begin = begin;
    }
    void setBegin (const Type &data) {
        _begin->setData(data);
    }
    
    void setEnd (const Node<Type> *end) {
        if ( end->getPredecessor() != _end->getPredecessor() ) {
            throw std::invalid_argument("Method LinkedList::setEnd(): pointers to predecessors don't match");
        }
        _end = end;
    }
    void setEnd (const Type &data) {
        _end->setData(data);
    }

    // TODO: insert
    virtual void insert (const Type &data, const int &pos) override {
        if ( pos <= 0 ) {
            throw std::out_of_range("LinkedList<Type>::insert: pos out of range");
        }
        /*if ( pos == 1 ) {
        this->pushFront(data);
    }
    else if ( pos == size_ + 1 ) {
        this->pushBack(data);
    }
    else {
        Object *objectCurrent = head_;

        for ( int position = 1; position < pos - 1; position++ ) {
            objectCurrent = objectCurrent->getSucessor();
        }

        Object *objectInsert = new Object(data, objectCurrent->getSucessor(), objectCurrent);

        objectCurrent->setSucessor(objectInsert);
        (objectInsert->getSucessor())->setPredecessor(objectInsert);

        size_++;
    }*/
    }
    // checked
    virtual void push (const Type &data) override {
        Node<Type> *beginNew = new Node<Type>(data, _begin, nullptr);
        if ( _size != 0 ) {
            _begin->setPredecessor(beginNew);
        }
        else {
            _end = beginNew;
        }

        _begin = beginNew;
        _size++;
    }

    // TODO: LinkedList<Type>::remove
    virtual const Node<Type> *remove (const int &pos) override {
        return nullptr;
    }
    // TODO: LinkedList<Type>::pop
    virtual const Node<Type> *pop() override {
        return nullptr;
    }
    //checked
    virtual void clear() {
        while ( _begin != nullptr ) {
            Node<Type> *nodeToDelete = _begin->getSucessor();
            delete _begin; _begin = nodeToDelete;
        }
        _size = 0;
    }


    //checked
    Node<Type> *operator[] (const int &pos) const {
        if ( pos < 0 || pos >= _size ) {
            throw std::out_of_range("Method LinkedList<Type>::operator[] : pos out of range");
        }

        Node<Type> *node = _begin;

        for ( int i = 0; i < pos; i++ ) {
            node = node->getSucessor();
        }


        return node;
    }


    //checked
    void print() const noexcept {
        Node<Type> *current = _begin;

        std::cout << nline << "{ : ";

        for ( int i = 0; i < _size; i++ ) {
            std::cout << current->getData() << " : ";
            current = current->getSucessor();
        }

        std::cout << "}; " << nline;
    }
    template<class otherType> friend std::ostream &operator<< (std::ostream &output,
                                                               LinkedList<otherType> &list) noexcept(false);



protected:
    Node<Type> *_begin;
    Node<Type> *_end;
    size_t      _size;
};

//ckecked
template<class Type> std::ostream &operator<< (std::ostream &output,
                                               LinkedList<Type> &list) noexcept(false) {
    if ( list.LinkedList<Type>::_size != 0 ) {
        Node<Type> *nodeCurrent = list.getBegin();

        if ( typeid(output).name() == typeid(std::ofstream).name() ) {
            if ( output.fail() ) {
                throw std::ios_base::failure("LinkedList<Type>::operator<< : could not open the file");
            }
            output << list.size() << nline;

            while ( nodeCurrent != nullptr ) {
                output << nodeCurrent->getData() << " ";
                nodeCurrent = nodeCurrent->getSucessor();
            }
        }
        else {
            output << nline << "Size: " << list._size << nline;

            int it = 0;
            while ( nodeCurrent != nullptr ) {
                output << "[" << it << "] = " << nodeCurrent->getData() << nline;
                nodeCurrent = nodeCurrent->getSucessor();
                it++;
            }
        }
    }


    return output;
}
