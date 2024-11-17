#include <iostream>
#include <conio.h>
using namespace std;

/**이진 검색 트리 클래스*/
class BstNode
{
private:
    BstNode *left;
    BstNode *right;
    int key;

    /**대상 인스턴스보다 오른쪽 자식중 가장 작은 값을 찾아서 삭제함. this == 대상 바로 오른쪽 자식, pParam == 첫 대상 */
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
        int tmp = this->key;
        BstNode *pTmp = this->right;
        this->right = nullptr;
        delete this;
        pParam.key = tmp;
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
    ~BstNode()
    {
        cout << "소멸 키 : " << this->key << endl;
        delete left;
        delete right;
    }

    /**노드 삽입 */
    BstNode &setNode(int data)
    {
        if (this == nullptr)
            return *(new BstNode(data));
        else if (this->key > data)
        {
            this->left = &this->left->setNode(data);
        }
        else if (this->key < data)
        {
            this->right = &this->right->setNode(data);
        }
        return *(this);
    }

    /**값 탐색. */
    BstNode *SearchNode(int data)
    {
        if (this == nullptr)
        {
            cout << "해당 값이 없습니다 : " << data << endl;
            return nullptr;
        }
        else if (this->key > data)
        {
            return this->left->SearchNode(data);
        }
        else if (this->key < data)
        {
            return this->right->SearchNode(data);
        }

        cout << "해당 값을 찾았습니다 : " << data << endl;

        return this;
    }

    /**값 삭제 */
    BstNode *DeleteNode(int data)
    {
        if (this == nullptr)
        {
            cout << "해당 값이 없습니다 : " << data << endl;
            return nullptr;
        }
        else if (this->key > data)
        {
            this->left = this->left->DeleteNode(data);
        }
        else if (this->key < data)
        {
            this->right = this->right->DeleteNode(data);
        }
        else if (data == this->key)
        {
            return this->DeleteLogic();
        }
        return this;
    }

    /**중위 순회 */
    void in_OrderTravers()
    {
        if (this == nullptr)
        {
            return;
        }
        this->left->in_OrderTravers();
        cout << key << endl;
        this->right->in_OrderTravers();
    }
};

int main(void)
{
    BstNode *root = new BstNode(20);
    root->setNode(13);
    root->setNode(28);
    root->setNode(6);
    root->setNode(17);
    root->setNode(15);
    root->setNode(16);
    root->DeleteNode(17);
    root->in_OrderTravers();
    delete root;
    _getch();
    return 0;
}