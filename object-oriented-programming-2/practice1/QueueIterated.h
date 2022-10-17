#pragma once
#include "LinkedListIterated.h"


template<class Type>
class QueueIterated : public LinkedListIterated<Type> {
public:

    friend class Iterator<Type>;

    QueueIterated() {
        std::cout << '\n' << "QueueIterated has been created" << '\n';
    }

    virtual ~QueueIterated() = default;

    
    void master() const noexcept;

    void push (const Type &data) override;

    
    const Node<Type> *pop() override;

};

