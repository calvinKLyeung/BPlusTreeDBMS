#ifndef BPLUSTREE_H__
#define BPLUSTREE_H__

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <cmath>
#include "Node.h"



// using namespace std;

// #define WHITE 1
// #define GRAY 2
// #define BLACK 3


class BPlusTree {
private:
    Node* root; 



public:

    BPlusTree();
    ~BPlusTree();
    void setRoot(Node* node);
    Node* getRootNode();
    //Node** getRoot();

    Node* find(int v);
    int IndexOfKiSmallestKeyGeqV(Node* curr_node, int v);
    // int test(Node* curr_node, int v);

    std::vector <Node *> findRange(int lb, int ub);

    // insert
    bool insert_content(int key);
    void InsertInLeaf(Node* L, int key);
    void InsertInParent(Node* N, int KPrime, Node* NPrime);
    Node* getParentNode(Node* N);
    void InsertInInternalNode(Node* P, Node* N, int KPrime, Node* NPrime);

    // delete 
    bool delete_content(int k);
    bool remove_entry(Node* L, int K);




};

#endif // BPLUSTREE_H__

