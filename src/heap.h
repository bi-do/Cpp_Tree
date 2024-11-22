#pragma once
#include "bst.h"
using namespace std;
class Heap
{
private:
    BstNode *rootNode = nullptr;
    BstNode *lastInsert = nullptr;

public:
    ~Heap()
    {
        delete rootNode;
    }
    BstNode *getRoot()
    {
        return rootNode;
    }
    /**노드 삽입 */
    void insert(int data);

    /**왼쪽이 높으면 true, 아니면 false */
    bool isBigValue(BstNode &pChild, BstNode &pParent);

    /**우선순위가 더 높은 자식노드를 반환함 */
    BstNode *BiggerChild(BstNode *pParent);

    /**삽입할 위치의 부모 노드를 리턴 해줌. */
    BstNode *FindInsertParent(BstNode &lastInsert);

    /**오른쪽 형제 구해줌 */
    BstNode *getRightsibling(BstNode &pParam);

    /**왼쪽 형제 구해줌 */
    BstNode *getLeftsibling(BstNode &pParam);

    /**최소값 ( 최대 값 ) 삭제 */
    BstNode *remove();

    /**마지막 삽입 이전의 삽입 위치를 반환함 */
    BstNode *getPrevLastInsert(BstNode &lastInsert);
};