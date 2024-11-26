#include <iostream>
#include <algorithm>
#include <vector>
#include "btree.h"
Btree::Btree(/* args */) {

};
Btree::~Btree()
{
    delete rootNode;
};

void Btree::insert(int param)
{
    BtreeIndex *curIndex = new BtreeIndex(param);

    /**최초 삽입 */
    if (rootNode == nullptr)
    {
        rootNode = new BtreeNode();
        rootNode->pushKey(*curIndex);
    }
    else
    {
        BtreeNode *curNode = rootNode;
        BtreeNode *parentNode = nullptr;

        /**리프노드 일 때 까지 계속 탐색 */
        while (curNode->getChilds().size() != 0)
        {
            parentNode = curNode;
            curNode = curNode->getNextNode(param);
        }
        curNode->pushKey(*curIndex);

        /**현재 노드의 key가 최대값보다 많다면 */
        while (curNode->getKeys().size() > maxkey)
        {
            int middelvalue = curNode->getKeys().size() / 2;
            BtreeIndex *middleIndex = curNode->getKeys()[middelvalue];

            /**현재 검증 중인 노드가 루트 노드라면 */
            if (parentNode == nullptr)
            {
                parentNode = new BtreeNode();
                rootNode = parentNode;
                parentNode->pushChild(*curNode);
            }
            parentNode->pushKey(*middleIndex);
            BtreeNode *broNode = new BtreeNode();

            broNode->getKeys().insert(broNode->getKeys().end(), curNode->getKeys().begin() + middelvalue + 1, curNode->getKeys().end());

            /**현재 검증 중인 노드가 리프 노드가 아니라면 */
            if (curNode->getChilds().size() > 0)
            {
                broNode->getChilds().insert(broNode->getChilds().end(), curNode->getChilds().begin() + middelvalue + 1, curNode->getChilds().end());
                for (BtreeNode *element : broNode->getChilds())
                {
                    element->setParent(broNode);
                }

                curNode->getChilds().erase(curNode->getChilds().begin() + middelvalue + 1, curNode->getChilds().end());
            }

            parentNode->pushChild(*broNode);

            broNode->setParent(parentNode);
            curNode->setParent(parentNode);

            curNode->getKeys().erase(curNode->getKeys().begin() + middelvalue, curNode->getKeys().end());

            /**부모 노드 key값 확인 */
            curNode = parentNode;
            parentNode = parentNode->getParent();
        }
    }
}

BtreeIndex *Btree::search(int param)
{
    BtreeIndex *result = nullptr;
    BtreeNode *curNode = rootNode;
    while (curNode != nullptr)
    {
        int index = 0;
        for (BtreeIndex *element : curNode->getKeys())
        {
            if (param < element->getKey())
            {
                if (curNode->getChilds().size() > 0)
                {
                    curNode = curNode->getChilds()[index];
                    break;
                }
                else
                    return nullptr;
            }
            else if (param == element->getKey())
            {
                result = element;
                return result;
            }
            else
                index++;
        }
        if (index == curNode->getKeys().size())
        {
            if (curNode->getChilds().size() > 0)
            {
                curNode = curNode->getChilds().back();
            }
            else
                return nullptr;
        }
    }
    return nullptr;
}

BtreeNode *BtreeNode::getNextNode(int param)
{
    int index = 0;
    for (BtreeIndex *element : keys)
    {
        if (param < element->getKey())
        {
            return childs[index];
        }
        else
            index++;
    }
    return childs[index];
}

void BtreeNode::pushKey(BtreeIndex &pParam)
{
    this->keys.push_back(&pParam);
    sort(this->keys.begin(), this->keys.end(), compareByKey);
}

void BtreeNode::pushChild(BtreeNode &pParam)
{
    this->childs.push_back(&pParam);
    sort(this->childs.begin(), this->childs.end(), compaerByChild);
}

bool BtreeNode::compareByKey(BtreeIndex *a, BtreeIndex *b)
{
    return a->getKey() < b->getKey();
}

bool BtreeNode::compaerByChild(BtreeNode *a, BtreeNode *b)
{
    return a->getKeys().back()->getKey() < b->getKeys().back()->getKey();
}

void BtreeNode::in_orderTraversal()
{
    for (int i = 0; i < this->keys.size(); i++)
    {
        if (this->childs.size() > 0)
        {
            this->childs[i]->in_orderTraversal();
        }
        cout << this->keys[i]->getKey() << endl;
    }
    if (this->childs.size() > 0)
    {
        this->childs.back()->in_orderTraversal();
    }
}

BtreeNode::BtreeNode()
{
}

BtreeNode::~BtreeNode()
{
    for (BtreeNode *element : childs)
    {
        delete element;
    }
    for (BtreeIndex *element : keys)
    {
        delete element;
    }
}

BtreeIndex::BtreeIndex(int param)
{
    this->key = param;
}

BtreeIndex::~BtreeIndex()
{
    delete data;
}