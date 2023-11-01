#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

class Data{
public:
    int number{};
    char character{};

    class Data* leftNode = nullptr;
    class Data* rightNode = nullptr;
    class Data* parentNode = nullptr;

    Data() {
        number = 1 + rand() % 10000;
        character = 'A' + (rand() % 26);
    }

    int compare(Data* node) {
        if(node == nullptr){
            return false;
        }
        else {
            if(number == node->number){
                if(character ==  node->character){
                    return 0;
                }
                return character < node->character ? -1 : 1;
            }
            return number < node->number ? -1 : 1;
        }
    }

    void display() {
        cout
                << "Number: " << number << "    "
                << "Character: " << character << endl;
    }

    int getHeight(){
        if (leftNode == nullptr && rightNode == nullptr){
            return 1;
        }
        else if(leftNode != nullptr && rightNode == nullptr){
            return 1 + leftNode->getHeight();
        }
        else if(leftNode == nullptr && rightNode != nullptr){
            return 1 + rightNode->getHeight();
        }
        else{
            return 1 + max(leftNode->getHeight(), rightNode->getHeight());
        }
    }

};

template <class T>
class BST{
public:
    int numberOfNodes = {};
    int treeHeight = {};
    T* rootNode = {};
    T* inOrderList = {};
    T* preOrderList = {};

    BST(){
        numberOfNodes = 0;
        treeHeight = 0;
        rootNode = nullptr;
        inOrderList = new T[numberOfNodes];
        preOrderList = new T[numberOfNodes];
    }

    bool checkIfEmpty(){
        return rootNode == nullptr ? true : false;
    }

    bool checkIfRightOrLeft(T* node){
        return node->parentNode->leftNode == node ? false : true;
    }

    int getTreeHeight(){
        return (rootNode == nullptr) ? 0 : rootNode->getHeight();
    }

    void preOrderTraversal(T* currentNode){
        if (currentNode == nullptr){
            return;
        }
        cout << currentNode->number << endl;
        preOrderTraversal(currentNode->leftNode);
        preOrderTraversal(currentNode->rightNode);
    }

    T* preOrderSuccessor(T* node){

    }

    void inOrderTraversal(T* currentNode){
        if (currentNode == nullptr){
            return;
        }
        inOrderTraversal(currentNode->leftNode);
        cout << currentNode->number << endl;
        inOrderTraversal(currentNode->rightNode);
    }

    T* inOrderSuccessor(T* node){
        T* currentNode = rootNode;
        T* successorNode;
        while(!currentNode && currentNode->compare(node) != 0){
            if(currentNode->compare(node) == -1) {
                currentNode = currentNode->leftNode;
            }
            else {
                currentNode = currentNode->rightNode;
            }
        }

        if (!currentNode){
            return nullptr;
        }

        if (currentNode->rightNode){
            successorNode = currentNode->rightNode;
            while(successorNode->leftNode){
                successorNode = successorNode->leftNode;
            }
            return successorNode;
        }
        else{
            while(currentNode->parentNode && currentNode->parentNode->leftNode){
                currentNode = currentNode->parentNode;
            }
            return currentNode->parentNode;
        }

    }

    void addRootNode(T* newNode){
        rootNode = newNode;
    }

    bool addNewNode(T* newNode){
        if(checkIfEmpty()){
            addRootNode(newNode);
            numberOfNodes++;
            return true;
        }
        else {
            T* previousNode = nullptr;
            T* currentNode = rootNode;

            while(currentNode != nullptr){
                if(currentNode->compare(newNode) == 0){
                    return false;
                }
                previousNode = currentNode;
                if(currentNode->compare(newNode) == -1){
                    currentNode = currentNode->rightNode;
                }
                else{
                    currentNode = currentNode->leftNode;
                }
            }
            newNode->parentNode = previousNode;
            if (previousNode->compare(newNode) == -1) {
                previousNode->rightNode = newNode;
            }
            else{
                previousNode->leftNode= newNode;
            }
            numberOfNodes++;
            return true;
        }
    }

    bool removeNodeWithoutChildren(T* nodeToRemove){
        if(checkIfRightOrLeft(nodeToRemove)) {
            nodeToRemove->parentNode->rightNode = nullptr;
            delete nodeToRemove;
        }
        else{
            nodeToRemove->parentNode->leftNode = nullptr;
        }
        return true;
    }

    bool removeNodeWithOneChildren(T* nodeToRemove){
        T* parent = nodeToRemove->parentNode;
        T* rotateNode;
        if(checkIfRightOrLeft(nodeToRemove)){
            if(nodeToRemove->leftNode == nullptr){
                rotateNode = nodeToRemove->rightNode;
            }
            else {
                rotateNode = nodeToRemove->leftNode;
            }
            parent->rightNode = rotateNode;
        }
        else{
            if(nodeToRemove->leftNode == nullptr){
                rotateNode = nodeToRemove->rightNode;
            }
            else {
                rotateNode = nodeToRemove->leftNode;
            }
            parent->leftNode = rotateNode;
        }
        delete nodeToRemove;
        return true;
    }

    bool removeNodeWithBothChildren(T* nodeToRemove){
        T* successorNode = inOrderSuccessor(nodeToRemove->rightNode);
        T* parentNode = nodeToRemove->parentNode;
        if(nodeToRemove == parentNode->leftNode){
            
        }
    }

    T* findNode(T* node){
        if(checkIfEmpty()){
            return nullptr;
        }
        else {
            T* currentNode = rootNode;

            while(currentNode != nullptr){
                if(currentNode->compare(node) == 0){
                    return currentNode;
                }

                if(currentNode->compare(node) == -1){
                    currentNode = currentNode->rightNode;
                }
                else{
                    currentNode = currentNode->leftNode;
                }
            }
            return currentNode;
        }
    }

    T* findMinimum(T* currentNode){
        while(currentNode->leftNode != nullptr){
            currentNode = currentNode->leftNode;
        }
        return currentNode;
    }

    bool findAndRemoveNode(T* node){
        T* nodeToRemove = findNode(node);
        if (nodeToRemove == nullptr) {
            return false;
        }

        if(nodeToRemove->rightNode == nullptr && nodeToRemove->leftNode == nullptr){
            return removeNodeWithoutChildren(nodeToRemove);
        }
        else if(nodeToRemove->rightNode == nullptr || nodeToRemove->leftNode == nullptr){
            return removeNodeWithOneChildren(nodeToRemove);
        }
        else {
            return removeNodeWithBothChildren(nodeToRemove);
        }
    }

    void printTreeInfo(){
        T* currentNode = rootNode;
        for (int i = 0; i < 50; ++i) {

        }
    }

    void display(T *currentNode, int indent) {
        if (currentNode != nullptr) {
            Display(currentNode->leftNode, indent + 1);
            if (indent > 0)
                cout << setw(indent) << " ";
            cout << currentNode->number << endl;
            Display(currentNode->rightNode, indent + 1);
        }
    }

    void clearTree(){

    }
};

int main(){
    srand(time(nullptr));

    class BST<Data>* tree = new BST<Data>;

    for (int i = 0; i < 10; ++i) {
        class Data* newNode = new Data();
        tree->addNewNode(newNode);
    }

    tree->inOrderTraversal(tree->rootNode);
    cout << "=============" << endl;
    tree->preOrderTraversal(tree->rootNode);

    return 0;
}