#include "BPlusTree.h"

BPlusTree::BPlusTree()
{

}


BPlusTree::~BPlusTree()
{

}



std::shared_ptr<Node> BPlusTree::find(std::shared_ptr<Node> v)
{
    /* Assumes no duplicate keys, and returns pointer to the record with
    * search key value v if such a record exists, and null otherwise */
    std::shared_ptr<Node> C = this->root;
    while (C->IsLeaf() != true)
    {
        unsigned int i = C->getArrayPointer()[0]; // get first num in keys arr
        

    }


}
/* Assumes no duplicate keys, and returns pointer to the record with
* search key value v if such a record exists, and null otherwise */
    Set C = root node
    while (C is not a leaf node) begin
        Let i = smallest number such that v ≤ C.Ki
        if there is no such number i then begin
            Let Pm = last non-null pointer in the node
            Set C = C.Pm
        end
        else if (v = C.Ki) then Set C = C.Pi+1
        else Set C = C.Pi /* v < C.Ki */
    end
    /* C is a leaf node */
    if for some i, Ki = v
        then return Pi
        else return null ; /* No record with key value v exists*/