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
    void setRootNode(Node* node);
    Node* getRootNode();
    //Node** getRoot();

    Node* find(int v);
    int IndexOfKiSmallestKeyGeqV(Node* curr_node, int v);
    // int test(Node* curr_node, int v);

    std::vector <Node *> findRange(int lb, int ub);

    // insert
    bool Insert(int key);
    void InsertInLeaf(Node* L, int key);
    void InsertInParent(Node* N, int KPrime, Node* NPrime);
    Node* getParentNode(Node* N);
    void InsertInInternalNode(Node* P, Node* N, int KPrime, Node* NPrime);

    // delete 
    bool Delete(int k);
    bool delete_entry(Node* N, int K, Node* pointer);
    bool getPrevOrNextChildFromParentOfN(Node* P, Node* N, Node* &NPrime);
    int findIndexOfKPrime(Node* P, Node* N, Node* NPrime, bool retrieved_prev_child);
    void swap_variables(Node* &N, Node* &NPrime);
    void appendKPrimeAndNToNPrime(Node* &NPrime, int KPrime, Node* N);
    void appendNToNPrime(Node* &NPrime, Node* N);





};

#endif // BPLUSTREE_H__

