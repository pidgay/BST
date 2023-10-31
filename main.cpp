#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
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
};

template <class T>
class BST{
public:
    T* rootNode = nullptr;

    bool checkIfEmpty(){
        return rootNode == nullptr ? true : false;
    }

    bool checkIfRightOrLeft(T* node){
        return node->parentNode->leftNode == node ? false : true;
    }

    void addRootNode(T* newNode){
        rootNode = newNode;
    }

    bool addNewNode(T* newNode){
        if(checkIfEmpty()){
            addRootNode(newNode);
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
        T* parent = nodeToRemove->parentNode;
        T* rotateNode;
        if(checkIfRightOrLeft(nodeToRemove)){

        }
        else{

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
        for (int i = 0; i < 100; ++i) {
            currentNode->display();
            if(currentNode-> leftNode != nullptr){
                currentNode = currentNode->leftNode;
            }
            else if(currentNode->rightNode != nullptr){
                currentNode = currentNode->rightNode;
            }
            else{
                break;
            }
        }
    }

    void clearTree(){

    }
};

int main(){
    srand(time(nullptr));

    class BST<Data>* tree = new BST<Data>;

    for (int i = 0; i < 100; ++i) {
        class Data* newNode = new Data();
        tree->addNewNode(newNode);
    }
    return 0;
}