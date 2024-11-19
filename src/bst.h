#pragma once
#include <iostream>
#include "treedb.h"
using namespace std;

/**이진 검색 트리 클래스*/
class BstNode
{

protected:
    BstNode *left;
    BstNode *right;
    int height = 0;
    int key;

    /**대상 인스턴스보다 오른쪽 자식중 가장 작은 값을 찾아서 삭제함. this == 대상 바로 오른쪽 자식, pParam == 덮어 쓸 대상 */
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

    /**노드의 자식 개수에 따라 삭제하는 로직 */
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
        cout << "생성 키 : " << this->key << endl;
    }
    virtual ~BstNode()
    {
        cout << "소멸 키 : " << this->key << endl;
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

    /**노드 삽입 */
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

    /**값 탐색. */
    const BstNode *SearchNode(int data) const
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
    /**값 삭제 */
    virtual BstNode *DeleteNode(int data)
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

    /**중위 순회 */
    void in_OrderTraversal()
    {
        if (this == nullptr)
        {
            return;
        }
        this->left->in_OrderTraversal();
        cout << "키 값 : " << this->key << " 높이 : " << this->height << endl;
        this->right->in_OrderTraversal();
    }

    int getHeight()
    {
        return this->height;
    }

    /**실제 노드 타입 변환 */
    virtual BstNode &NewNode(int data)
    {
        return *(new BstNode(data));
    }

    virtual BstNode &BalanceUpdate()
    {
        return *this;
    }
};

/**AVL 트리 클래스 */
class AvlNode : public BstNode
{
public:
    AvlNode(int param) : BstNode(param)
    {
        cout << "생성자 명시" << endl;
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

    /**회전 여부 확인*/
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

    /**가상 함수 업데이트 */
    BstNode &BalanceUpdate()
    {
        return this->rotation();
    }

    BstNode &LeftRotate()
    {
        TreeDB *tmp = TreeDB::getTree();
        cout << "Left 회전 완료" << endl;
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

        cout << "Right 회전 완료" << endl;
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