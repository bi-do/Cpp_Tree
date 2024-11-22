#include <iostream>
#include <conio.h>
#include "treedb.h"
#include "bst.h"
#include "heap.h"

using namespace std;

int main(void)
{
    Heap *heap = new Heap();
    int collection[] = {4, 2, 5, 7, 1};
    for (const auto element : collection)
    {
        heap->insert(element);
    }

    heap->getRoot()->in_OrderTraversal();
    heap->remove();

    heap->getRoot()->in_OrderTraversal();
    cout << "·çÆ® Å° : " << heap->getRoot()->getKey() << endl;

    _getch();
    return 0;
}