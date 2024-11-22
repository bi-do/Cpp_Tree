#include "heap.h"
void Heap::insert(int data)
{
    BstNode &newTmp = *new BstNode(data);
    /**최초 삽입 시 */
    if (rootNode == nullptr)
    {
        rootNode = &newTmp;
        lastInsert = rootNode;
        return;
    }
    else
    {
        /**마지막 삽입 한 위치가 루트 노드 일 시 */
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
    /**마지막으로 삽입된 자식이 부모의 왼쪽 일 경우 */
    if (&lastInsert == lastInsert.getparent()->getLeft())
    {
        return lastInsert.getparent();
    }
    /**마지막으로 삽입된 자식이 부모의 오른쪽 일 때 */
    else if (&lastInsert == lastInsert.getparent()->getRight())
    {
        BstNode *currentNode = &lastInsert;
        BstNode *rightSibling = nullptr;
        while (currentNode->getparent()->getparent() != nullptr)
        {
            currentNode = currentNode->getparent();
            rightSibling = getRightsibling(*currentNode);
            /**부모 중에 오른쪽 형제가 있다면 */
            if (rightSibling != nullptr)
            {
                while (rightSibling->getLeft() != nullptr)
                {
                    rightSibling = rightSibling->getLeft();
                }
                return rightSibling;
            }
        }
        /**부모 중에 오른쪽 형제가 없다면 */
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

    /**삭제 할 실제 노드가 루트 노드 일 시 */
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
        cout << "삭제 키 : " << deleteNode->getKey() << endl;
        return deleteNode;
    }
}
BstNode *Heap::getPrevLastInsert(BstNode &lastInsert)
{
    /**마지막 삽입위치가 부모의 왼쪽 자식이었다면 */
    if (&lastInsert == lastInsert.getparent()->getLeft())
    {
        BstNode *curNode = &lastInsert;
        BstNode *leftsibling = nullptr;
        while (curNode->getparent()->getparent() != nullptr)
        {
            curNode = curNode->getparent();
            leftsibling = getLeftsibling(*curNode);
            /**부모의 왼쪽 형제가 있을 시 */
            if (leftsibling != nullptr)
            {
                while (leftsibling->getRight() != nullptr)
                {
                    leftsibling = leftsibling->getRight();
                }
                return leftsibling;
            }
        }
        /**부모의 왼쪽 형제가 없을 시 */
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
    /**마지막 삽입이 부모의 오른쪽 자식이었다면 */
    else
    {
        return lastInsert.getparent()->getLeft();
    }
    return nullptr;
}