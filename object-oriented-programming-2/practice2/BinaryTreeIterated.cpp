#include "BinaryTreeIterated.h"


template<class Type> TreeIterator<Type> &BinaryTreeIterated<Type>::operator++() const {
    // p++
    if ( ptr != nullptr ) {
        if ( ptr->getRight() != nullptr ) {
            ptr = T->min(ptr->getRight());
        }
        else {
            if ( ptr->getParent() == nullptr ) {
                return *this;
            }
            Node<Type> *current = ptr->getParent();
            while ( current->getParent() != nullptr && current->getData() < ptr->getData() ) {
                current = current->getParent();
            }
            if ( current->getData() > ptr->getData() ) {
                ptr = current;
            }
        }
    }
    return *this;


}


template<class Type> TreeIterator<Type> &BinaryTreeIterated<Type>::operator++ (int v) const {
    // p++
    return *this++;
}

template<class Type> TreeIterator<Type> &BinaryTreeIterated<Type>::operator--() const {

}

template<class Type> Node<Type> &BinaryTreeIterated<Type>::operator*() const {
    return *ptr;
}
