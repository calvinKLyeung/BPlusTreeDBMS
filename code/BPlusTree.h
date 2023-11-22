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
    std::shared_ptr<Node> root; 


public:

    BPlusTree();
    ~BPlusTree();
    std::shared_ptr<Node> find(std::shared_ptr<Node> v);

};

#endif // BPLUSTREE_H__

