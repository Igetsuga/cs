#include <iostream>
//#include "Node.h"
#include "LinkedList.h"




int main()
{

    LinkedList<int> list;
    for ( int i = 0; 0 < 10; i++ ) {
        list.push(i);
    }

    list.print(); //std::cout << list;

    std::cout << "Hello World!\n";
    return 0;
}

