#pragma once
#include <iostream>
#include "treedb.h"
using namespace std;

/**���� �˻� Ʈ�� Ŭ����*/
class BstNode
{

protected:
    BstNode *left;
    BstNode *right;
    int height = 0;
    int key;

    /**��� �ν��Ͻ����� ������ �ڽ��� ���� ���� ���� ã�Ƽ� ������. this == ��� �ٷ� ������ �ڽ�, pParam == ���� �� ��� */
    BstNode *DeleteNextValue(BstNode &pParam)
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

    /**����� �ڽ� ������ ���� �����ϴ� ���� */
    BstNode *DeleteLogic()
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

public:
    explicit BstNode(int Key)
    {
        this->left = this->right = nullptr;
        this->key = Key;
        cout << "���� Ű : " << this->key << endl;
    }
    virtual ~BstNode()
    {
        cout << "�Ҹ� Ű : " << this->key << endl;
        delete left;
        delete right;
    }

    BstNode *getLeft() const
    {
        return this->left;
    }
    BstNode *getRight() const
    {
        return this->right;
    }
    void setLeft(BstNode &pParam)
    {
        this->left = &pParam;
    }
    void setRight(BstNode &pParam)
    {
        this->right = &pParam;
    }

    /**��� ���� */
    virtual BstNode &insertNode(int data)
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

    /**�� Ž��. */
    const BstNode *SearchNode(int data) const
    {
        if (this->key > data)
        {
            if (this->left == nullptr)
            {
                cout << "�ش� ���� �����ϴ� : " << data << endl;
                return nullptr;
            }
            else
                return this->left->SearchNode(data);
        }
        else if (this->key < data)
        {
            if (this->right == nullptr)
            {
                cout << "�ش� ���� �����ϴ� : " << data << endl;
                return nullptr;
            }
            else
                return this->right->SearchNode(data);
        }
        cout << "�ش� ���� ã�ҽ��ϴ� : " << data << endl;
        return this;
    }
    /**�� ���� */
    virtual BstNode *DeleteNode(int data)
    {
        if (this->key > data)
        {
            if (this->left == nullptr)
            {
                cout << "�ش� ���� �����ϴ� : " << data << endl;
                return nullptr;
            }
            else
                this->left = this->left->DeleteNode(data);
        }
        else if (this->key < data)
        {
            if (this->right == nullptr)
            {
                cout << "�ش� ���� �����ϴ� : " << data << endl;
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

    /**���� ��ȸ */
    void in_OrderTraversal()
    {
        if (this == nullptr)
        {
            return;
        }
        this->left->in_OrderTraversal();
        cout << "Ű �� : " << this->key << " ���� : " << this->height << endl;
        this->right->in_OrderTraversal();
    }

    int getHeight()
    {
        return this->height;
    }

    /**���� ��� Ÿ�� ��ȯ */
    virtual BstNode &NewNode(int data)
    {
        return *(new BstNode(data));
    }

    virtual BstNode &BalanceUpdate()
    {
        return *this;
    }
};

/**AVL Ʈ�� Ŭ���� */
class AvlNode : public BstNode
{
public:
    AvlNode(int param) : BstNode(param)
    {
        cout << "������ ���" << endl;
    }
    ~AvlNode() {}

    virtual AvlNode &NewNode(int data)
    {
        AvlNode &tmp = *new AvlNode(data);
        tmp.heightUpdate();
        return tmp;
    }

    void heightUpdate()
    {
        this->height = max(this->left != nullptr ? this->left->getHeight() : 0, this->right != nullptr ? this->right->getHeight() : 0) + 1;
    }

    int getBalanceFactor()
    {
        return (this->left != nullptr ? this->left->getHeight() : 0) - (this->right != nullptr ? this->right->getHeight() : 0);
    }

    /**ȸ�� ���� Ȯ��*/
    BstNode &rotation()
    {
        int BF = this->getBalanceFactor();
        BstNode *Tmp = this;
        if (BF < -1)
        {
            AvlNode *rightTmp = static_cast<AvlNode *>(this->getRight());
            if (rightTmp->getBalanceFactor() >= 0)
            {
                Tmp = &this->LeftRotate();
            }
            else
            {
                this->right = &rightTmp->RitgtRotate();
                Tmp = &this->LeftRotate();
            }
        }
        if (BF > 1)
        {
            AvlNode *leftTmp = static_cast<AvlNode *>(this->getLeft());
            if (leftTmp->getBalanceFactor() >= 0)
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

    /**���� �Լ� ������Ʈ */
    BstNode &BalanceUpdate()
    {
        return this->rotation();
    }

    BstNode &LeftRotate()
    {
        TreeDB *tmp = TreeDB::getTree();
        cout << "Left ȸ�� �Ϸ�" << endl;
        BstNode *pTmp = this->right;
        this->right = pTmp->getLeft();
        pTmp->setLeft(*this);
        this->heightUpdate();
        static_cast<AvlNode *>(pTmp)->heightUpdate();
        if (tmp->rootNode == this)
        {
            tmp->rootNode = pTmp;
        }

        return *pTmp;
    }

    BstNode &RitgtRotate()
    {
        TreeDB *tmp = TreeDB::getTree();

        cout << "Right ȸ�� �Ϸ�" << endl;
        BstNode *pTmp = this->left;
        this->left = pTmp->getRight();
        pTmp->setRight(*this);

        this->heightUpdate();
        static_cast<AvlNode *>(pTmp)->heightUpdate();
        if (tmp->rootNode == this)
        {
            tmp->rootNode = pTmp;
        }
        return *pTmp;
    }
};