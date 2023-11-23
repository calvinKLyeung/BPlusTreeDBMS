#include "BPlusTree.h"

BPlusTree::BPlusTree()
{

}


BPlusTree::~BPlusTree()
{

}



Node* BPlusTree::find(int v)
{
    /* Assumes no duplicate keys, and returns pointer to the record with
    * search key value v if such a record exists, and null otherwise */
    Node* C = this->root;

    // while loop to traverse the B+Tree 
    while (C->IsLeaf() == false)
    {
        int i = this->IndexOfKiSmallestKeyGeqV(C, v);

        // unsigned int i = C->getArrayPointer()[0]; // get first num in keys arr

        if (i == -1) // there is no such number i where K_{i} is smallest number such that v ≤ C.Ki
        {
            unsigned int m = C->getSlots() + 1;  // m == index of last non-null pointer in the node
            C = &(C->accessChildren()[m]); // Pointer at index m
        }
        else if (v == C->getKey((unsigned int)i))
        {
            C = &(C->accessChildren()[i+1]);
        }
        else // v < C.Ki  v strightly smaller than K_{i}
        {
            C = &(C->accessChildren()[i]);
        }
    }
    // iterate through each key in the Leaf Node 
    for (unsigned int i=0; i<C->getSlots(); ++i)
    {
        if (C->accessKeysArray()[i] == v)
        {
            return &(C->accessChildren()[i]); // return Pi, a pointer that point to the Actual Disk?????
        }
    }
    return NULL; // Not found 
}



// /* Assumes no duplicate keys, and returns pointer to the record with
// * search key value v if such a record exists, and null otherwise */
//     Set C = root node
//     while (C is not a leaf node) begin
//         Let i = smallest number such that v ≤ C.Ki
//         if there is no such number i 
//         then begin
//             Let Pm = last non-null pointer in the node
//             Set C = C.Pm
//         end
//         else if (v = C.Ki) then Set C = C.Pi+1
//         else Set C = C.Pi /* v < C.Ki */
//     end
//     /* C is a leaf node */
//     if for some i, Ki = v
//         then return Pi
//         else return null ; /* No record with key value v exists*/


int BPlusTree::IndexOfKiSmallestKeyGeqV(Node* curr_node, int v)
{
    // return index of K_{i} which is the smallest key >= v 
    for (unsigned int i=0; i<curr_node->getSlots(); ++i)
    {
        if (v <= curr_node->accessKeysArray()[i])
        {
            return i; 
        }
    }
    return -1; 
}