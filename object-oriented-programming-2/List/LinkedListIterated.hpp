/*****************************************************************//**
 * \file   LinkedListIterated.h
 * \brief  Файл реализации параметризованного класса `LinkedListIterated`.
 * 
 * \author  Sirazetdinov Rustem
 * \version 
 * \date    October 2022
 *********************************************************************/
#pragma once


#include "LinkedList.hpp"
#include <iterator>

// TODO: template<class Type> class ... : public IListIterated, public LinkedList<Type>
// how to override that without multiple inheritance??
/**
 * Класс полностью наследует интейфейс родительского класса, добавляя к нему опции работы 
 * с итерирующими объектами.
 */
template<class Type> class LinkedListIterated : public LinkedList<Type>
{
public:
    
    /**
     * Класс представляет собой итерирующий объект.
     */
    class Iterator : public std::iterator<std::input_iterator_tag, Type> {
    public:

        

        Iterator() {
            std::cout << "Iterator had been created" << nline;
            _iterator = nullptr;
        }

        Iterator (Node<Type> *node) {
            _iterator = node;
        }

        /*operator Iterator() {
            Iterator::_iterator = const_cast<Node<Type>*>(const_iterator::_const_iterator);
        }*/

        //Iterator (const_iterator c_it) {}

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

        Iterator operator+(const int v) noexcept {
            for ( int i = 0; i < v; i++ ) {
                if ( this == nullptr ) {
                    break;
                }
                else {
                    ++(*this);
                }
            }

            return *this;
        }

        Iterator operator-(const int v) noexcept {
            for ( int i = 0; i < v; i++ ) {
                if ( this == nullptr ) {
                    break;
                }
                else {
                    --(*this);
                }
            }

            return *this;
        }

        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------

        Node<Type> *getNode() const noexcept {
            return _iterator;
        }

    private:
        Node<Type> *_iterator;
        friend class LinkedListIterated<Type>::const_iterator;
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
            _const_iterator = const_cast<const Node<Type>*>(iterator._iterator);
        }

        const_iterator (const const_iterator &itt) {
            _const_iterator = itt._const_iterator;
        }

        const_iterator (const Type &data) {
            _const_iterator = new Node<Type>(data);
            _const_iterator = const_cast<const Node<Type>*>(_const_iterator);
        }


        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------


        bool operator== (const const_iterator itt) const noexcept {
            return _const_iterator == itt._const_iterator;
        }

        bool operator!= (const const_iterator itt) const noexcept {
            return _const_iterator != itt._const_iterator;
        }

        const Node<Type> &operator* () const {
            if ( this == nullptr ) {
                throw std::exception("Method LIT<Type>::const_iterator::operator*(): this == nullptr");
            }
            return *_const_iterator;
        }


        // ----------------------------------------------------------------------
        // ----------------------------------------------------------------------

        const Node<Type> *getNode() const noexcept {
            return _const_iterator;
        }

    private:
        const Node<Type> *_const_iterator;
    };


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    LinkedListIterated() {
        std::cout << "LinkedListIterated had been created";
    }

    virtual ~LinkedListIterated() = default;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------

    // Невозможна вставка в конец. Реализация 1. Более правильная, но медленная 
    // из-за дополнительных неявных преобразований.
    virtual Iterator insert (const_iterator const_pos, const Type &data) final {
        if ( const_pos == nullptr ) {
            throw std::exception("Method LIT<Type>::insert(...): pos = nullptr");
        }

        Iterator pos = const_cast<Node<Type>*>(const_pos.getNode());

        // Костыль
        if ( pos == this->begin() ) {
            this->push_front(data);
        }
        else {
            Node<Type> *node_pos = pos.getNode();
            Node<Type> *nodeNew = new Node<Type>(data, pos.getNode(), node_pos->getPredecessor());

            (node_pos->getPredecessor())->setSucessor(nodeNew);
            node_pos->setPredecessor(nodeNew);

            LinkedList<Type>::_size += 1;
        }
        

        return --pos;
    }
    
    // Невозможна вставка в конец. Реализация 2. Не по канону, но быстрее.
    //virtual Iterator insert (const Iterator const_pos, const Type &data) final {
    //    if ( const_pos == nullptr ) {
    //        throw std::exception("Method LIT<Type>::insert(...): pos = nullptr");
    //    }

    //    Iterator pos = const_pos;

    //    // Костыль
    //    if ( pos == this->begin() ) {
    //        this->push_front(data);
    //    }
    //    else {
    //        Node<Type> *nodeNew = new Node<Type>(data, pos.getNode(), pos.getNode()->getPredecessor());

    //        (pos.getNode()->getPredecessor())->setSucessor(nodeNew);
    //        pos.getNode()->setPredecessor(nodeNew);

    //        LinkedList<Type>::_size += 1;
    //    }
    //    

    //    return --pos;
    //}


    virtual const_iterator erase (const_iterator const_pos) final {
        if ( const_pos == nullptr ) {
            throw std::exception("Method LIT<Type>::erase(...): pos = nullptr");
        }

        Iterator pos = const_cast<Node<Type>*>(const_pos.getNode());

        // Костыль
        if ( pos == this->begin() ) {
            this->pop_front();
        }
        else if ( pos == this->end() ) {
            this->pop_back();
        }
        else {
            Node<Type> *node_pos = pos.getNode();
            (node_pos->getPredecessor())->setSucessor(node_pos->getSucessor());
            (node_pos->getSucessor())->setPredecessor(node_pos->getPredecessor());
            node_pos = nullptr;
            LinkedList<Type>::_size -= 1;
        }


        return const_pos;
    }

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

    virtual void print() const noexcept override {
        Iterator itt = this->begin();

        std::cout << nline << "{ : ";

        for ( int i = 0; i < LinkedList<Type>::_size; i++, itt++ ) {
            std::cout << *itt << " : ";
        }

        std::cout << "}; " << nline;
    }

    virtual void print_reverse() const noexcept override {
        Iterator itt = this->end();

        std::cout << nline << "{ : ";

        for ( int i = 0; i < LinkedList<Type>::_size; i++, itt-- ) {
            std::cout << *itt << " : ";
        }

        std::cout << "}; " << nline;
    }
};





