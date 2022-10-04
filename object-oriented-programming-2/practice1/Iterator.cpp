#include "Iterator.h"
using namespace LinkedList;

/**
 * Конструктор по умолчанию.
 *
 */
template<class Type> LinkedList::Iterator<Type>::Iterator() {
    _iterator = nullptr;
}

/**
 * Конструктор преобразований.
 *
 * Конструктор преобразует тип `Node<Type>` в тип `Iterator<Type>`.
 *
 * \param node
 */
template<class Type> LinkedList::Iterator<Type>::Iterator (Node<Type> *node) {
    _iterator = node;
}

/**
 * Конструктор копий.
 *
 * \param iterator
 */
template<class Type> LinkedList::Iterator<Type>::Iterator (const Iterator<Type> *iterator) {
    _iterator = iterator._iterator;
}

/**
 * Перегрузка операторо присваисания, аргумент -- `Iterator<Type>`.
 *
 *
 * \warning Shallow copy
 * \param iterator
 * \return Новый объект типа `Iterator<Type>`, который смотрит на тот же адресс в памяти, который
 * занимает переданный объект.
 */
template<class Type>
Iterator<Type> &LinkedList::Iterator<Type>::operator= (const Iterator *iterator) noexcept {
    _iterator = iterator._iterator;


    return *this;
}

/**
 * Перегрузка операторо присваивания(deep).
 *
 *
 * \warning Shallow copy
 * \param node
 * \return Новый объект типа `Iterator<Type>`, который смотрит на тот же адресс в памяти, который
 * занимает переданный объект.
 */
template<class Type>
Iterator<Type> &LinkedList::Iterator<Type>::operator= (const Node<Type> &node) noexcept {
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
bool LinkedList::Iterator<Type>::operator!= (Iterator<Type> const &iterator) const noexcept {
    return (_iterator != iterator._iterator);
}

/**
 * Проверка равенства объектов(shallow).
 *
 * \param iterator
 * \return
 */
template<class Type>
bool LinkedList::Iterator<Type>::operator== (Iterator<Type> const &iterator) const noexcept {
    return (_iterator == iterator._iterator)
}

/**
 * Перегрузка оператора разыменования.
 *
 * \return Ссылка на константный объект типа `Type`.
 */
template<class Type>
const Node<Type> &LinkedList::Iterator<Type>::operator*() {
    if ( _iterator == nullptr ) {
        throw std::invalid_argument("LinkedList::Iterator<Type> : operator*");
    }


    return *_iterator;
}


/**
 * Перегрузка оператора перехода к следующему итератору.
 *
 * \return Указатель на следующий итератор.
 */
template<class Type>
Iterator<Type> *LinkedList::Iterator<Type>::operator++() {
    if ( _iterator == nullptr || _iterator->GetSucessor() ) {
        throw std::invalid_argument("LinkedList::Iterator<Type> : operator*");
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
Iterator<Type> *LinkedList::Iterator<Type>::operator++ (int move_steps) {
    if ( _iterator == nullptr ) {
        throw std::invalid_argument("LinkedList::Iterator<Type> : operator*");
    }

    for ( int i = 0; i < move_steps; i++ ) {
        Node<Type> *iteratorNext = _iterator->GetSucessor();

        if ( iteratorNext->GetSucessor() == nullptr ) {
            throw std::invalid_argument("LinkedList::Iterator<Type> : operator*");
        }

        _iterator = iteratorNext;
    }



    return this;
}




