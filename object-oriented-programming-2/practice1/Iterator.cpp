/*****************************************************************//**
 * \file    Iterator.cpp
 * \brief   Файл, содержащий определение класса `Iterator`.
 * 
 * \author  Sirazetdinov Rustem
 * \version
 * \date    October 2022
 *********************************************************************/
#include "Iterator.h"


/**
 * Конструктор по умолчанию.
 *
 */
template<class Type> Iterator<Type>::Iterator() {
    _iterator = nullptr;
}

/**
 * Конструктор преобразований.
 *
 * Конструктор преобразует тип `Node<Type>` в тип `Iterator<Type>`.
 *
 * \param node
 */
template<class Type> Iterator<Type>::Iterator (Node<Type> *node) {
    _iterator = node;
}

/**
 * Конструктор копий.
 *
 * \param iterator
 */
template<class Type> Iterator<Type>::Iterator (const Iterator<Type> &iterator) {
    _iterator = iterator._iterator;
}

/**
 * Деструктор.
 * 
 */
template<class Type> Iterator<Type>::~Iterator() = default;

template<class Type> Node<Type> *Iterator<Type>::getNode() {
    return _iterator;
}

/**
 * Перегрузка оператора `operator=`(shallow copy).
 *
 * 
 * \param iterator
 * 
 * \return Новый объект типа `Iterator<Type>`, который смотрит на тот же адресс в памяти, который
 * занимает переданный объект.
 */
template<class Type>
Iterator<Type> &Iterator<Type>::operator= (const Iterator<Type> &iterator) noexcept {
    _iterator = iterator._iterator;


    return *this;
}

/**
 * Перегрузка оператора `operator=`(shallow copy).
 *
 *
 * \param node
 *
 *  \return Новый объект типа `Iterator<Type>`, который смотрит на тот же адресс в памяти, который
 * занимает переданный объект.
 */
template<class Type>
Iterator<Type> &Iterator<Type>::operator= (const Node<Type> &node) noexcept {
    _iterator = node;


    return *this;
}

/**
 * Перегрузка оператора `operator!=`(shallow).
 *
 * \param iterator
 * 
 * \return `true`, если сравниваемые объекты смортят на разные
 * участки памяти, в противном случае `false`.
 */
template<class Type>
bool Iterator<Type>::operator!= (Iterator<Type> const &iterator) const noexcept {
    return (_iterator != iterator._iterator);
}

/**
 * Перегрузка оператора `operator==`(shallow).
 *
 * \param iterator
 * 
 * \return `true`, если сравниваемые объекты смортят на один и тот же
 * участок памяти, в противном случае `false`.
 */
template<class Type>
bool Iterator<Type>::operator== (Iterator<Type> const &iterator) const noexcept {
    return (_iterator == iterator._iterator);
}

/**
 * Перегрузка оператора `operator*`.
 *
 * \return Ссылку на константный объект типа `Type`.
 */
template<class Type>
Node<Type> &Iterator<Type>::operator*() {
    if ( _iterator == nullptr ) {
        throw std::invalid_argument("Iterator<Type> : operator* : _iterator == nullptr");
    }


    return *_iterator;
}


/**
 * Перегрузка оператора `operator++`.
 * 
 * Переход итератора к следующему.
 *
 * \return Указатель на следующий итератор.
 */
template<class Type>
Iterator<Type> &Iterator<Type>::operator++() {
    if ( _iterator == nullptr || _iterator->GetSucessor() == nullptr ) {
        throw std::invalid_argument("Iterator<Type> : operator++");
    }

    _iterator = _iterator->GetSucessor();


    return *this;
}

/**
 * Перегрузка оператора `operator--`.
 *
 * Переход итератора к предыдущему.
 *
 * \return Указатель на предыдущий итератор.
 */
template<class Type>
Iterator<Type> &Iterator<Type>::operator--() {
    if ( _iterator == nullptr || _iterator->GetSucessor() == nullptr ) {
        throw std::invalid_argument("Iterator<Type> : operator++");
    }

    _iterator = _iterator->GetPredecessor();


    return *this;
}

/**
 * Перегрузка оператора перехода на заданное количество шагов вперед к соот-му итератору.
 *
 * \param move_steps
 * \return Указатель на итератор, находящийся на заданном расстоянии от данного.
 */
template<class Type>
Iterator<Type> &Iterator<Type>::operator++ (int move_steps) {
    if ( _iterator == nullptr || _iterator->GetSucessor() == nullptr ) {
        throw std::invalid_argument("Iterator<Type> : operator++");
    }

    for ( int i = 0; i < move_steps; i++ ) {
        Node<Type> *iteratorNext = _iterator->GetSucessor();

        if ( iteratorNext->GetSucessor() == nullptr ) {
            throw std::invalid_argument("Iterator<Type> : operator++");
        }

        _iterator = iteratorNext;
    }



    return *this;
}




