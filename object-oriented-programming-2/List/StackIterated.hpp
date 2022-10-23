#pragma once


template<class Type> class StackIterated : public LinkedListIterated<Type> {
public:

    StackIterated() = default;

    virtual ~StackIterated() = default;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    LinkedListIterated<Type>::Iterator insert (const Type & data) {

        LinkedListIterated<Type>::push_front(data);

        return LinkedListIterated<Type>::Iterator(this->end());
    }

    LinkedListIterated<Type>::const_iterator erase() {

        auto itt = LinkedListIterated<Type>::erase(this->begin());

        return itt;
    }
};



