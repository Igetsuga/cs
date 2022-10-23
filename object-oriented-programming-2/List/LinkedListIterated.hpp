/*****************************************************************//**
 * \file   LinkedListIterated.h
 * \brief  .
 * 
 * \author Sirazetdinov Rustem
 * \version
 * \date   October 2022
 *********************************************************************/
#pragma once


#include "LinkedList.hpp"
#include <iterator>

// TODO: template<class Type> class ... : public IListIterated, public LinkedList<Type>
// how to override that without multiple inheritance??
template<class Type> class LinkedListIterated : public LinkedList<Type>
{
public:
    
    // TODO: const_iterator
    class Iterator : public std::iterator<std::input_iterator_tag, Type> {
    public:

        Iterator() {
            std::cout << "Iterator had been created" << nline;
            _iterator = nullptr;
        }

        Iterator (Node<Type> *node) {
            _iterator = node;
        }

        Iterator (const Iterator &iterator) {
            _iterator = iterator._iterator;
        }

        Iterator (const Type &data) {
            _iterator = new Node<Type>(data);
        }

        ~Iterator() = default;


        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------


        bool operator== (const Iterator &itt) const noexcept {
            return _iterator == itt._iterator;
        }

        bool operator!= (const Iterator &itt) const noexcept{
            return _iterator != itt._iterator;
        }

        const Node<Type> &operator* () const {
            if ( this == nullptr ) {
                throw std::exception("Method LIT<Type>::Iterator::operator*(): this == nullptr");
            }
            return *_iterator;
        }

        Iterator &operator++() {
            if ( this == nullptr ) {
                throw std::exception("Method LIT<Type>::Iterator::operator++(): this == nullptr");
            }
            _iterator = _iterator->getSucessor();
            return *this;
        }

        Iterator operator++(int v) {
            if ( this == nullptr ) {
                throw std::exception("Method LIT<Type>::Iterator::operator++(int v): this = nullptr");
            }
            Iterator itt_this_old = *this;
            _iterator = _iterator->getSucessor();
            return itt_this_old;
        }

        Iterator &operator--() {
            if ( this == nullptr ) {
                throw std::exception("Method LIT<Type>::Iterator::operator--(): this = nullptr");
            }
            _iterator = _iterator->getPredecessor();
            return *this;
        }

        Iterator operator--(int v) {
            if ( this == nullptr ) {
                throw std::exception("Method LIT<Type>::Iterator::operator--(int v): this = nullptr");
            }
            Iterator itt_this_old = *this;
            _iterator = _iterator->getPredecessor();
            return itt_this_old;
        }


        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------

        const Node<Type> *getNode() const noexcept {
            return const_cast<const Node<Type>*>(_iterator);
        }

    protected:
        Node<Type> *_iterator;
    };


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    class const_iterator : public std::iterator<std::input_iterator_tag, Type> {
    public:

        const_iterator() {
            std::cout << "const_iterator had been created" << nline;
            _const_iterator = nullptr;
        }

        const_iterator (Node<Type> *node) {
            _const_iterator = const_cast<const Node<Type>*>(node);
        }

        const_iterator (const Iterator &iterator) {
            _const_iterator = const_cast<const Node<Type>*>(iterator._const_iterator);
        }

        const_iterator (const const_iterator &itt) {
            _const_iterator = itt._const_iterator;
        }

        const_iterator (const Type &data) {
            _const_iterator = new Node<Type>(data);
            _const_iterator = const_cast<const Node<Type>*>(_const_iterator);
        }

        ~const_iterator() {
            delete _const_iterator;
        }


        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------


        bool operator== (const const_iterator &itt) const noexcept {
            return _const_iterator == itt._const_iterator;
        }

        bool operator!= (const const_iterator &itt) const noexcept {
            return _const_iterator != itt._const_iterator;
        }

        const Node<Type> &operator* () {
            return *_const_iterator;
        }

        //TODO: add exception
        const_iterator &operator++() {
            //if (  ) { throw; }
            _const_iterator = _const_iterator->getSucessor();
            return *this;
        }

        //Iterator operator++(const Iterator &itt) {}
        //TODO: add exception
        const_iterator &operator--() {
            //if ( ) { throw; }
            _const_iterator = _const_iterator->getPredecessor();
            return *this;
        }


        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------

        const Node<Type> *getNode() const noexcept {
            return const_cast<const Node<Type>*>(_const_iterator);
        }

    protected:
        Node<Type> *_const_iterator;
    };


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    LinkedListIterated() {
        std::cout << "LinkedListIterated had been created";
    }

    virtual ~LinkedListIterated() = default;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    Iterator begin() const noexcept {
        return Iterator(LinkedList<Type>::_begin);
    }

    Iterator end() const noexcept {
        return Iterator(LinkedList<Type>::_end);
    }

    Iterator rbegin() const noexcept {
        return this->end();
    }

    Iterator rend() const noexcept {
        return this->begin();
    }


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------






};





