#ifndef DATASTURCURES_HW1_AVL_TREE_H
#define DATASTURCURES_HW1_AVL_TREE_H
#include "utilesWet2.h"
#include <cmath>
template<class T>
class AVL_Tree {
    int numOfNodes;
    T* root;
public:
    AVL_Tree<T>():numOfNodes(0),root(nullptr){};
    ~AVL_Tree()=default;
    AVL_Tree(AVL_Tree& avlTree)=default;
    T* getRoot(){return this->root;};
    void changeRoot(T* ptr){root = ptr;}
    int getNumOfNodes() const{return this->numOfNodes;};
    void setNumOfNodes(int newNum) {this->numOfNodes = newNum;};
    T* search(int key);
    StatusType_t searchAndAdd(T* toInsert);
    StatusType_t searchAndDelete(int key);
    T* getMax();
    void leftRoll(T* node);
    void rightRoll(T* node);
};

template<class T>
void deleteTree(T* ptr){
    if(ptr == nullptr){
        return;
    }
    deleteTree(ptr->leftSon);
    deleteTree(ptr->rightSon);
    delete ptr;
    ptr = nullptr;
}

template<class T>
StatusType AVL_Tree<T>::searchAndAdd(T* toInsert)
{
    // Search

    T* currentNodePtr = this->root;
    T* currentFatherNodePtr = nullptr;
    while(currentNodePtr != nullptr)
    {
        currentFatherNodePtr = currentNodePtr;
        if (currentNodePtr->key < toInsert->key)
        {
            currentNodePtr = currentNodePtr->rightSon; //Go to right son
            if (currentNodePtr == nullptr)
            {
                toInsert->father = currentFatherNodePtr;
                currentFatherNodePtr->addRightSon(toInsert);
                break;
            }
            continue;
        }
        if (currentNodePtr->key == toInsert->key)
            return StatusType::ALREADY_EXISTS;
        currentNodePtr = currentNodePtr->leftSon; //Go to right son
        if (currentNodePtr == nullptr)
        {
            toInsert->father = currentFatherNodePtr;
            currentFatherNodePtr->addLeftSon(toInsert);
            break;
        }
    }
    // Add
    if(currentFatherNodePtr == nullptr) //new root
    {
        toInsert->father = nullptr;
        this->root=toInsert;
        toInsert->updateHeight();
        this->numOfNodes++;
        return StatusType::SUCCESS;
    }

    int oldHeight = currentFatherNodePtr->height;
    while(oldHeight != currentFatherNodePtr->updateHeight())
    {
        int currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
        if(abs(currentBalanceFactor) == 2)
        {
            if(currentBalanceFactor == -2) //balance -2 -> RR/RL
            {
                if(currentFatherNodePtr->rightSon->getBalanceFactor() == 1) //RL
                {
                    rightRoll(currentFatherNodePtr->rightSon);
                    leftRoll(currentFatherNodePtr);
                    break;
                }
                //RR
                leftRoll(currentFatherNodePtr);
                break;

            }
            //balance 2 -> LR/LL
            if(currentFatherNodePtr->leftSon->getBalanceFactor() == -1) //LR
            {
                leftRoll(currentFatherNodePtr->leftSon);
                rightRoll(currentFatherNodePtr);
                break;
            }
            //LL
            rightRoll(currentFatherNodePtr);
            break;
        }

        currentFatherNodePtr = currentFatherNodePtr->father;
        if (currentFatherNodePtr == nullptr)
            break;
        oldHeight = currentFatherNodePtr->height;
    }
    this->numOfNodes++;
    return StatusType::SUCCESS;
}

template<class T>
StatusType AVL_Tree<T>::searchAndDelete(int key)
{
// Search
    T* currentNodePtr = this->root;
    if (currentNodePtr == nullptr) //no members yet
    {
        return StatusType::FAILURE;
    }
    T* currentFatherNodePtr;
    while(true)
    {
        if (currentNodePtr->key == key)
        {
            //found the node to delete
            //leaf
            currentFatherNodePtr = currentNodePtr->father;
            if(currentNodePtr->rightSon == nullptr && currentNodePtr->leftSon == nullptr)
            {
                //deleting root
                if (currentNodePtr->father == nullptr)
                {
                    numOfNodes--;
                    delete currentNodePtr;
                    root = nullptr;
                    return StatusType::SUCCESS;
                }

                if (currentNodePtr->father->rightSon == currentNodePtr)
                {
                    currentNodePtr->father->rightSon = nullptr;
                    delete currentNodePtr;
                    break;
                }
                currentNodePtr->father->leftSon = nullptr;
                delete currentNodePtr;
                break;
            }
            // has just one son
            if(currentNodePtr->rightSon != nullptr && currentNodePtr->leftSon == nullptr)
            {
                //deleting root
                if (currentNodePtr->father == nullptr)
                {
                    root = currentNodePtr->rightSon;
                    currentNodePtr->rightSon->father = nullptr;
                    numOfNodes--;
                    delete currentNodePtr;
                    return StatusType::SUCCESS;
                }

                if (currentNodePtr->father->rightSon == currentNodePtr)
                {
                    currentNodePtr->father->rightSon = currentNodePtr->rightSon;
                    currentNodePtr->rightSon->father = currentNodePtr->father;
                    delete currentNodePtr;
                    break;
                }
                currentNodePtr->father->leftSon = currentNodePtr->rightSon;
                currentNodePtr->rightSon->father = currentNodePtr->father;
                delete currentNodePtr;
                break;
            }
            if(currentNodePtr->leftSon != nullptr && currentNodePtr->rightSon == nullptr)
            {
                //deleting root
                if (currentNodePtr->father == nullptr)
                {
                    root = currentNodePtr->leftSon;
                    currentNodePtr->leftSon->father = nullptr;
                    numOfNodes--;
                    delete currentNodePtr;
                    return StatusType::SUCCESS;
                }

                if (currentNodePtr->father->rightSon == currentNodePtr)
                {
                    currentNodePtr->father->rightSon = currentNodePtr->leftSon;
                    currentNodePtr->leftSon->father = currentNodePtr->father;
                    delete currentNodePtr;
                    break;
                }
                currentNodePtr->father->leftSon = currentNodePtr->leftSon;
                currentNodePtr->leftSon->father = currentNodePtr->father;
                delete currentNodePtr;
                break;
            }
            // has two sons
            T* nodeToSwitch;
            nodeToSwitch = currentNodePtr->rightSon;
            while(nodeToSwitch->leftSon != nullptr)
            {
                nodeToSwitch = nodeToSwitch->leftSon;
            }
            if(root == currentNodePtr)
            {
                root = nodeToSwitch;
            }
            nodeToSwitch->swapNodes(currentNodePtr);
            if(currentNodePtr->father->leftSon == currentNodePtr)
            {
                if(currentNodePtr->rightSon == nullptr)
                {
                    currentNodePtr->father->leftSon = nullptr;
                }
                else
                {
                    currentNodePtr->father->leftSon = currentNodePtr->rightSon;
                }
                if(currentNodePtr->rightSon !=nullptr)
                    currentNodePtr->rightSon->father = currentNodePtr->father;
            }
            else{
                currentNodePtr->father->rightSon = currentNodePtr->rightSon;
                if(currentNodePtr->rightSon !=nullptr)
                    currentNodePtr->rightSon->father = currentNodePtr->father;
            }
            currentFatherNodePtr = currentNodePtr->father;
            currentNodePtr->father = nullptr;
            delete currentNodePtr;
            break;
        }
        if (currentNodePtr->key < key)
        {
            currentNodePtr = currentNodePtr->rightSon; //Go to right son
            if (currentNodePtr == nullptr)
            {
                return StatusType::FAILURE;
            }
            continue;
        }

        currentNodePtr = currentNodePtr->leftSon; //Go to right son
        if (currentNodePtr == nullptr)
        {
            return StatusType::FAILURE;
        }
    }

    // fixing the tree with rolls

    int oldHeight = currentFatherNodePtr->height;
    int currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
    while(oldHeight != currentFatherNodePtr->updateHeight() || abs(currentBalanceFactor) == 2)
    {

        if(abs(currentBalanceFactor) == 2)
        {
            if(currentBalanceFactor == -2) //balance -2 -> RR/RL
            {
                if(currentFatherNodePtr->rightSon->getBalanceFactor() == 1) //RL
                {
                    rightRoll(currentFatherNodePtr->rightSon);
                    leftRoll(currentFatherNodePtr);
                    currentFatherNodePtr = currentFatherNodePtr->father;
                    if (currentFatherNodePtr == nullptr)
                        break;
                    oldHeight = currentFatherNodePtr->height;
                    currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
                    continue;
                }
                //RR
                leftRoll(currentFatherNodePtr);
                currentFatherNodePtr = currentFatherNodePtr->father;
                if (currentFatherNodePtr == nullptr)
                    break;
                oldHeight = currentFatherNodePtr->height;
                currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
                continue;

            }
            //balance 2 -> LR/LL
            if(currentFatherNodePtr->leftSon->getBalanceFactor() == -1) //LR
            {
                leftRoll(currentFatherNodePtr->leftSon);
                rightRoll(currentFatherNodePtr);
                currentFatherNodePtr = currentFatherNodePtr->father;
                if (currentFatherNodePtr == nullptr)
                    break;
                oldHeight = currentFatherNodePtr->height;
                currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
                continue;
            }
            //LL
            rightRoll(currentFatherNodePtr);
            currentFatherNodePtr = currentFatherNodePtr->father;
            if (currentFatherNodePtr == nullptr)
                break;
            oldHeight = currentFatherNodePtr->height;
            currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
            continue;
        }

        currentFatherNodePtr = currentFatherNodePtr->father;
        if (currentFatherNodePtr == nullptr)
            break;
        oldHeight = currentFatherNodePtr->height;
        currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
    }
    this->numOfNodes--;
    return StatusType::SUCCESS;

}

template <class T>
void AVL_Tree<T>::leftRoll(T* node)
{
    T *newHead,*tempNode;
    newHead = node->rightSon;
    tempNode = newHead->leftSon;
    newHead->leftSon = node;
    node->rightSon = tempNode;
    //correcting fathers
    newHead->father=node->father;
    node->father=newHead;
    if (tempNode!= nullptr)
    {
        tempNode->father=node;
    }
    // correcting root and father's son
    if (newHead->father == nullptr)
    {
        this->root = newHead;
    }
    else if (newHead->father->rightSon == node)
    {
        newHead->father->rightSon = newHead;
    }
    else if (newHead->father->leftSon == node)
    {
        newHead->father->leftSon = newHead;
    }
    node->updateHeight();
    newHead->updateHeight();
}
template<class T>
void AVL_Tree<T>::rightRoll(T* node)
{
    T *newHead,*tempNode;
    newHead = node->leftSon;
    tempNode = newHead->rightSon;
    newHead->rightSon = node;
    node->leftSon = tempNode;
    //correcting fathers
    newHead->father=node->father;
    node->father=newHead;
    if (tempNode!= nullptr)
    {
        tempNode->father=node;
    }
    // correcting root
    if (newHead->father == nullptr)
    {
        this->root = newHead;
    }
    else if (newHead->father->rightSon == node)
    {
        newHead->father->rightSon = newHead;
    }
    else if (newHead->father->leftSon == node)
    {
        newHead->father->leftSon = newHead;
    }
    node->updateHeight();
    newHead->updateHeight();
}

template<class T>
T* AVL_Tree<T>::search(int key){
    T* ptr = this->root;
    while (ptr){
        if (key == ptr->key){
            return ptr;
        }
        if (key < ptr->key){
            ptr = ptr->leftSon;
            continue;
        }
        if (key > ptr->key){
            ptr = ptr->rightSon;
            continue;
        }
    }
    return new T(0, nullptr, nullptr);
}
template<class T>
T* AVL_Tree<T>::getMax(){
    T* ptr = this->root;
    T* head = this->root;
    while (ptr){
        ptr = ptr->rightSon;
        if(!ptr){
            return head;
        }
        head = head->rightSon;
    }
    return nullptr;
}

// avl_tree end
#endif //DATASTURCURES_HW1_AVL_TREE_H