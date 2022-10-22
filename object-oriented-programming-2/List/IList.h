/*****************************************************************//**
 * \file   List.h
 * \brief  ������������ ���� ���������� ������������ ������ List.
 * 
 * \author  Sirazetdinov Rustem
 * \version
 * \date    October 2022
 *********************************************************************/
#pragma once

#include "Node.h"

/**
 * ����������� ����� List.
 */
template<class Type> class IList 
{
public:

    virtual void push (const Type &data) = 0;
    
    virtual void insert (const Type &data, const int &pos) = 0;


    virtual const Node<Type> *pop() = 0;
    
    virtual const Node<Type> *remove (const int &pos) = 0;
};

