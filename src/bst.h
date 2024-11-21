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
    BstNode *parent;
    int height = 0;
    int key;
    bool color = false; // true = black , false = red;

    /**��� �ν��Ͻ����� ������ �ڽ��� ���� ���� ���� ã�Ƽ� ������. this == ��� �ٷ� ������ �ڽ�, pParam == ���� �� ��� */
    BstNode *DeleteNextValue(BstNode &pParam);

    /**����� �ڽ� ������ ���� �����ϴ� ���� */
    BstNode *DeleteLogic();

public:
    explicit BstNode(int Key)
    {
        this->left = this->right = this->parent = nullptr;
        this->key = Key;
        cout << "���� Ű : " << this->key << endl;
    }
    virtual ~BstNode()
    {
        // cout << "�Ҹ� Ű : " << this->key << endl;
        delete left;
        delete right;
    }

    int getKey()
    {
        return this->key;
    }
    void setKey(int data)
    {
        this->key = data;
    }
    BstNode *getLeft() const
    {
        return this->left;
    }
    BstNode *getRight() const
    {
        return this->right;
    }
    void setLeft(BstNode *pParam)
    {
        this->left = pParam;
    }
    void setRight(BstNode *pParam)
    {
        this->right = pParam;
    }
    int getHeight()
    {
        return this->height;
    }
    BstNode *getparent() const
    {
        return this->parent;
    }
    bool getColor() const
    {
        return this->color;
    }
    void setColor(bool param)
    {
        this->color = param;
    }
    void setparent(BstNode &pParam)
    {
        this->parent = &pParam;
    }

    /**��� ���� */
    virtual BstNode &insertNode(int data);

    /**�� Ž��. */
    const BstNode *SearchNode(int data) const;

    /**�� ���� */
    virtual BstNode *DeleteNode(int data);

    /**���� ��ȸ */
    void in_OrderTraversal();

    /**���� ��ȸ */
    void post_OrderTraversal();

    /**���� ��� Ÿ�� ��ȯ �� ���� �۾�*/
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

    AvlNode &NewNode(int data) override
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
    BstNode &BalanceUpdate() override
    {
        return this->rotation();
    }
};

class RedBlackNode : public BstNode
{
private:
    void DeleteNodeLogic(BstNode *currentNode);

    /**��� ���� Ȯ�� */
    void RedBlackBlanceUpdate(BstNode &pDelete, BstNode *pTmp, bool doubly = false);

    /**���� �� ��Ģ ���� üũ */
    void insertRuleCheck(RedBlackNode &grandSonNode);

    /**ȸ�� ���� üũ */
    void rotation(BstNode &grandParantNode, BstNode &grandSonNode);

    /**��� ������ ��ü�Ǵ� ���� �θ� �ڽ� ���� ������ */
    BstNode *setParentChild(RedBlackNode *pParent, BstNode *pOldChild, BstNode *pNewChild);

public:
    bool IsNil = false;
    explicit RedBlackNode() : BstNode(0)
    {
        this->IsNil = true;
    }
    RedBlackNode(int param) : BstNode(param)
    {
        // cout << "������ ���" << endl;
    }
    ~RedBlackNode()
    {
        cout << "�Ҹ� Ű : " << this->key << " is nil? : " << (this->IsNil == true ? " yes " : " no ") << endl;
    }

    BstNode *getuncle();

    BstNode *getBro();

    /**���ο� ��� ���� */
    BstNode &insertNode(int data);

    RedBlackNode &NewNode(int data) override;

    /**��� ���� */
    BstNode *DeleteNode(int data) override;

    void broRightRotate(RedBlackNode *broNode, RedBlackNode *broParent)
    {
        broNode->setColor(broParent->getColor());
        broParent->setColor(true);
        broNode->left->setColor(true);
        RightRotate(*broParent);
    }

    void broLeftRotate(RedBlackNode *broNode, RedBlackNode *broParent)
    {
        broNode->setColor(broParent->getColor());
        broParent->setColor(true);
        broNode->right->setColor(true);
        LeftRotate(*broParent);
    }

    void RightRotate(RedBlackNode &pParam);

    void LeftRotate(RedBlackNode &pParam);
};