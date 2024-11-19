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
    BstNode *DeleteNextValue(BstNode &pParam);

    /**����� �ڽ� ������ ���� �����ϴ� ���� */
    BstNode *DeleteLogic();

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
    int getHeight()
    {
        return this->height;
    }

    /**��� ���� */
    virtual BstNode &insertNode(int data);

    /**�� Ž��. */
    const BstNode *SearchNode(int data) const;

    /**�� ���� */
    virtual BstNode *DeleteNode(int data);

    /**���� ��ȸ */
    void in_OrderTraversal();

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

    BstNode &LeftRotate();

    BstNode &RitgtRotate();
    
    /**ȸ�� ���� Ȯ�� �� ���� ������ ȸ�� �� ���ο� ��Ʈ ��ȯ*/
    BstNode &rotation();

    /**���� �Լ� ������Ʈ */
    BstNode &BalanceUpdate()
    {
        return this->rotation();
    }
};