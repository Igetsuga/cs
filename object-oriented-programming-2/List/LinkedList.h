#pragma once

#include "List.h"

template<class Type> class LinkedList : public List<Type>
{
public:

    LinkedList();

    LinkedList (const LinkedList<Type> &otherList) noexcept;

    LinkedList<Type> &operator= (const LinkedList<Type> &otherList) noexcept;

    virtual ~LinkedList() override;



    Node<Type> *getBegin() const noexcept;
    Node<Type> *getEnd() const noexcept;
    const size_t &size() const noexcept;


    void setBegin (const Node<Type> *begin) noexcept;
    void setEnd (const Node<Type> *end) noexcept;



    virtual void insert (const Type &data, const int &pos) override;
    virtual void push (const Type &data) override;

    virtual const Node<Type> *remove (const int &pos) override;
    virtual const Node<Type> *pop() override;

    virtual void clear();



    const Node<Type> *operator[] (const int &pos) const;



    void print() const noexcept;
    template<class otherType> friend std::ostream &operator<< (std::ostream &output,
                                                               LinkedList<Type> &list) noexcept(false);
protected:
    Node<Type> *_begin;
    Node<Type> *_end;
    size_t      _size;
};

