#include "treedb.h"
#include "bst.h"

TreeDB *TreeDB::getTree()
{
    if (instance == nullptr)
    {
        return instance = new TreeDB();
    }
    else
        return instance;
}
TreeDB::~TreeDB()
{
    delete rootNode;
    delete instance;
}
void TreeDB::rootinsert(BstNode &insert)
{
    insert.setColor(true);
    rootNode = &insert;
}
void TreeDB::insertNode(int data)
{
    rootNode->insertNode(data);
}
void TreeDB::in_OrderTravers()
{
    rootNode->in_OrderTraversal();
}
void TreeDB::post_OrderTravers()
{
    rootNode->post_OrderTraversal();
}
const BstNode *TreeDB::SearchNode(int data)
{
    return rootNode->SearchNode(data);
}
void TreeDB::DeleteNode(int data)
{
    rootNode->DeleteNode(data);
}

TreeDB *TreeDB::instance = nullptr;
BstNode *TreeDB::rootNode = nullptr;