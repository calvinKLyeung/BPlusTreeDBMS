#ifndef BPLUSTREE_H__
#define BPLUSTREE_H__

#include <iostream>
#include <memory>
#include "Node.h"
#include "BPlusTree.h"

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
    Node* find(Node* v);

};

#endif // BPLUSTREE_H__

