#include "bst.h"
#include "treedb.h"

BstNode *BstNode::DeleteNextValue(BstNode &pParam)
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
    if (pTmp != nullptr)
    {
        pTmp = &pTmp->BalanceUpdate();
    }
    this->right = nullptr;
    delete this;
    return pTmp;
}
BstNode *BstNode::DeleteLogic()
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
BstNode &BstNode::insertNode(int data)
{
    if (this->key > data)
    {
        if (this->left == nullptr)
        {
            this->left = &this->NewNode(data);
        }
        else
            this->left = &this->left->insertNode(data);
    }
    else if (this->key < data)
    {
        if (this->right == nullptr)
        {
            this->right = &this->NewNode(data);
        }
        else
            this->right = &this->right->insertNode(data);
    }

    return this->BalanceUpdate();
}
const BstNode *BstNode::SearchNode(int data) const
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
BstNode *BstNode::DeleteNode(int data)
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
void BstNode::in_OrderTraversal()
{

    if (this == nullptr)
    {
        return;
    }
    this->left->in_OrderTraversal();
    cout << "키 값 : " << this->key << " 높이 : " << this->height << " 색깔 : " << (this->color == true ? "black" : "red") << endl;
    this->right->in_OrderTraversal();
}

void BstNode::post_OrderTraversal()
{
    if (this == nullptr)
    {
        return;
    }
    cout << "키 값 : " << this->key << " 높이 : " << this->height << " 색깔 : " << (this->color == true ? "black" : "red") << endl;
    this->left->post_OrderTraversal();
    this->right->post_OrderTraversal();
}

BstNode &AvlNode::rotation()
{
    int BF = this->getBalanceFactor();
    BstNode *Tmp = this;
    if (BF < -1)
    {
        AvlNode *rightTmp = static_cast<AvlNode *>(this->getRight());
        if (rightTmp->getBalanceFactor() > 0)
        {
            this->right = &rightTmp->RitgtRotate();
            Tmp = &this->LeftRotate();
        }
        else
        {
            Tmp = &this->LeftRotate();
        }
    }
    else if (BF > 1)
    {
        AvlNode *leftTmp = static_cast<AvlNode *>(this->getLeft());
        if (leftTmp->getBalanceFactor() < 0)
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

BstNode &AvlNode::LeftRotate()
{
    TreeDB *tmp = TreeDB::getTree();

    AvlNode *pTmp = static_cast<AvlNode *>(this->right);
    this->right = pTmp->getLeft();
    pTmp->setLeft(this);
    this->heightUpdate();
    pTmp->heightUpdate();
    if (tmp->rootNode == this)
    {
        tmp->rootNode = pTmp;
    }
    cout << "Left 회전 완료" << endl;

    return *pTmp;
}

BstNode &AvlNode::RitgtRotate()
{
    TreeDB *tmp = TreeDB::getTree();
    AvlNode *pTmp = static_cast<AvlNode *>(this->left);
    this->left = pTmp->getRight();
    pTmp->setRight(this);

    this->heightUpdate();
    pTmp->heightUpdate();
    if (tmp->rootNode == this)
    {
        tmp->rootNode = pTmp;
    }
    cout << "Right 회전 완료" << endl;
    return *pTmp;
}
BstNode *RedBlackNode::getuncle()
{
    if (this->parent->getparent() == nullptr)
    {
        return nullptr;
    }

    if (this->parent == this->parent->getparent()->getLeft())
    {
        return this->parent->getparent()->getRight();
    }
    else
        return this->parent->getparent()->getLeft();
}

BstNode *RedBlackNode::getBro()
{
    if (this == this->getparent()->getLeft())
    {
        return this->getparent()->getRight();
    }
    else
        return this->getparent()->getLeft();
}
BstNode &RedBlackNode::insertNode(int data)
{
    TreeDB *root = TreeDB::getTree();
    BstNode *rootNode = root->rootNode;
    BstNode *currentNode = rootNode;
    while (currentNode != nullptr)
    {
        if (currentNode->getKey() < data)
        {
            rootNode = currentNode;
            currentNode = currentNode->getRight();
        }
        else if (currentNode->getKey() > data)
        {
            rootNode = currentNode;
            currentNode = currentNode->getLeft();
        }
        else
            return *currentNode;
    }
    if (rootNode->getKey() < data)
    {
        rootNode->setRight(&rootNode->NewNode(data));
        insertRuleCheck(*static_cast<RedBlackNode *>(rootNode->getRight()));
    }
    else
    {
        rootNode->setLeft(&rootNode->NewNode(data));
        insertRuleCheck(*static_cast<RedBlackNode *>(rootNode->getLeft()));
    }

    return *currentNode;
}
RedBlackNode &RedBlackNode::NewNode(int data)
{
    RedBlackNode *NewTmp = new RedBlackNode(data);
    NewTmp->parent = this;

    return *NewTmp;
}

void RedBlackNode::insertRuleCheck(RedBlackNode &grandSonNode)
{
    TreeDB *root = TreeDB::getTree();
    /**체크하는 노드가 루트 일 시. */
    if (&grandSonNode == root->rootNode)
    {
        grandSonNode.setColor(true);
        return;
    }
    /**만약 자신의 부모가 Red이고 */
    else if (grandSonNode.parent->getColor() == false)
    {
        /**자신의 삼촌이 black이거나 없다면 */
        if (grandSonNode.getuncle() == nullptr || grandSonNode.getuncle()->getColor() == true)
        {
            BstNode *grandP = grandSonNode.getparent()->getparent();
            if ((grandP->getLeft() != nullptr && (&grandSonNode == grandP->getLeft()->getLeft())) || (grandP->getRight() != nullptr && (&grandSonNode == grandP->getRight()->getRight())))
            {
                rotation(*grandP, grandSonNode);
                grandSonNode.getparent()->setColor(true);
                grandP->setColor(false);
            }
            else
            {
                rotation(*grandP, grandSonNode);
                grandSonNode.setColor(true);
                grandP->setColor(false);
            }
        }
        /**자신의 삼촌이 Red라면 */
        else
        {
            grandSonNode.getparent()->setColor(true);
            grandSonNode.getuncle()->setColor(true);
            grandSonNode.getparent()->getparent()->setColor(false);
            insertRuleCheck(*static_cast<RedBlackNode *>(grandSonNode.getparent()->getparent()));
        }
    }
}
void RedBlackNode::rotation(BstNode &grandParantNode, BstNode &grandSonNode)
{
    RedBlackNode *grandP = static_cast<RedBlackNode *>(&grandParantNode);
    RedBlackNode *grandS = static_cast<RedBlackNode *>(&grandSonNode);

    if (grandS->parent == grandP->left)
    {
        /**RR회전 */
        if (grandS == grandP->left->getLeft())
        {
            grandS->RightRotate(*grandP);
        }
        /**LR회전 */
        else if (grandS == grandP->left->getRight())
        {
            grandS->LeftRotate(*static_cast<RedBlackNode *>(grandS->parent));
            grandS->RightRotate(*grandP);
        }
    }
    else
    {
        /**LL회전 */
        if (grandS == grandP->right->getRight())
        {
            grandS->LeftRotate(*grandP);
        }
        /**LR회전 */
        else if (grandS == grandP->right->getLeft())
        {
            grandS->RightRotate(*static_cast<RedBlackNode *>(grandS->parent));
            grandS->LeftRotate(*grandP);
        }
    }
}
void RedBlackNode::RightRotate(RedBlackNode &pParam)
{
    TreeDB *root = TreeDB::getTree();
    RedBlackNode *pLeft = static_cast<RedBlackNode *>(pParam.getLeft());

    if (pParam.parent == nullptr)
    {
        root->rootNode = pLeft;
        root->rootNode->setColor(true);
    }
    else if (pParam.parent->getLeft() == &pParam)
    {
        pParam.parent->setLeft(pLeft);
    }
    else
        pParam.parent->setRight(pLeft);

    pLeft->setparent(*pParam.parent);
    pParam.setparent(*pLeft);
    pParam.setLeft(pLeft->getRight());
    pLeft->setRight(&pParam);

    cout << "RR 회전 완료" << endl;
}
void RedBlackNode::LeftRotate(RedBlackNode &pParam)
{
    TreeDB *root = TreeDB::getTree();
    RedBlackNode *pRight = static_cast<RedBlackNode *>(pParam.getRight());

    if (pParam.parent == nullptr)
    {
        root->rootNode = pRight;
        root->rootNode->setColor(true);
    }
    else if (pParam.parent->getLeft() == &pParam)
    {
        pParam.parent->setLeft(pRight);
    }
    else
        pParam.parent->setRight(pRight);

    pRight->setparent(*pParam.parent);
    pParam.setparent(*pRight);
    pParam.setRight(pRight->getLeft());
    pRight->setLeft(&pParam);
    cout << "LL 회전 완료" << endl;
}
BstNode *RedBlackNode::DeleteNode(int data)
{
    TreeDB *root = TreeDB::getTree();
    BstNode *rootNode = root->rootNode;
    BstNode *currentNode = rootNode;
    while (currentNode != nullptr)
    {
        if (currentNode->getKey() < data)
        {
            rootNode = currentNode;
            currentNode = currentNode->getRight();
        }
        else if (currentNode->getKey() > data)
        {
            rootNode = currentNode;
            currentNode = currentNode->getLeft();
        }
        else
            break;
    }
    if (currentNode == nullptr)
    {
        cout << "삭제할 노드가 존재하지 않습니다." << endl;
        return nullptr;
    }
    DeleteNodeLogic(currentNode);
    return nullptr;
}

void RedBlackNode::DeleteNodeLogic(BstNode *currentNode)
{
    if (currentNode->getLeft() == nullptr)
    {
        BstNode *pTmp = currentNode->getRight();
        RedBlackNode *pParent = static_cast<RedBlackNode *>(currentNode->getparent());
        pTmp = pParent->setParentChild(pParent, currentNode, pTmp);
        RedBlackBlanceUpdate(*currentNode, pTmp);
    }
    else if (currentNode->getRight() == nullptr)
    {
        BstNode *pTmp = currentNode->getLeft();
        RedBlackNode *pParent = static_cast<RedBlackNode *>(currentNode->getparent());
        pTmp = pParent->setParentChild(pParent, currentNode, pTmp);
        RedBlackBlanceUpdate(*currentNode, pTmp);
    }
    else
    {
        BstNode *pTmp = currentNode->getRight();
        while (pTmp->getLeft() != nullptr)
        {
            pTmp = pTmp->getLeft();
        }
        currentNode->setKey(pTmp->getKey());
        DeleteNodeLogic(pTmp);
    }
}

void RedBlackNode::RedBlackBlanceUpdate(BstNode &pDelete, BstNode *pTmp, bool doubly)
{
    TreeDB *DB = TreeDB::getTree();
    RedBlackNode *tmp = static_cast<RedBlackNode *>(pTmp);
    if (pDelete.getColor() == false)
    {
        if (tmp->IsNil == true)
        {
            if (tmp == tmp->getparent()->getLeft())
            {
                tmp->getparent()->setLeft(nullptr);
            }
            else
                tmp->getparent()->setRight(nullptr);
            delete tmp;
        }
        delete &pDelete;
        return;
    }
    /**삭제할 노드가 루트노드일 때*/
    else if (&pDelete == DB->rootNode)
    {
        if (tmp->IsNil == true)
        {
            DB->rootNode = nullptr;
        }
        else
        {
            DB->rootNode = tmp;
            tmp->setColor(true);
        }
        delete &pDelete;
        return;
    }
    /**루트 노드를 재검증 할 시. */
    else if (tmp == DB->rootNode)
    {
        DB->rootNode = tmp;
        tmp->setColor(true);
        return;
    }
    /**대체 노드의 색이 빨강색인 경우 */
    else if (tmp->getColor() == false)
    {
        tmp->setColor(true);
    }
    /**형제 노드가 검정색인 경우 */
    else if (tmp->getBro()->getColor() == true)
    {
        RedBlackNode *broNode = static_cast<RedBlackNode *>(tmp->getBro());
        RedBlackNode *broParent = static_cast<RedBlackNode *>(tmp->getBro()->getparent());
        /**형제가 오른쪽이며 , 형제의 오른쪽 자식이 RED인 경우 */
        if (broNode == broNode->getparent()->getRight() && broNode->getRight() != nullptr && broNode->getRight()->getColor() == false)
        {
            broLeftRotate(broNode, broParent);
        }
        /**형제가 왼쪽이며 , 형제의 왼쪽 자식이 RED인 경우 */
        else if (broNode == broNode->getparent()->getLeft() && broNode->getLeft() != nullptr && broNode->getLeft()->getColor() == false)
        {
            broRightRotate(broNode, broParent);
        }
        /**형제가 왼쪽이며 , 형제의 오른쪽 자식이 RED인 경우 */
        else if (broNode == broNode->getparent()->getLeft() && broNode->getRight() != nullptr && broNode->getRight()->getColor() == false)
        {
            broNode->setColor(false);
            broNode->getRight()->setColor(true);
            LeftRotate(*broNode);
            broRightRotate(static_cast<RedBlackNode *>(broParent->getLeft()), broParent);
        }
        /**형제가 오른쪽이며 , 형제의 왼쪽 자식이 RED인 경우 */
        else if (broNode == broNode->getparent()->getRight() && broNode->getLeft() != nullptr && broNode->getLeft()->getColor() == false)
        {
            broNode->setColor(false);
            broNode->getRight()->setColor(true);
            RightRotate(*broNode);
            broLeftRotate(static_cast<RedBlackNode *>(broParent->getRight()), broParent);
        }
        /**형제의 자식이 모두 black일 때*/
        else
        {
            broNode->setColor(false);
            RedBlackBlanceUpdate(pDelete, tmp->parent, true);
        }
    }
    /**형제 노드가 빨강색일 경우 */
    else if (tmp->getBro()->getColor() == false)
    {
        tmp->getparent()->setColor(false);
        tmp->getBro()->setColor(true);
        if (tmp->getBro() == tmp->getparent()->getRight())
        {
            LeftRotate(*static_cast<RedBlackNode *>(tmp->getparent()));
        }
        else
            RightRotate(*static_cast<RedBlackNode *>(tmp->getparent()));
        RedBlackBlanceUpdate(pDelete, tmp, true);
    }

    if (doubly == false)
    {
        if (tmp->IsNil == true)
        {
            if (tmp == tmp->getparent()->getLeft())
            {
                tmp->getparent()->setLeft(nullptr);
            }
            else
                tmp->getparent()->setRight(nullptr);
            delete tmp;
        }
        cout << "삭제 완료 : " << pDelete.getKey() << endl;
        delete &pDelete;
    }
}
BstNode *RedBlackNode::setParentChild(RedBlackNode *pParent, BstNode *pOldChild, BstNode *pNewChild)
{
    /**닐 노드 생성 */
    if (pNewChild == nullptr)
    {
        pNewChild = new RedBlackNode();
        pNewChild->setColor(true);
    }
    pNewChild->setparent(*pParent);
    if (pParent != nullptr)
    {
        if (pOldChild == pParent->getRight())
        {
            pParent->setRight(pNewChild);
        }
        else
            pParent->setLeft(pNewChild);
    }

    pOldChild->setLeft(nullptr);
    pOldChild->setRight(nullptr);
    return pNewChild;
}