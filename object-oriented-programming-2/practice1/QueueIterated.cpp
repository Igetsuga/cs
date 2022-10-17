#include "QueueIterated.h"


template<class Type> void QueueIterated<Type>::master() const noexcept {
    std::cout << "YA ZDES TT";
}

template<class Type> void QueueIterated<Type>::push (const Type &data) {
        std::cout << "hello" << '\n';
}


template<class Type> const Node<Type> *QueueIterated<Type>::pop() {
        std::cout << "bingo" << '\n';


        return nullptr;
}