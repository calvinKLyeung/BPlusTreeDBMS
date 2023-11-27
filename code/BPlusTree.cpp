#include "BPlusTree.h"

BPlusTree::BPlusTree()
{

}


BPlusTree::~BPlusTree()
{

}

void BPlusTree::setRoot(Node* node)
{
    // set the given node as the root of BPluesTree
    this->root = node;
}

Node* BPlusTree::getRoot()
{
    // get the root node store in the BPlusTree 
    return this->root;
}



Node* BPlusTree::find(int v)
{
    /* Assumes no duplicate keys, and returns pointer to the record with
    * search key value v if such a record exists, and null otherwise */
    Node* C = this->root;

    // while loop to traverse the B+Tree 
    while (C->IsLeaf() != true)
    {
        std::cout << "??????????????????????????" << std::endl;
        std::cout << "v is now: " << v << std::endl;
        int i = this->IndexOfKiSmallestKeyGeqV(C, v);
        std::cout << "IndexOfKiSmallestKeyGeqV: " << i << std::endl;
        // unsigned int i = C->getArrayPointer()[0]; // get first num in keys arr

        if (i == -1) // -1 == there is no such number i where K_{i} is smallest number such that v ≤ C.Ki
        {
            unsigned int m = C->getSlots();  // m == index of last non-null pointer in the node, slot IS ALREADY the last pointer as Exclusive End indexing [0, 4)
            C = C->accessChildren()[m]; // Pointer at index m
        }
        else if (v == C->getKey((unsigned int)i))
        {
            C = C->accessChildren()[i+1];
        }
        else // v < C.Ki  v strightly smaller than K_{i}
        {
            C = C->accessChildren()[i];
        }
    }
    // iterate through each key in the Leaf Node 
    for (unsigned int i=0; i<C->getSlots(); ++i)
    {
        if (C->accessKeys()[i] == v)
        {
            return C;

            // return C->accessChildren()[i]; // return Pi, a pointer that point to the Actual Disk?????
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
    std::cout << "Where are We? : " << curr_node->getData() << std::endl;
    std::cout << "What is SLots size: " << curr_node->getSlots() << std::endl;
    for (unsigned int i = 0; i < curr_node->getSlots(); ++i)
    {
        if (v <= curr_node->accessKeys()[i])
        {   
            std::cout << "V is :" << v << std::endl;
            std::cout << "V <= THE NUM is : " << curr_node->accessKeys()[i] << std::endl;
            return i; 
        }
    }
    return -1; 
}

std::vector <Node *> BPlusTree::findRange(int lb, int ub) // lb == lower bound, ub == upper bound 
{
    std::vector <Node *> retSet; 
    Node* C = this->root; 
    while (C->IsLeaf() != true)
    {
        int i = this->IndexOfKiSmallestKeyGeqV(C, lb);
        if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
        {
            unsigned int m = C->getSlots();
            C = C->accessChildren()[m];
        }
        else if (lb == C->getKey((unsigned int)i))
        {
            C = C->accessChildren()[i+1];
        }
        else
        {
            C = C->accessChildren()[i]; // where lb < C.Ki
        }
    }

    // if i != -1 == key exists or within range of current leaf node 
    int i; // = this->IndexOfKiSmallestKeyGeqV(C, lb);  
    // else, walk right to valid leaf node 
    while(C != NULL && -1 == (i = this->IndexOfKiSmallestKeyGeqV(C, lb)))
    {
        C = C->getNext(); // access the next sibling on the right
    }

    int j; // = this->test(C, ub);
    while(C != NULL && -1 == (j = IndexOfKiSmallestKeyGeqV(C, ub))) //this->test(C, ub)))
    {
        retSet.push_back(C);
        C = C->getNext();
    }
    retSet.push_back(C); 

    return retSet;
}



// int BPlusTree::test(Node* curr_node, int v)
// {

//     for (unsigned int i = 0; i < curr_node->getSlots(); ++i)
//     {
//         if (v <= curr_node->accessKeys()[i])
//         {   
//             return i; 
//         }
//     }
//     return -1; 
// }



// function findRange(lb, ub)
// /* Returns all records with search key value V such that lb ≤ V ≤ ub. */
//     Set resultSet = {};
//     Set C = root node
//     while (C is not a leaf node) begin
//         Let i = smallest number such that lb ≤ C.Ki
//         if there is no such number i then begin
//             Let Pm = last non-null pointer in the node
//             Set C = C.Pm
//         end
//         else if (lb = C.Ki) then Set C = C.Pi+1
//         else Set C = C.Pi /* lb < C.Ki */
//     end
//     /* C is a leaf node */
//     Let i be the least value such that Ki ≥ lb
//     if there is no such i
//         then Set i = 1 + number of keys in C; /* To force move to next leaf ?????????????????????*/
//     Set done = false;
//     while (not done) begin
//         Let n = number of keys in C.
//         if ( i ≤ n and C.Ki ≤ ub) then begin
//             Add C.Pi to resultSet
//             Set i = i + 1
//         end
//         else if (i ≤ n and C.Ki > ub)
//             then Set done = true;
//         else if (i > n and C.Pn+1 is not null)
//             then Set C = C.Pn+1, and i = 1 /* Move to next leaf */
//         else Set done = true; /* No more leaves to the right */
//     end
//     return resultSet;

bool BPlusTree::insert(int key)
{
    bool ret = false; 
    if (this->getRoot() == NULL)
    {
        int arr[] = {key};
        Node* new_root_node = new Node("root", 0, true, 1, arr); // leaf == true 
        this->setRoot(new_root_node);
        ret = true; 
    }
    else
    {
        // walk to the leaf node L that should contain key value K
        Node* L = this->root; 
        while (L->IsLeaf() != true)
        {
            int i = this->IndexOfKiSmallestKeyGeqV(L, key);
            if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
            {
                unsigned int m = L->getSlots();
                L = L->accessChildren()[m];
            }
            else if (key == L->getKey((unsigned int)i))
            {
                L = L->accessChildren()[i+1];
            }
            else
            {
                L = L->accessChildren()[i]; // where lb < C.Ki
            }
        }

        if (L->getSlots() < ORDER_M - 1)
        {
            this->insertInLeaf(L, key);
        }
        else
        {
            // Create NEW node L′
            Node* new_root_node = new Node();
        }
    }

}





procedure insert(value K, pointer P)
    if (tree is empty) create an empty leaf node L, which is also the root
    else Find the leaf node L that should contain key value K
        if (L has less than n − 1 key values)
            then insert in leaf (L, K, P)
        else begin /* L has n − 1 key values already, split it */
            Create node L′
            Copy L.P1 …L.Kn−1 to a block of memory T that can
                hold n (pointer, key-value) pairs
            insert in leaf (T, K, P)
            Set L′
            .Pn = L.Pn; Set L.Pn = L′
            Erase L.P1 through L.Kn−1 from L
            Copy T.P1 through T.K⌈n∕2⌉ from T into L starting at L.P1
            Copy T.P⌈n∕2⌉+1 through T.Kn from T into L′ starting at L′.P1
            Let K′ be the smallest key-value in L′
            insert in parent(L, K′, L′)
        end

void BPlusTree::insertInLeaf(Node* L, int key)
{
    if (key < L->accessKeys()[0])
    {
        // move existing keys in L 1 slot to the right 
        for (unsigned int i = L->getSlots() - 1; i >= 0; --i)
        {
            L->accessKeys()[i+1] = L->accessKeys()[i];
        }
        L->accessKeys()[0] = key;
    }
    else
    {
        // Let Ki be the highest value in L that is less than or equal to K
        int i = -1; 
        for (unsigned int j = L->getSlots() - 1; j >= 1; --i)
        {
            if ((L->accessKeys()[j] <= key))
            {
                i = j;
                break; 
            }
        }
        if (i != -1) // just in case? 
        {
            L->accessKeys()[i+1] = key;  // Insert P, K into L just after L.Ki
        }
    }
}





procedure insert in leaf (node L, value K, pointer P)
    if (K < L.K1)
        then insert P, K into L just before L.P1
    else begin
        Let Ki be the highest value in L that is less than or equal to K
        Insert P, K into L just after L.Ki
    end




