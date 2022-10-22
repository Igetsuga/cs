/*****************************************************************//**
 * \file   List.h
 * \brief  Заголовочный файл объявления абстрактного класса List.
 * 
 * \author  Sirazetdinov Rustem
 * \version
 * \date    October 2022
 *********************************************************************/
#pragma once

#include "Node.h"

/**
 * Абстрактный класс List.
 */
template<class Type> class IList 
{
public:

    virtual Type &front() = 0;
    
    virtual Type &back() = 0;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual bool empty() const = 0;
    
    virtual size_t size() const = 0;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual void clear() = 0;
    
    virtual void insert (const Type &data, const int &pos) = 0;
    
    virtual const Node<Type> *erase (const int &pos) = 0;
    
    virtual void push_back (const Type &data) = 0;
    
    virtual const Node<Type> *pop_back() = 0;
    
    virtual void push_front (const Type &data) = 0;
    
    virtual const Node<Type> *pop_front() = 0;
};

