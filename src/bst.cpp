#include "bst.h"

BstNode *BstNode::DeleteNextValue(BstNode &pParam)
{
    if (this->left != nullptr)
    {
        this->left = this->left->DeleteNextValue(pParam);

        return this;
    }
    else if (this == pParam.right)
    {
        pParam.right = this->right;
    }
    pParam.key = this->key;
    BstNode *pTmp = this->right;
    this->right = nullptr;
    delete this;
    return pTmp;
}
BstNode *BstNode::DeleteLogic()
{
    BstNode *ptmp = nullptr;
    if (this->left == nullptr)
    {
        ptmp = this->right;
        this->right = nullptr;
        delete this;
        return ptmp;
    }
    else if (this->right == nullptr)
    {
        ptmp = this->left;
        this->left = nullptr;
        delete this;
        return ptmp;
    }
    this->right->DeleteNextValue(*this);
    return this;
}
BstNode &BstNode::insertNode(int data)
{
    if (this->key > data)
    {
        if (this->left == nullptr)
        {
            this->left = &NewNode(data);
        }
        else
            this->left = &this->left->insertNode(data);
    }
    else if (this->key < data)
    {
        if (this->right == nullptr)
        {
            this->right = &NewNode(data);
        }
        else
            this->right = &this->right->insertNode(data);
    }

    return this->BalanceUpdate();
}
const BstNode *BstNode::SearchNode(int data) const
{
    if (this->key > data)
    {
        if (this->left == nullptr)
        {
            cout << "해당 값이 없습니다 : " << data << endl;
            return nullptr;
        }
        else
            return this->left->SearchNode(data);
    }
    else if (this->key < data)
    {
        if (this->right == nullptr)
        {
            cout << "해당 값이 없습니다 : " << data << endl;
            return nullptr;
        }
        else
            return this->right->SearchNode(data);
    }
    cout << "해당 값을 찾았습니다 : " << data << endl;
    return this;
}
BstNode *BstNode::DeleteNode(int data)
{
    if (this->key > data)
    {
        if (this->left == nullptr)
        {
            cout << "해당 값이 없습니다 : " << data << endl;
            return nullptr;
        }
        else
            this->left = this->left->DeleteNode(data);
    }
    else if (this->key < data)
    {
        if (this->right == nullptr)
        {
            cout << "해당 값이 없습니다 : " << data << endl;
            return nullptr;
        }
        else
            this->right = this->right->DeleteNode(data);
    }
    else if (data == this->key)
    {
        return this->DeleteLogic();
    }

    return &this->BalanceUpdate();
}
void BstNode::in_OrderTraversal()
{
    if (this == nullptr)
    {
        return;
    }
    this->left->in_OrderTraversal();
    cout << "키 값 : " << this->key << " 높이 : " << this->height << endl;
    this->right->in_OrderTraversal();
}

BstNode &AvlNode::rotation()
{
    int BF = this->getBalanceFactor();
    BstNode *Tmp = this;
    if (BF < -1)
    {
        AvlNode *rightTmp = static_cast<AvlNode *>(this->getRight());
        if (rightTmp->getBalanceFactor() > 0)
        {
            this->right = &rightTmp->RitgtRotate();
            Tmp = &this->LeftRotate();
        }
        else
        {
            Tmp = &this->LeftRotate();
        }
    }
    else if (BF > 1)
    {
        AvlNode *leftTmp = static_cast<AvlNode *>(this->getLeft());
        if (leftTmp->getBalanceFactor() < 0)
        {
            this->left = &leftTmp->LeftRotate();
            Tmp = &this->RitgtRotate();
        }
        else
        {
            Tmp = &this->RitgtRotate();
        }
    }
    static_cast<AvlNode *>(Tmp)->heightUpdate();
    return *Tmp;
}

BstNode &AvlNode::LeftRotate()
{
    TreeDB *tmp = TreeDB::getTree();

    BstNode *pTmp = this->right;
    this->right = pTmp->getLeft();
    pTmp->setLeft(*this);
    this->heightUpdate();
    static_cast<AvlNode *>(pTmp)->heightUpdate();
    if (tmp->rootNode == this)
    {
        tmp->rootNode = pTmp;
    }
    cout << "Left 회전 완료" << endl;

    return *pTmp;
}

BstNode &AvlNode::RitgtRotate()
{
    TreeDB *tmp = TreeDB::getTree();

    BstNode *pTmp = this->left;
    this->left = pTmp->getRight();
    pTmp->setRight(*this);

    this->heightUpdate();
    static_cast<AvlNode *>(pTmp)->heightUpdate();
    if (tmp->rootNode == this)
    {
        tmp->rootNode = pTmp;
    }
    cout << "Right 회전 완료" << endl;
    return *pTmp;
}