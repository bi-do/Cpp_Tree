#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class BtreeNode;
class BtreeIndex;
class Btree
{
private:
    BtreeNode *rootNode = nullptr;
    int maxchild = 3;
    int maxkey = maxchild - 1;
    int minchild = (maxchild + 1) / 2;
    int minkey = minchild - 1;

public:
    Btree(/* args */);
    ~Btree();

    BtreeNode *getRoot()
    {
        return this->rootNode;
    }

    /** 노드 삽입 */
    void insert(int param);

    /**노드 검색 */
    BtreeIndex *search(int param);

    void deleteNode(int param);
};

class BtreeNode
{
private:
    vector<BtreeIndex *> keys;
    vector<BtreeNode *> childs;
    BtreeNode *parent = nullptr;

public:
    BtreeNode();
    ~BtreeNode();
    vector<BtreeIndex *> &getKeys()
    {
        return this->keys;
    }
    vector<BtreeNode *> &getChilds()
    {
        return this->childs;
    }
    BtreeNode *getParent()
    {
        return this->parent;
    }
    void setParent(BtreeNode *pParam)
    {
        this->parent = pParam;
    }

    /**입력한 key값에 따라 다음 자식을 뱉어냄 */
    BtreeNode *getNextNode(int param);

    void pushKey(BtreeIndex &pParam);

    void pushChild(BtreeNode &pParam);

    /**키 값 비교 함수 (오름차순) */
    static bool compareByKey(BtreeIndex *a, BtreeIndex *b);

    /**자식노드 중 가장 큰 키값 비교 함수 (오름차순) */
    static bool compaerByChild(BtreeNode *a, BtreeNode *b);

    int getSelfIndexByParent();

    bool isLeap();

    BtreeNode &getSucessorNode(BtreeNode &pNode, BtreeIndex &pParam);

    BtreeNode *getLeftSibling();

    BtreeNode *getRightSibling();
    
    /**중위 순회 */
    void in_orderTraversal();
};

class BtreeData
{
private:
    int age;
    string name;
    string phone;

public:
    BtreeData(/* args */) {

    };
    ~BtreeData() {

    };
};

class BtreeIndex
{
private:
    int key;
    BtreeData *data = nullptr;

public:
    BtreeIndex(int param);
    ~BtreeIndex();
    void setKey(int param)
    {
        this->key = param;
    }
    int getKey()
    {
        return this->key;
    }
    void setData(BtreeData &pParam)
    {
        this->data = &pParam;
    }
    BtreeData *getData()
    {
        return this->data;
    }
};
