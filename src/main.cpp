#include <iostream>
#include <conio.h>
#include "treedb.h"
#include "bst.h"

using namespace std;

int main(void)
{
    TreeDB *DB = TreeDB::getTree();
    DB->rootinsert(*new RedBlackNode(10));
    int collection[] = {20, 30, 15, 25, 5, 35};
    for (const auto element : collection)
    {
        DB->insertNode(element);
    }
    DB->SearchNode(20);
    DB->SearchNode(10);
    DB->post_OrderTravers();
    DB->DeleteNode(5);
    DB->DeleteNode(10);
    DB->DeleteNode(15);
    DB->DeleteNode(35);
    DB->DeleteNode(25);
    DB->DeleteNode(30);
    DB->DeleteNode(20);

    DB->post_OrderTravers();
    _getch();
    return 0;
}