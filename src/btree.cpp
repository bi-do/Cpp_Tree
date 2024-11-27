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

    /**���� ���� */
    if (rootNode == nullptr)
    {
        rootNode = new BtreeNode();
        rootNode->pushKey(*curIndex);
    }
    else
    {
        BtreeNode *curNode = rootNode;
        BtreeNode *parentNode = nullptr;

        /**������� �� �� ���� ��� Ž�� */
        while (curNode->getChilds().size() != 0)
        {
            parentNode = curNode;
            curNode = curNode->getNextNode(param);
        }
        curNode->pushKey(*curIndex);

        /**���� ����� key�� �ִ밪���� ���ٸ� */
        while (curNode->getKeys().size() > maxkey)
        {
            int middelvalue = curNode->getKeys().size() / 2;
            BtreeIndex *middleIndex = curNode->getKeys()[middelvalue];

            /**���� ���� ���� ��尡 ��Ʈ ����� */
            if (parentNode == nullptr)
            {
                parentNode = new BtreeNode();
                rootNode = parentNode;
                parentNode->pushChild(*curNode);
            }
            parentNode->pushKey(*middleIndex);
            BtreeNode *broNode = new BtreeNode();

            broNode->getKeys().insert(broNode->getKeys().end(), curNode->getKeys().begin() + middelvalue + 1, curNode->getKeys().end());

            /**���� ���� ���� ��尡 ���� ��尡 �ƴ϶�� */
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

            /**�θ� ��� key�� Ȯ�� */
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

void Btree::deleteNode(int param)
{
    BtreeIndex *deleteIndex = nullptr;
    int deleteIndexNum;
    BtreeNode *curNode = rootNode;
    BtreeNode *parent = curNode;

    while (parent != nullptr)
    {
        int index = 0;
        for (BtreeIndex *element : curNode->getKeys())
        {

            if (param < element->getKey())
            {
                if (curNode->isLeap())
                {
                    parent = nullptr;
                    break;
                }
                else
                {
                    parent = curNode;
                    curNode = curNode->getChilds()[index];
                    break;
                }
            }
            else if (param == element->getKey())
            {
                parent = nullptr;
                deleteIndex = element;
                deleteIndexNum = index;
                break;
            }
            else
                index++;
        }
        if (index == curNode->getKeys().size())
        {
            if (curNode->isLeap())
            {
                parent = nullptr;
            }
            else
            {
                parent = curNode;
                curNode = curNode->getChilds().back();
            }
        }
    }

    if (deleteIndex == nullptr)
    {
        cout << "�ش� ���� ã�� ���߽��ϴ�." << endl;
        return;
    }
    /** ���� �����Ϸ��� Ű�� ������尡 �ƴ϶�� */
    else if (curNode->isLeap() == false)
    {
        curNode = &curNode->getSucessorNode(*curNode, *deleteIndex);
        int tmp = deleteIndex->getKey();
        deleteIndex->setKey(curNode->getKeys()[0]->getKey());
        curNode->getKeys()[0]->setKey(tmp);
        deleteIndex = curNode->getKeys()[0];
        deleteIndexNum = 0;
    }

    cout << "���� �Ϸ� : " << deleteIndex->getKey() << endl;
    curNode->getKeys().erase(curNode->getKeys().begin() + deleteIndexNum);
    delete deleteIndex;

    /**���� ����� Ű ���� ���� Ű�� ���� ���ٸ� */
    while (curNode->getKeys().size() < minkey)
    {
        BtreeNode *siblingNode = nullptr;
        parent = curNode->getParent();
        int selfindex = curNode->getSelfIndexByParent();
        int siblingindex;
        /**���� ������ Ű�� ������ �ִٸ� */
        if ((siblingNode = curNode->getLeftSibling()) != nullptr && siblingNode->getKeys().size() > minkey)
        {
            siblingindex = selfindex - 1;
            curNode->pushKey(*parent->getKeys()[siblingindex]);
            parent->getKeys().erase(parent->getKeys().begin() + siblingindex);
            parent->pushKey(*siblingNode->getKeys().back());
            siblingNode->getKeys().pop_back();
            break;
        }
        /**������ ������ Ű�� ������ �ִٸ� */
        else if ((siblingNode = curNode->getRightSibling()) != nullptr && siblingNode->getKeys().size() > minkey)
        {
            siblingindex = selfindex + 1;
            curNode->pushKey(*parent->getKeys()[siblingindex]);
            parent->getKeys().erase(parent->getKeys().begin() + siblingindex);
            parent->pushKey(*siblingNode->getKeys()[0]);
            siblingNode->getKeys().erase(siblingNode->getKeys().begin());
            break;
        }
        else
        {
            /**���� ������ �����Ѵٸ� */
            if ((siblingNode = curNode->getLeftSibling()) != nullptr)
            {
                siblingindex = selfindex - 1;
                siblingNode->getKeys().insert(siblingNode->getKeys().end(), curNode->getKeys().begin(), curNode->getKeys().end());
                siblingNode->getChilds().insert(siblingNode->getChilds().end(), curNode->getChilds().begin(), curNode->getChilds().end());
                siblingNode->pushKey(*parent->getKeys()[siblingindex]);
                parent->getKeys().erase(parent->getKeys().begin() + siblingindex);
                parent->getChilds().erase(parent->getChilds().begin() + selfindex);
                curNode->getKeys().clear();
                curNode->getChilds().clear();
                delete curNode;
                curNode = siblingNode;
            }
            /**���� ������ �������� �ʴ´ٸ� */
            else if ((siblingNode = curNode->getRightSibling()) != nullptr)
            {
                siblingindex = selfindex + 1;
                curNode->getKeys().insert(curNode->getKeys().end(), siblingNode->getKeys().begin(), siblingNode->getKeys().end());
                curNode->getChilds().insert(curNode->getChilds().end(), siblingNode->getChilds().begin(), siblingNode->getChilds().end());
                curNode->pushKey(*parent->getKeys()[selfindex]);
                parent->getKeys().erase(parent->getKeys().begin() + selfindex);
                parent->getChilds().erase(parent->getChilds().begin() + siblingindex);
                siblingNode->getKeys().clear();
                siblingNode->getChilds().clear();
                delete siblingNode;
            }
            else
                break;
            if (parent->getKeys().size() < minkey)
            {
                if (parent == rootNode)
                {
                    if (parent->getKeys().size() == 0)
                    {
                        rootNode = curNode;
                        parent->getChilds().clear();
                        parent->getKeys().clear();
                        delete parent;
                        curNode->setParent(nullptr);
                    }
                    else
                        break;
                }
                else
                    curNode = parent;
            }
        }
    }
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
int BtreeNode::getSelfIndexByParent()
{
    if (this->parent == nullptr)
    {
        return -1;
    }
    else
    {
        int Selfindex = 0;
        for (BtreeNode *element : parent->childs)
        {
            if (element == this)
            {
                break;
            }
            else
                Selfindex++;
        }
        return Selfindex;
    }
}

bool BtreeNode::isLeap()
{
    if (this->childs.size() > 0)
    {
        return false;
    }
    else
        return true;
}

BtreeNode &BtreeNode::getSucessorNode(BtreeNode &pNode, BtreeIndex &pParam)
{
    BtreeNode *curNode = nullptr;
    for (BtreeIndex *element : pNode.getKeys())
    {
        int index = 0;
        if (element == &pParam)
        {
            curNode = pNode.childs[index + 1];
            break;
        }
        else
            index++;
    }
    while (curNode->childs.size() > 0)
    {
        curNode = curNode->childs[0];
    }
    return *curNode;
}
BtreeNode *BtreeNode::getLeftSibling()
{
    BtreeNode *curNode = nullptr;
    int count = 0;
    while (curNode != this)
    {
        curNode = this->parent->childs[count];
        count++;
    }
    if (count > 1)
    {
        return this->parent->childs[count - 2];
    }
    else
        return nullptr;
}
BtreeNode *BtreeNode::getRightSibling()
{
    BtreeNode *curNode = nullptr;
    int count = 0;
    while (curNode != this)
    {
        curNode = this->parent->childs[count];
        count++;
    }
    if (this->parent->childs.size() > count)
    {
        return this->parent->childs[count];
    }
    else
        return nullptr;
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