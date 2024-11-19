#include <iostream>
#include <conio.h>
#include "treedb.h"
#include "bst.h"
using namespace std;

int main(void)
{
    TreeDB *DB = TreeDB::getTree();
    DB->rootNode = new AvlNode(5);

    int collection[] = {1, 8, 7, 10, 6};
    for (const auto element : collection)
    {
        DB->insertNode(element);
    }
    DB->DeleteNode(1);
    DB->SearchNode(20);
    DB->SearchNode(10);
    DB->in_OrderTravers();
    _getch();
    return 0;
}