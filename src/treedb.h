#pragma once
#include <iostream>
#include "bst.h"
class BstNode;
class TreeDB
{
private:
    static TreeDB *instance;
    TreeDB() {};

public:
    static BstNode *rootNode;

    /**싱글턴 인스턴스 생성 */
    static TreeDB *getTree();
    ~TreeDB();

    /**루트 노드 기준 노드 삽입 */
    void insertNode(int data);

    /**루트 노드 기준 중위 선회 */
    void in_OrderTravers();

    /**노드 검색 */
    const BstNode *SearchNode(int data);

    /**노드 삭제 */
    void DeleteNode(int data);
};
