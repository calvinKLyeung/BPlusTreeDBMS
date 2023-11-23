#ifndef BPLUSTREE_H__
#define BPLUSTREE_H__

#include <iostream>
#include <memory>
#include "Node.h"


// using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3


class BPlusTree {
private:
    Node* root; 


public:

    BPlusTree();
    ~BPlusTree();
    Node* find(int v);
    int IndexOfKiSmallestKeyGeqV(Node* curr_node, int v);

};

#endif // BPLUSTREE_H__

