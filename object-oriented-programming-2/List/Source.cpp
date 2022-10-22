#include <iostream>
//#include "Node.h"
#include "LinkedList.h"




int main()
{

    LinkedList<int> A;
    /*for ( int i = 0; i < 3; i++ ) {
        A.push(i);
    }*/
    A.push(3); A.push(2); A.push(1);
    std::cout << A;
    std::cout << A[A.size() - 1]->getPredecessor();
    return 0;
}

