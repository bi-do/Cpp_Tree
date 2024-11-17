#include <iostream>
#include <conio.h>
using namespace std;
/**���� �˻� Ʈ��*/
class BstNode
{
private:
    BstNode *left;
    BstNode *right;
    int key;
public:
    BstNode(int Key)
    {
        this->left = this->right = nullptr;
        this->key = Key;
    }
    ~BstNode()
    {
        cout << "�Ҹ� Ű : " << key << endl;
        delete left;
        delete right;
    }
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
    root->in_OrderTravers();
    delete root;
    _getch();
    return 0;
}