#ifndef BPLUSTREE_H__
#define BPLUSTREE_H__

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <cmath>
#include "Node.h"



// using namespace std;


class BPlusTree {
private:
    Node* root; 



public:

    BPlusTree();


    ~BPlusTree();
    void DestroyRecursive(Node* node); 

    void setRootNode(Node* node);
    Node* getRootNode();

    int IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(Node* curr_node, int given_key);


    // Find by Key 
    Node* Find(int v);

    // Find by Range Scan 
    std::vector <Node *> FindRange(int lower_bound, int upper_bound);

    // Insert
    bool Insert(int key, std::string value);
    void InsertInLeaf(Node* Leaf, int key, std::string value);
    void InsertInParent(Node* N, int KPrime, Node* NPrime);
    Node* getParentNode(Node* N);
    void InsertInInternalNode(Node* Parent, Node* N, int KeyPrime, Node* NPrime);

    // Delete 
    bool Delete(int k);
    bool delete_entry(Node* N, int K, Node* pointer);
    bool getPrevOrNextChildFromParentOfN(Node* P, Node* N, Node* &NPrime);
    int findIndexOfKPrime(Node* P, Node* N, Node* NPrime, bool retrieved_prev_child);
    void swap_pointers(Node* &N, Node* &NPrime);
    void appendKPrimeAndNToNPrime(Node* &NPrime, int KPrime, Node* N);
    void appendNToNPrime(Node* &NPrime, Node* N);





};

#endif // BPLUSTREE_H__

