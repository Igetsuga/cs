/*****************************************************************//**
 * \file   IList.h
 * \brief  Заголовочный файл объявления абстрактного класса IList.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    October 2022
 *********************************************************************/
#pragma once

#include "Node.hpp"

/**
 * Класс представляет собой интерфейс для контейнера `LinkedList<Type>` и других
 * унаследованных / основанных от него.
 */
template<class Type> class IList
{
public:

    virtual Type &front() const = 0;

    virtual Type &back() const = 0;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual bool empty() const = 0;

    virtual size_t size() const = 0;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual void clear() = 0;

    virtual void insert (const int &pos, const Type &data) = 0;

    virtual Type &erase (const int &pos) = 0;

    virtual void push_back (const Type &data) = 0;

    virtual Type &pop_back() = 0;

    virtual void push_front (const Type &data) = 0;

    virtual Type &pop_front() = 0;
};
