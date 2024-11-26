#include "heap.h"
void Heap::insert(int data)
{
    BstNode &newTmp = *new BstNode(data);
    /**���� ���� �� */
    if (rootNode == nullptr)
    {
        rootNode = &newTmp;
        lastInsert = rootNode;
        return;
    }
    else
    {
        /**������ ���� �� ��ġ�� ��Ʈ ��� �� �� */
        if (lastInsert == rootNode)
        {
            rootNode->setLeft(&newTmp);
            newTmp.setparent(*rootNode);
            lastInsert = &newTmp;
        }
        else
        {
            BstNode *newParent = FindInsertParent(*lastInsert);
            if (newParent->getLeft() == nullptr)
            {
                newParent->setLeft(&newTmp);
            }
            else if (newParent->getRight() == nullptr)
            {
                newParent->setRight(&newTmp);
            }
            newTmp.setparent(*newParent);
            lastInsert = &newTmp;
        }
        BstNode *curNode = &newTmp;
        while (curNode->getparent() != nullptr)
        {
            if (isBigValue(*curNode, *curNode->getparent()) == false)
            {
                break;
            }
            int tmp = curNode->getKey();
            curNode->setKey(curNode->getparent()->getKey());
            curNode->getparent()->setKey(tmp);
            curNode = curNode->getparent();
        }
    }
}
bool Heap::isBigValue(BstNode &pChild, BstNode &pParent)
{
    return (pChild.getKey() < pParent.getKey());
}
BstNode *Heap::BiggerChild(BstNode *pParent)
{
    if (pParent->getLeft() == nullptr)
    {
        return pParent->getRight();
    }
    else if (pParent->getRight() == nullptr)
    {
        return pParent->getLeft();
    }
    else if (isBigValue(*pParent->getLeft(), *pParent->getRight()) == true)
    {
        return pParent->getLeft();
    }
    else
        return pParent->getRight();
}
BstNode *Heap::FindInsertParent(BstNode &lastInsert)
{
    /**���������� ���Ե� �ڽ��� �θ��� ���� �� ��� */
    if (&lastInsert == lastInsert.getparent()->getLeft())
    {
        return lastInsert.getparent();
    }
    /**���������� ���Ե� �ڽ��� �θ��� ������ �� �� */
    else if (&lastInsert == lastInsert.getparent()->getRight())
    {
        BstNode *currentNode = &lastInsert;
        BstNode *rightSibling = nullptr;
        while (currentNode->getparent()->getparent() != nullptr)
        {
            currentNode = currentNode->getparent();
            rightSibling = getRightsibling(*currentNode);
            /**�θ� �߿� ������ ������ �ִٸ� */
            if (rightSibling != nullptr)
            {
                while (rightSibling->getLeft() != nullptr)
                {
                    rightSibling = rightSibling->getLeft();
                }
                return rightSibling;
            }
        }
        /**�θ� �߿� ������ ������ ���ٸ� */
        if (rightSibling == nullptr)
        {
            currentNode = rootNode;
            while (currentNode->getLeft() != nullptr)
            {
                currentNode = currentNode->getLeft();
            }
            return currentNode;
        }
    }
    return nullptr;
}
BstNode *Heap::getRightsibling(BstNode &pParam)
{
    if (pParam.getparent() != nullptr && (&pParam) == pParam.getparent()->getLeft())
    {
        return pParam.getparent()->getRight();
    }
    else
        return nullptr;
}
BstNode *Heap::getLeftsibling(BstNode &pParam)
{
    if (pParam.getparent() != nullptr && (&pParam) == pParam.getparent()->getRight())
    {
        return pParam.getparent()->getLeft();
    }
    else
        return nullptr;
}
BstNode *Heap::remove()
{
    BstNode *deleteNode = lastInsert;
    BstNode *curNode = rootNode;

    /**���� �� ���� ��尡 ��Ʈ ��� �� �� */
    if (deleteNode == rootNode)
    {
        lastInsert = nullptr;
        rootNode = nullptr;
        return deleteNode;
    }
    else
    {
        int tmp = deleteNode->getKey();
        deleteNode->setKey(curNode->getKey());
        curNode->setKey(tmp);
        if (deleteNode == deleteNode->getparent()->getLeft())
        {
            deleteNode->getparent()->setLeft(nullptr);
        }
        else
            deleteNode->getparent()->setRight(nullptr);
        do
        {
            BstNode *bigchild = BiggerChild(curNode);
            if (bigchild != nullptr && bigchild->getKey() < curNode->getKey())
            {
                int tmp = curNode->getKey();
                curNode->setKey(bigchild->getKey());
                bigchild->setKey(tmp);
                curNode = bigchild;
            }
            else
                break;
        } while (curNode->getLeft() != nullptr);
        lastInsert = getPrevLastInsert(*deleteNode);
        cout << "���� Ű : " << deleteNode->getKey() << endl;
        return deleteNode;
    }
}
BstNode *Heap::getPrevLastInsert(BstNode &lastInsert)
{
    /**������ ������ġ�� �θ��� ���� �ڽ��̾��ٸ� */
    if (&lastInsert == lastInsert.getparent()->getLeft())
    {
        BstNode *curNode = &lastInsert;
        BstNode *leftsibling = nullptr;
        while (curNode->getparent()->getparent() != nullptr)
        {
            curNode = curNode->getparent();
            leftsibling = getLeftsibling(*curNode);
            /**�θ��� ���� ������ ���� �� */
            if (leftsibling != nullptr)
            {
                while (leftsibling->getRight() != nullptr)
                {
                    leftsibling = leftsibling->getRight();
                }
                return leftsibling;
            }
        }
        /**�θ��� ���� ������ ���� �� */
        if (leftsibling == nullptr)
        {
            curNode = rootNode;
            while (curNode->getRight() != nullptr)
            {
                curNode = curNode->getRight();
            }
            return curNode;
        }
    }
    /**������ ������ �θ��� ������ �ڽ��̾��ٸ� */
    else
    {
        return lastInsert.getparent()->getLeft();
    }
    return nullptr;
}