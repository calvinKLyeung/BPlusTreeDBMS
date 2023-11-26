#ifndef BPLUSTREE_H__
#define BPLUSTREE_H__

#include <iostream>
#include <memory>
#include <set>
#include <vector>
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
    Node* getRoot();

    Node* find(int v);
    int IndexOfKiSmallestKeyGeqV(Node* curr_node, int v);

    int test(Node* curr_node, int v);

    std::vector <Node *> findRange(int lb, int ub);

};

#endif // BPLUSTREE_H__

