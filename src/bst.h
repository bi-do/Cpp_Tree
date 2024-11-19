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
    BstNode *DeleteNextValue(BstNode &pParam);

    /**노드의 자식 개수에 따라 삭제하는 로직 */
    BstNode *DeleteLogic();

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
    int getHeight()
    {
        return this->height;
    }

    /**노드 삽입 */
    virtual BstNode &insertNode(int data);

    /**값 탐색. */
    const BstNode *SearchNode(int data) const;

    /**값 삭제 */
    virtual BstNode *DeleteNode(int data);

    /**중위 순회 */
    void in_OrderTraversal();

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

    BstNode &LeftRotate();

    BstNode &RitgtRotate();
    
    /**회전 여부 확인 및 조건 만족시 회전 후 새로운 루트 반환*/
    BstNode &rotation();

    /**가상 함수 업데이트 */
    BstNode &BalanceUpdate()
    {
        return this->rotation();
    }
};