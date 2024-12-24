#include "RedBlackTree.h"
#include <iostream>
#include <set>
#include <climits>
#include <vector>

using namespace std;

RedBlackTree :: RedBlackTree(){
    root = nullptr;
    numItems = 0;
}


RBTNode* RedBlackTree :: Clone(RBTNode* node){
    if (node == nullptr){
        return nullptr;
    }

    RBTNode* newNode = new RBTNode;
    newNode->data = node->data;
    newNode->color = node->color;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;

    newNode->left = Clone(node->left);
    if (newNode->left != nullptr) {
        newNode->left->parent = newNode;
    }

    newNode->right = Clone(node->right);
    if (newNode->right != nullptr) {
        newNode->right->parent = newNode;
    }

    return newNode;
}

//creates a deep copy of another Red-Black Tree
RedBlackTree :: RedBlackTree(const RedBlackTree& other){
    root = Clone(other.root);
    numItems = other.numItems;
}

bool RedBlackTree :: isEmpty (){
    if(root == nullptr){
        return true;
    }
    return false;
}

void RedBlackTree::Insert(int value) {
    // Create a new node to hold the inserted value
    RBTNode* node = new RBTNode;
    node->data = value;
    node->color = COLOR_RED;  
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;

    if (isEmpty()) {
        root = node;
        root->color = COLOR_BLACK;  //the root must always be black
    } else {
        RBTNode* temp = root;
        RBTNode* prev = nullptr;

        while (temp != nullptr) {
            prev = temp;
            if (value < temp->data) {
                temp = temp->left;
            } else if (value > temp->data) {
                temp = temp->right;
            } else {
                //if the value already exists, clean up and throw an exception
                delete node;
                throw std::invalid_argument("This value already exists in the tree.");
            }
        }

        node->parent = prev;
        if (value < prev->data) {
            prev->left = node;
        } else {
            prev->right = node;
        }

        Balance(node);
    }

    numItems++;
}

// gets the uncle of a node (the sibling of its parent)
RBTNode* RedBlackTree :: getUncle(RBTNode* node) {
    if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
        return nullptr; 
    }

    RBTNode* parent = node->parent;
    RBTNode* grandparent = parent->parent;

    if (grandparent->left == parent) {
        return grandparent->right; 
    } else {
        return grandparent->left; 
    }
}


void RedBlackTree :: Balance(RBTNode* node){
    RBTNode* parent = nullptr;
    RBTNode *grandparent = nullptr;
//used loop to fix violations
    while (node != root && node->parent->color == COLOR_RED && node->color == COLOR_RED) {
        parent = node -> parent;
        grandparent = parent->parent;
        RBTNode *uncle = getUncle(node);

        //case#1: uncle is red
        if(uncle != nullptr && uncle->color == COLOR_RED){
            parent->color = COLOR_BLACK;
            uncle->color = COLOR_BLACK;
            grandparent->color = COLOR_RED;
            node = grandparent;
            
        } else {
            //cases 2&3: uncle is black
            if (parent == grandparent->left){

                if(node == parent->left){ //left-left
                    rotateRight(grandparent);
                    parent->color = COLOR_BLACK;
                    grandparent->color = COLOR_RED;
                    node = parent;
                } else { //left-right
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
            } else {

                if(node == parent->right){ //right-right
                    rotateLeft(grandparent);
                    parent->color = COLOR_BLACK;
                    grandparent->color = COLOR_RED;
                    node = parent;
                } else { //right-left
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
            }
        }
    }
    root->color = COLOR_BLACK; 
}

// https://www.geeksforgeeks.org/introduction-to-red-black-tree/#4-rotation
// helped to structure both rotations
void RedBlackTree :: rotateLeft(RBTNode* node){
    RBTNode *parent = node->parent;
    RBTNode *child = node->right; 

    node->right = child->left;
    if(child->left != nullptr){ 
        child->left->parent = node;
    }

    child->parent = node->parent;
    if(node -> parent == nullptr){
        root = child;
    } else if (node == parent->left){
        parent->left = child;
    } else {
        parent->right = child;
    }
    child -> left = node;
    node -> parent = child;
}

void RedBlackTree :: rotateRight(RBTNode* node){
    RBTNode *grparent = node->parent;
    RBTNode *child = node->left;

    node->left = child->right;
    if(child->right != nullptr){
        child->right->parent = node;
    }

    child->parent = node->parent;
    if(node -> parent == nullptr){
        root = child;
    }else if (node == grparent->left){
        grparent->left = child;
    } else {
        grparent->right = child;
    }
    child -> right = node;
    node -> parent = child;
}


bool RedBlackTree :: Contains(int n){
    RBTNode *current = root;
    RBTNode *parent = nullptr;

    while (current != nullptr){
        parent = current;
        if(n < current->data){
            current = parent->left;
        } else if (n > current->data){
            current = parent ->right;
        } else {
            return true;
            break;
        }
    }
    return false;
}

int RedBlackTree :: GetMin(){
    RBTNode* node = root;
    while(node != nullptr && node ->left !=nullptr){
        node = node->left;
    }

    return node->data;
}

int RedBlackTree :: GetMax(){
    RBTNode* node = root;
    while(node != nullptr && node->right !=nullptr){
        node = node->right;
    }

    return node->data;
}

int RedBlackTree :: Size(){
    return numItems;  
}


string RedBlackTree :: ToInfixString(RBTNode *nd) const{ 
    if(nd == nullptr){
        return "";
    }
    
    string current = to_string(nd -> data);
    string c = "";
    if(nd -> color == COLOR_RED){
        c = "R";
    } else {
        c = "B";
    }

    string left = ToInfixString(nd -> left);
    string right = ToInfixString(nd -> right);

    return left + " " + c + current + " " + right;
}

string RedBlackTree :: ToPrefixString(RBTNode *nd) const{ 
    if(nd == nullptr){
        return "";
    }
    string current = to_string(nd -> data);
    string c = "";
    if(nd -> color == COLOR_RED){
        c = "R";
    } else {
        c = "B";
    }

    string left = ToPrefixString(nd -> left);
    string right = ToPrefixString(nd -> right);
    
    return " " + c + current + " " + left + right;
}

string RedBlackTree :: ToPostfixString(RBTNode *nd) const{ 
    if(nd == nullptr){
        return "";
    }
    string current = to_string(nd -> data);
    string c = "";
    if(nd -> color == COLOR_RED){
        c = "R";
    } else {
        c = "B";
    }

    string left = ToPostfixString(nd -> left);
    string right = ToPostfixString(nd -> right);

    return left + right + " " + c + current + " ";
}

//zybook 7 helped me - thank you zybook
void deleteNodes(RBTNode* nd) {
    if (nd == nullptr) {
        return;
    }

    deleteNodes(nd->left);
    deleteNodes(nd->right);

    nd->left = nullptr;
    nd->right = nullptr;
    nd->parent = nullptr;

    delete nd;
}

// destructor to clean up the tree
RedBlackTree :: ~RedBlackTree(){
    deleteNodes (root);
    root = nullptr;
}

RBTNode* RedBlackTree :: Get(int data){
    RBTNode* current = root;
    RBTNode* D = nullptr;

    if(!Contains(data)){
        throw std::invalid_argument("Cannot find value in the tree");
    }

    while (current != nullptr) {
        if (current->data > data) {
            current = current->left;
        } else if (current->data < data) {
            current = current->right;
        } else {
            D = current;
            break; 
        }
    }
    return D;
}

RBTNode* RedBlackTree :: GetReplacement(RBTNode* D){
    if (D->left!=nullptr && D->right!=nullptr) {
        // if both children exist, find the in-order successor
        RBTNode* current = D->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    // return the non-null child if one exists
    if(D->left != nullptr) return D->left;
    if (D->right != nullptr) return D->right;
    return nullptr;
}


RBTNode* RedBlackTree::getSibling(RBTNode* R) {
    if (R == nullptr || R->parent == nullptr) {
        return nullptr; 
    }

    RBTNode* parent = R->parent;
    RBTNode* sibling = nullptr;
    
   
    if (parent->left == R || parent->left == nullptr) {

        sibling = parent->right; 
    } else if (parent->right == R || parent->right == nullptr) {

        sibling = parent->left;
    }

    if (sibling != nullptr) {
  
    } 


    return sibling;
}


//used your pseudocode for inspiration
void RedBlackTree :: FixDoubleBlack(RBTNode* node){
    if (node == root || node == nullptr){ 
        return;
    }

    RBTNode* sibling = nullptr;
    RBTNode* parent = node->parent;

    if(parent->left == node){
        sibling = parent->right;
    }else{
        sibling = parent->left;
    }
 
    if (sibling == nullptr) {

       FixDoubleBlack(parent);
        return;
    }

    if(sibling->color == COLOR_RED){
        parent->color = COLOR_RED;
        sibling->color = COLOR_BLACK;

        if(sibling == parent->right){
            rotateLeft(parent);
        } else {
            rotateRight(parent);
        }
        if (parent->left == node) {
            sibling = parent->right;
        } else {
            sibling = parent->left;
        }
    } 

    if (sibling->color == COLOR_BLACK){

        if ((sibling->left == nullptr || sibling->left->color == COLOR_BLACK) &&
        (sibling->right == nullptr || sibling->right->color == COLOR_BLACK)){
            sibling->color = COLOR_RED;
            if(parent->color == COLOR_RED){
                parent->color = COLOR_BLACK;
            } else {
                FixDoubleBlack(parent);
            }
        } else {


            if (sibling == parent->right) {
                //Right-Right
                if (sibling->right != nullptr && sibling->right->color == COLOR_RED) {
                    sibling->right->color = sibling->color;
                    sibling->color = parent->color;
                    
                    rotateLeft(parent);
                //Right-Left
                } else if (sibling->left != nullptr  && sibling->left->color == COLOR_RED) {
                    sibling->left->color = parent->color;

                    rotateRight(sibling);
                    rotateLeft(parent);
                }
            } else {
                //Left-Left case
                if (sibling->left != nullptr && sibling->left->color == COLOR_RED) {
                    sibling->left->color = sibling->color;
                    sibling->color = parent->color;

                    rotateRight(parent);
                } else if (sibling->right != nullptr && sibling->right->color == COLOR_RED) {
                    //Left-Right case
                    sibling->right->color = parent->color;

                    rotateLeft(sibling);
                    rotateRight(parent);
                }
            }
            parent->color = COLOR_BLACK;
        }
    }
}



void RedBlackTree::RemoveHelper(RBTNode* D, RBTNode* R) {
    if (R == nullptr) {
        // if the replacement is null and the node is black, fix double black
        if (D->color == COLOR_BLACK) {
            FixDoubleBlack(D);
        }
        return; 
    }
    // if either the node or its replacement is red, make the replacement black

    if (D->color == COLOR_RED || R->color == COLOR_RED) {
        R->color = COLOR_BLACK;
        return;
    }

    if (D->color == COLOR_BLACK && R->color == COLOR_BLACK) {
        FixDoubleBlack(R);  
    }
}


void RedBlackTree::Remove(int data) {
    RBTNode* nodeToDelete = Get(data);
    RBTNode* replacement = GetReplacement(nodeToDelete);

    bool uvBlack = ((replacement == nullptr || replacement->color == COLOR_BLACK) &&
                    (nodeToDelete->color == COLOR_BLACK));
    RBTNode* parent = nodeToDelete->parent;

    if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
        // Case 1: `nodeToDelete` is a leaf
        if (nodeToDelete == root) {
            root = nullptr;
        } else {
            if (uvBlack) {
                FixDoubleBlack(nodeToDelete);
            } else {
                RBTNode* sibling = getSibling(nodeToDelete);
                if (sibling != nullptr) sibling->color = COLOR_RED;
            }

            if (nodeToDelete == parent->left) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete nodeToDelete;
    } else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
        // Case 2: `nodeToDelete` has one child
        RBTNode* child = nodeToDelete->left != nullptr ? nodeToDelete->left : nodeToDelete->right;

        if (nodeToDelete == root) {
            root = child;
            root->color = COLOR_BLACK;
            root->parent = nullptr;
        } else {
            if (nodeToDelete == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            child->parent = parent;

            if (uvBlack) {
                FixDoubleBlack(child);
            } else {
                child->color = COLOR_BLACK;
            }
        }
        delete nodeToDelete;
    } else {
        // Case 3: `nodeToDelete` has two children
        RBTNode* successor = GetReplacement(nodeToDelete);
        swapValues(successor, nodeToDelete); 
        Remove(successor->data);            
    }
}



void RedBlackTree::swapValues(RBTNode* u, RBTNode* v) {
    // swap the data of two nodes
    int temp = u->data;
    u->data = v->data;
    v->data = temp;
}