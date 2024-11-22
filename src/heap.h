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
    /**��� ���� */
    void insert(int data);

    /**������ ������ true, �ƴϸ� false */
    bool isBigValue(BstNode &pChild, BstNode &pParent);

    /**�켱������ �� ���� �ڽĳ�带 ��ȯ�� */
    BstNode *BiggerChild(BstNode *pParent);

    /**������ ��ġ�� �θ� ��带 ���� ����. */
    BstNode *FindInsertParent(BstNode &lastInsert);

    /**������ ���� ������ */
    BstNode *getRightsibling(BstNode &pParam);

    /**���� ���� ������ */
    BstNode *getLeftsibling(BstNode &pParam);

    /**�ּҰ� ( �ִ� �� ) ���� */
    BstNode *remove();

    /**������ ���� ������ ���� ��ġ�� ��ȯ�� */
    BstNode *getPrevLastInsert(BstNode &lastInsert);
};