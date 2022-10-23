#include <iostream>
//#include "Node.h"
#include "LinkedList.hpp"
#include "LinkedListIterated.hpp"

template<class Type> using LIT = LinkedListIterated<Type>;



int main()
{

   /* LinkedList<int> A;
    A.push_front(3); A.push_front(2); A.push_front(1);
    std::cout << A;

    A.push_back(4); std::cout << A.back() << nline; 
    A.push_back(5); std::cout << A.back() << nline;
    A.push_back(6); std::cout << A.back() << nline;
    std::cout << A;

    std::cout << nline << (A[4])->getPredecessor()->getData() << " --> " << A[4]->getData() << " --> " << A[4]->getSucessor()->getData();
    */

    //LinkedListIterated<int> I;
    

    LinkedListIterated<int> IT;
    for ( int i = 0; i < 5; i++ ) {
        IT.push_back(i);
    }
    std::cout << IT;
    IT.print();
    IT.print_reverse();

    IT.insert(3, 234);
    IT.print();
    IT.print_reverse();

   /* IT.pop_back();
    IT.print();
    IT.print_reverse();

    IT.pop_front();
    IT.print();
    IT.print_reverse();

    IT.erase(6);
    IT.print();
    IT.print_reverse();*/
    //IT.push_front(3); IT.push_front(2); IT.push_front(1);
    //std::cout << IT;

    //IT.push_back(4); std::cout << IT.back() << nline;
    //IT.push_back(5); std::cout << IT.back() << nline;
    //IT.push_back(6); std::cout << IT.back() << nline;
    //std::cout << IT;

    //std::cout << nline << (IT[4])->getPredecessor()->getData() << " --> " << IT[4]->getData() << " --> " << IT[4]->getSucessor()->getData();
    

    //LIT<int>::Iterator it = IT.begin();
    //it = IT.end();
    //std::cout << nline << *(it);
    //it++; std::cout << nline << *it;

 /*   LinkedListIterated<int> IIT;
    for ( int i = 10; i < 15; i++ ) {
        IIT.push_back(i);
    }

    std::cout << IIT;

    it = IIT.begin();
    std::cout << *it;*/

    return 0;
}

