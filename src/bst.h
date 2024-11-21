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
    BstNode *parent;
    int height = 0;
    int key;
    bool color = false; // true = black , false = red;

    /**대상 인스턴스보다 오른쪽 자식중 가장 작은 값을 찾아서 삭제함. this == 대상 바로 오른쪽 자식, pParam == 덮어 쓸 대상 */
    BstNode *DeleteNextValue(BstNode &pParam);

    /**노드의 자식 개수에 따라 삭제하는 로직 */
    BstNode *DeleteLogic();

public:
    explicit BstNode(int Key)
    {
        this->left = this->right = this->parent = nullptr;
        this->key = Key;
        cout << "생성 키 : " << this->key << endl;
    }
    virtual ~BstNode()
    {
        // cout << "소멸 키 : " << this->key << endl;
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

    /**노드 삽입 */
    virtual BstNode &insertNode(int data);

    /**값 탐색. */
    const BstNode *SearchNode(int data) const;

    /**값 삭제 */
    virtual BstNode *DeleteNode(int data);

    /**중위 순회 */
    void in_OrderTraversal();

    /**전위 순회 */
    void post_OrderTraversal();

    /**실제 노드 타입 변환 및 사전 작업*/
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

    /**회전 여부 확인 및 조건 만족시 회전 후 새로운 루트 반환*/
    BstNode &rotation();

    /**가상 함수 업데이트 */
    BstNode &BalanceUpdate() override
    {
        return this->rotation();
    }
};

class RedBlackNode : public BstNode
{
private:
    void DeleteNodeLogic(BstNode *currentNode);

    /**노드 균형 확인 */
    void RedBlackBlanceUpdate(BstNode &pDelete, BstNode *pTmp, bool doubly = false);

    /**삽입 후 규칙 위반 체크 */
    void insertRuleCheck(RedBlackNode &grandSonNode);

    /**회전 조건 체크 */
    void rotation(BstNode &grandParantNode, BstNode &grandSonNode);

    /**노드 삭제시 대체되는 노드와 부모 자식 관계 재지정 */
    BstNode *setParentChild(RedBlackNode *pParent, BstNode *pOldChild, BstNode *pNewChild);

public:
    bool IsNil = false;
    explicit RedBlackNode() : BstNode(0)
    {
        this->IsNil = true;
    }
    RedBlackNode(int param) : BstNode(param)
    {
        // cout << "생성자 명시" << endl;
    }
    ~RedBlackNode()
    {
        cout << "소멸 키 : " << this->key << " is nil? : " << (this->IsNil == true ? " yes " : " no ") << endl;
    }

    BstNode *getuncle();

    BstNode *getBro();

    /**새로운 노드 삽입 */
    BstNode &insertNode(int data);

    RedBlackNode &NewNode(int data) override;

    /**노드 삭제 */
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