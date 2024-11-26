#include <iostream>
#include <conio.h>
// #include "treedb.h"
// #include "bst.h"
// #include "heap.h"
#include "btree.h"
using namespace std;

int main(void)
{
    Btree *root = new Btree();
    int collection[] = {4, 2, 5, 8, 1, 9, 10, 14, 6};
    for (const auto element : collection)
    {
        root->insert(element);
    }
    root->getRoot()->in_orderTraversal();

    BtreeIndex *search = root->search(12);

    if (search != nullptr)
    {
        cout << "�˻� ��� : " << search->getKey() << endl;
    }
    else
        cout << "�˻� �Ͻ� ����� �����ϴ�" << endl;

    _getch();
}