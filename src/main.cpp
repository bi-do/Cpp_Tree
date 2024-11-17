#include <iostream>
#include <conio.h>
using namespace std;

/**���� �˻� Ʈ�� Ŭ����*/
class BstNode
{
private:
    BstNode *left;
    BstNode *right;
    int key;

    /**��� �ν��Ͻ����� ������ �ڽ��� ���� ���� ���� ã�Ƽ� ������. this == ��� �ٷ� ������ �ڽ�, pParam == ù ��� */
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

    /**����� �ڽ� ������ ���� �����ϴ� ���� */
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
        cout << "���� Ű : " << this->key << endl;
    }
    ~BstNode()
    {
        cout << "�Ҹ� Ű : " << this->key << endl;
        delete left;
        delete right;
    }

    /**��� ���� */
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

    /**�� Ž��. */
    BstNode *SearchNode(int data)
    {
        if (this == nullptr)
        {
            cout << "�ش� ���� �����ϴ� : " << data << endl;
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

        cout << "�ش� ���� ã�ҽ��ϴ� : " << data << endl;

        return this;
    }

    /**�� ���� */
    BstNode *DeleteNode(int data)
    {
        if (this == nullptr)
        {
            cout << "�ش� ���� �����ϴ� : " << data << endl;
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

    /**���� ��ȸ */
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