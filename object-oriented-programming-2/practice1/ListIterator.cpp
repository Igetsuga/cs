#include "ListIterator.h"
using namespace LinkedList;

/**
 * Конструктор по умолчанию.
 * 
 */
template<class Type> LinkedList::ListIterator<Type>::ListIterator() {
    _iterator = nullptr;
}

/**
 * Конструктор преобразований. 
 * 
 * Конструктор преобразует тип `Node<Type>` в тип `ListIterator<Type>`.
 * 
 * \param node
 */
template<class Type> LinkedList::ListIterator<Type>::ListIterator (Node<Type> *node) {
    _iterator = node;
}

/**
 * Конструктор копий.
 * 
 * \param iterator
 */
template<class Type> LinkedList::ListIterator<Type>::ListIterator (const ListIterator<Type> *iterator) {
    _iterator = iterator._iterator;
}

/**
 * Перегрузка операторо присваисания, аргумент -- `ListIterator<Type>`.
 * 
 * 
 * \warning Shallow copy
 * \param iterator
 * \return Новый объект типа `ListIterator<Type>`, который смотрит на тот же адресс в памяти, который
 * занимает переданный объект.
 */
template<class Type>
ListIterator<Type> &LinkedList::ListIterator<Type>::operator= (const ListIterator *iterator) noexcept {
    _iterator = iterator._iterator;
    
    
    return *this;
}

/**
 * Перегрузка операторо присваивания(deep).
 *
 *
 * \warning Shallow copy
 * \param node
 * \return Новый объект типа `ListIterator<Type>`, который смотрит на тот же адресс в памяти, который
 * занимает переданный объект.
 */
template<class Type>
ListIterator<Type> &LinkedList::ListIterator<Type>::operator= (const Node<Type> &node) noexcept {
    _iterator = node; 


    return *this;
}

/**
 * Проверка неравенства объектов(shallow).
 * 
 * \param iterator
 * \return 
 */
template<class Type>
bool LinkedList::ListIterator<Type>::operator!= (ListIterator<Type> const &iterator) const noexcept {
    return (_iterator != iterator._iterator);
}

/**
 * Проверка равенства объектов(shallow).
 * 
 * \param iterator
 * \return 
 */
template<class Type>
bool LinkedList::ListIterator<Type>::operator== (ListIterator<Type> const &iterator) const noexcept {
    return (_iterator == iterator._iterator)
}

/**
 * Перегрузка оператора разыменования.
 * 
 * \return Ссылка на константный объект типа `Type`.
 */
template<class Type>
const Node<Type> &LinkedList::ListIterator<Type>::operator*() {
    if ( _iterator == nullptr ) {
        throw std::invalid_argument("LinkedList::ListIterator<Type> : operator*");
    }

    
    return *_iterator;
}


/**
 * Перегрузка оператора перехода к следующему итератору.
 * 
 * \return Указатель на следующий итератор.
 */
template<class Type> 
ListIterator<Type> *LinkedList::ListIterator<Type>::operator++() {
    if ( _iterator == nullptr || _iterator->GetSucessor() ) {
        throw std::invalid_argument("LinkedList::ListIterator<Type> : operator*");
    }

    _iterator = _iterator->GetSucessor();


    return this;
}

/**
 * Перегрузка оператора перехода на заданное количество шагов вперед к соот-му итеретору.
 *
 * \param move_steps
 * \return Указатель на итератор, находящийся на заданном расстоянии от данного.
 */
template<class Type>
ListIterator<Type> *LinkedList::ListIterator<Type>::operator++ (int move_steps) {
    if ( _iterator == nullptr ) {
        throw std::invalid_argument("LinkedList::ListIterator<Type> : operator*");
    }

    for ( int i = 0; i < move_steps; i++ ) {
        Node<Type> *iteratorNext = _iterator->GetSucessor();
        
        if ( iteratorNext->GetSucessor() == nullptr ) {
            throw std::invalid_argument("LinkedList::ListIterator<Type> : operator*");
        }

        _iterator = iteratorNext;
    }
    


    return this;
}




