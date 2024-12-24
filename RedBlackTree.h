#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define DOUBLE_BLACK 2
#define COLOR_RED 0
#define COLOR_BLACK 1

#include <string>


struct RBTNode {
    int data;
    int color; 
    RBTNode* parent;
    RBTNode* left;
    RBTNode* right;

    RBTNode() : data(0), color(0), parent(nullptr), left(nullptr), right(nullptr) {}

    bool IsNullNode() const; //{

    bool isempty() const;

    //}
};

class RedBlackTree {
private:

    std::string ToInfixString(RBTNode* node) const;
    std::string ToPrefixString(RBTNode* node) const;
    std::string ToPostfixString(RBTNode* node) const;
    RBTNode* InOrderSuccessor(RBTNode* node);




    RBTNode* findNode(RBTNode* node, int data);
    void balanceAfterRemove(RBTNode* node);
    void rotateLeft(RBTNode* node);
    void rotateRight(RBTNode* node);
    void Balance(RBTNode* node);
    void replaceNode(RBTNode* node, RBTNode* child);
    RBTNode* getMinNode(RBTNode* node);
    void balanceAfterRemove(RBTNode* node, RBTNode* parent);

    void removeNode(RBTNode* node);
    void deleteTree(RBTNode* node);
    RBTNode* Clone(RBTNode* node);
    RBTNode* balanceAfterRemoveHelper(RBTNode* node);

    int countNodes(RBTNode* node) const;
    RBTNode* FindNode(RBTNode* node, int data);

    RBTNode* GetReplacement(RBTNode* node);
    //RBTNode* GetReplacement(RBTNode* node);
    void RemoveHelper(RBTNode* replacement, RBTNode* node);
    void FixDoubleBlack(RBTNode* node);

public:

    RBTNode* root;
    RBTNode* Get (int data);  
    size_t numItems; 
    void Insert(int node_data);
    bool Contains(int node_data) ;
    int GetMin() ;
    int GetMax() ;
    int Size() ;
    RedBlackTree();
    RedBlackTree(const RedBlackTree& input);
    ~RedBlackTree();
    bool isEmpty ();
    void DeleteNodes(RBTNode* node);

   


    void swapValues(RBTNode* u, RBTNode* v);
    void Remove(int value);
    void BSTInsert(RBTNode* newNode);

    RBTNode* getGrandparent(RBTNode* node);
    RBTNode* getSibling(RBTNode* node);
    RBTNode* getUncle(RBTNode* node);


    bool replaceChild(RBTNode* parent, RBTNode* currentChild, RBTNode* newChild);
    bool setChild(RBTNode* parent, std::string whichChild, RBTNode* child);
    std::string ToInfixString() const { return ToInfixString(root); };
    std::string ToPrefixString() const { return ToPrefixString(root); };
    std::string ToPostfixString() const { return ToPostfixString(root); };
};

#endif //REDBLACKTREE_H