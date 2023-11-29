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

Node* BPlusTree::getRootNode()
{
    // get the root node of the BPlusTree, by dereferencing the double pointer of the root 
    return this->root;
}

// Node** BPlusTree::getRoot()
// {
//     // return the root pointer of pointer of node as is 
//     return this->root; 
// }



Node* BPlusTree::find(int v)
{
    /* Assumes no duplicate keys, and returns pointer to the record with
    * search key value v if such a record exists, and null otherwise */
    Node* C = this->getRootNode();

    // while loop to traverse the B+Tree 
    while (C->isLeaf() != true)
    {
        // std::cout << "??????????????????????????" << std::endl;
        // std::cout << "v is now: " << v << std::endl;
        int i = this->IndexOfKiSmallestKeyGeqV(C, v);
        // std::cout << "IndexOfKiSmallestKeyGeqV: " << i << std::endl;
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
    // std::cout << "Where are We? : " << curr_node->getData() << std::endl;
    // std::cout << "What is SLots size: " << curr_node->getSlots() << std::endl;
    for (unsigned int i = 0; i < curr_node->getSlots(); ++i)
    {
        if (v <= curr_node->accessKeys()[i])
        {   
            // std::cout << "V is :" << v << std::endl;
            // std::cout << "V <= THE NUM is : " << curr_node->accessKeys()[i] << std::endl;
            return i; 
        }
    }
    return -1; 
}

std::vector <Node *> BPlusTree::findRange(int lb, int ub) // lb == lower bound, ub == upper bound 
{
    std::vector <Node *> retSet; 
    Node* C = this->getRootNode(); 
    while (C->isLeaf() != true)
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
    if (this->getRootNode() == NULL)
    {
        int arr[] = {key};
        Node* new_root_node = new Node("root", 0, true, 1, arr); // leaf == true 
        this->setRoot(new_root_node);
        ret = true; 
    }
    else
    {
        // walk to the leaf node L that should contain key value K
        Node* L = this->getRootNode(); 
        while (L->isLeaf() != true)
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
            this->InsertInLeaf(L, key);
        }
        else  /* L has n − 1 key values already, split it */
        {
            // Create NEW node L′
            Node* LPrime = new Node();
            Node* T = new Node(L->getData(), L->getLevel(), L->isLeaf(), L->getSlots(), L->accessKeys()); 
            this->InsertInLeaf(T, key); // should be OVerFull after InsertInLeaf() ?

            // Meaningless since Our Leaf Nodes' children are NULL by set up 
            // LPrime->accessChildren()[ORDER_M] = L->accessChildren()[ORDER_M]; 
            // Not inCompatible to our own design!!!
            // L->accessChildren()[ORDER_M] = LPrime; 

            LPrime->setNext(L->getNext()); 
            L->setNext(LPrime);


            unsigned int mDividedByTwoCeiling = ceil(ORDER_M / 2.0);
            L->setSlots(mDividedByTwoCeiling);
            // Copy Valid keys from T to L 
            for (unsigned int i = 0; i < L->getSlots(); ++i)
            {   
                L->accessKeys()[i] = T->accessKeys()[i]; 
            }

            LPrime->setSlots(ORDER_M - mDividedByTwoCeiling);
            for (unsigned int i = 0; i < LPrime->getSlots(); ++i) //ceil(ORDER_M / 2.0); i < ORDER_M; ++i)
            {
                LPrime->accessKeys()[i] = T->accessKeys()[i + mDividedByTwoCeiling];
            }

            int KPrime = LPrime->accessKeys()[0]; 
            this->InsertInParent(L, KPrime, LPrime);


        }
    }
    return ret; // NOT DONE YET WITH CHANGING RET STATUS!!!!!!!!!!!!!!!

}


// procedure insert(value K, pointer P)
//     if (tree is empty) create an empty leaf node L, which is also the root
//     else Find the leaf node L that should contain key value K
//         if (L has less than n − 1 key values)
//             then insert in leaf (L, K, P)
//         else begin /* L has n − 1 key values already, split it */
//             Create node L′
//             Copy L.P1 …L.Kn−1 to a block of memory T that can
//                 hold n (pointer, key-value) pairs
//             insert in leaf (T, K, P)
//             Set L′
//             .Pn = L.Pn; Set L.Pn = L′
//             Erase L.P1 through L.Kn−1 from L
//             Copy T.P1 through T.K⌈n∕2⌉ from T into L starting at L.P1
//             Copy T.P⌈n∕2⌉+1 through T.Kn from T into L′ starting at L′.P1
//             Let K′ be the smallest key-value in L′
//             insert in parent(L, K′, L′)
//         end


// NOT TESTED YET!!!!!!!!!!!!!!!!!!
void BPlusTree::InsertInLeaf(Node* L, int key)
{
    // std::cout << "First Key in L:" << std::endl; 
    // std::cout << L->accessKeys()[0] << std::endl; 
    if (key < L->accessKeys()[0])
    {
        
        // move existing keys in L down by 1 slot to the right 

        for (int i = L->getSlots() - 1; i >= 0; --i)
        {   
            L->accessKeys()[i+1] = L->accessKeys()[i];
        }
        L->accessKeys()[0] = key;
        L->setSlots(L->getSlots() + 1);
    }
    else
    {
        // Let Ki be the highest value in L that is less than or equal to K
        int Ki_index = -1; 
        for (int i = L->getSlots() - 1; i >= 0; --i)
        {
            if ((L->accessKeys()[i] <= key))
            {
                Ki_index = i;
                break; 
            }
        }
        if (Ki_index != -1) // just in case? 
        {
            // move values down 1 slot to the right for key to slot into [i+1]
            for (int i = L->getSlots() - 1; i >= Ki_index + 1; --i)
            {
                L->accessKeys()[i+1] = L->accessKeys()[i];
            }
            L->accessKeys()[Ki_index + 1] = key;  // Insert P, K into L just after L.Ki
            L->setSlots(L->getSlots() + 1);
        }
    }
}

// procedure insert in leaf (node L, value K, pointer P)
//     if (K < L.K1)
//         then insert P, K into L just before L.P1
//     else begin
//         Let Ki be the highest value in L that is less than or equal to K
//         Insert P, K into L just after L.Ki
//     end


void BPlusTree::InsertInParent(Node* N, int KPrime, Node* NPrime)
{
    if (this->getRootNode() == N)
    {
        int arr[] = {KPrime}; 
        Node* R = new Node("rootR", 0, false, 1, arr);
        R->accessChildren()[0] = N;             // Left pointer 
        R->accessChildren()[1] = NPrime;        // Mid1 pointer 
        this->setRoot(R);
        return; 
    }
    Node* P = this->getParentNode(N); // Set Node* P to the Parent Node of N 

    if (P != NULL)
    {
        if (P->getSlots() < ORDER_M)
        {
            // then insert (K′, N′) in P just after N

        }
        else 
        {

        }
    }

    
        
}

// procedure insert in parent(node N, value K′, node N′)
//     if (N is the root of the tree)
//         then begin
//             Create a new node R containing N, K′, N′ /* N and N′ are pointers */
//             Make R the root of the tree
//             return
//         end
//     Let P = parent (N)
//     if (P has less than n pointers)
//         then insert (K′, N′) in P just after N
//     else begin /* Split P */
//         Copy P to a block of memory T that can hold P and (K′, N′)
//         Insert (K′, N′) into T just after N
//         Erase all entries from P; Create node P′
//         Copy T.P1 …T.P⌈(n+1)∕2⌉ into P
//         Let K′′ = T.K⌈(n+1)∕2⌉
//         Copy T.P⌈(n+1)∕2⌉+1 …T.Pn+1 into P′
//         insert in parent(P, K′′, P′)
//     end

Node* BPlusTree::getParentNode(Node* N)
{
    Node* C = this->getRootNode(); // C start from Root node of the BPlusTree 

    // use 1st key in node N as guidance to traverse
    int key = N->accessKeys()[0]; 

    bool found = false; 

    while(C->isLeaf() != true && found == false)
    {

        // Base Case: 
        // if 1 of the child of C == N, C node is Parent of N
        // for (unsigned int i = 0; i < C->getSlots() + 1; ++i)
        // {
        //     if (C->accessChildren()[i] == N)
        //     {
        //         return C; 
        //     }
        // }
        
        int i = this->IndexOfKiSmallestKeyGeqV(C, key);
        // else follow the key as guidence to the next level of node 

        // Sub If cases == Base case
        if (i == -1)
        {
            unsigned int m = C->getSlots();
            if (N == C->accessChildren()[m])
            {
                found = true;  
            }
            else
            {
                C = C->accessChildren()[m]; 
            }
        }
        else if (key == C->getKey((unsigned int) i))
        {
            if (N == C->accessChildren()[i+1])
            {
                found = true;  
            }
            else
            {
                C = C->accessChildren()[i+1]; 
            }
        }
        else
        {
            if (N == C->accessChildren()[i])
            {
                found = true; 
            }
            else
            {
                C = C->accessChildren()[i]; 
            }
        }
    }

    return found == true ? C : NULL;  // if Parent Node is found, return C, else return NULL 

}


// Node* C = this->getRootNode();

//     // while loop to traverse the B+Tree 
//     while (C->isLeaf() != true)
//     {
//         std::cout << "??????????????????????????" << std::endl;
//         std::cout << "v is now: " << v << std::endl;
//         int i = this->IndexOfKiSmallestKeyGeqV(C, v);
//         std::cout << "IndexOfKiSmallestKeyGeqV: " << i << std::endl;
//         // unsigned int i = C->getArrayPointer()[0]; // get first num in keys arr

//         if (i == -1) // -1 == there is no such number i where K_{i} is smallest number such that v ≤ C.Ki
//         {
//             unsigned int m = C->getSlots();  // m == index of last non-null pointer in the node, slot IS ALREADY the last pointer as Exclusive End indexing [0, 4)
//             C = C->accessChildren()[m]; // Pointer at index m
//         }
//         else if (v == C->getKey((unsigned int) i))
//         {
//             C = C->accessChildren()[i+1];
//         }
//         else // v < C.Ki  v strightly smaller than K_{i}
//         {
//             C = C->accessChildren()[i];
//         }
//     }

void BPlusTree::InsertInInternalNode(Node* P, Node* N, int KPrime, Node* NPrime)
{
    int key = N->accessKeys()[0];
    int i = this->IndexOfKiSmallestKeyGeqV(P, key);

    // if (i == -1)
    // {
    //     unsigned int m = P->getSlots();

    //     // P->accessChildren()[m] == N


    //     if (N == C->accessChildren()[m])
    //     {
    //         C = C->accessChildren()[m]; 
    //     }
    // }
    // else if (key == P->getKey((unsigned int) i))
    // {
    //     // P->accessChildren()[i+1] == N


    //     if (N == C->accessChildren()[i+1])
    //     {
    //         C = C->accessChildren()[i+1]; 
    //     }
    // }
    // else
    // {
    //     // P->accessChildren()[i] == N


    //     if (N == C->accessChildren()[i])
    //     {}
    //         C = C->accessChildren()[i]; 
    //     }
    // }
}



