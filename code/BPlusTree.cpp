#include "BPlusTree.h"

BPlusTree::BPlusTree()
{
    this->root = NULL;
}


BPlusTree::~BPlusTree()
{
    
}

void BPlusTree::setRootNode(Node* node)
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
    while (C->getLeaf() != true)
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
        else if (v == C->getKeyByIndex((unsigned int)i))
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
    while (C->getLeaf() != true)
    {
        int i = this->IndexOfKiSmallestKeyGeqV(C, lb);
        if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
        {
            unsigned int m = C->getSlots();
            C = C->accessChildren()[m];
        }
        else if (lb == C->getKeyByIndex((unsigned int)i))
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

bool BPlusTree::Insert(int key)
{
    bool ret = false; 

    // if (tree is empty) create an empty leaf node L, which is also the root
    if (this->getRootNode() == NULL)
    {
        int arr[] = {key};
        Node* new_root_node = new Node("root", 0, true, 1, arr); // leaf == true 
        this->setRootNode(new_root_node);
        ret = true; 
    }
    // else Find the leaf node L that should contain key value K
    else
    {
        // walk to the leaf node L that should contain key value K
        Node* L = this->getRootNode(); 
        while (L->getLeaf() != true)
        {
            int i = this->IndexOfKiSmallestKeyGeqV(L, key);
            if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
            {
                unsigned int m = L->getSlots();
                L = L->accessChildren()[m];
            }
            else if (key == L->getKeyByIndex((unsigned int)i))
            {
                L = L->accessChildren()[i+1];
            }
            else
            {
                L = L->accessChildren()[i]; // where lb < C.Ki
            }
        }

        // L should be at the correct Leaf Node now
        // std::cout << "what is in the leaft node? " << std::endl;
        // for (unsigned int i=0; i<L->getSlots(); ++i)
        // {
        //     std::cout << L->accessKeys()[i] << " " ; 
        // }

        // if (L has less than n − 1 key values)
        if (L->getSlots() < ORDER_M - 1)
        {
            this->InsertInLeaf(L, key);
        }

        // else begin /* L has n − 1 key values already, split it */
        else  
        {
            // Create NEW node L′
            Node* LPrime = new Node();
            Node* T = new Node(L->getData(), L->getLevel(), L->getLeaf(), L->getSlots(), L->accessKeys(), L->accessChildren()); 
            this->InsertInLeaf(T, key); // should be OVerFull after InsertInLeaf() ?


            // std::cout << "what is in the leaft node L? " << std::endl;
            // for (unsigned int i=0; i<L->getSlots(); ++i)
            // {
            //     std::cout << L->accessKeys()[i] << " " ; 
            // }
            // std::cout << std::endl; 
            // std::cout << "what is in the tmp leaft node T, should be OVERFULL now? " << std::endl;
            // for (unsigned int i=0; i<T->getSlots(); ++i)
            // {
            //     std::cout << T->accessKeys()[i] << " " ; 
            // }
            // std::cout << std::endl; 




            // Modified the following:
            // Set L′.Pn = L.Pn; Set L.Pn = L′
            // SKipped the following 
            // Erase L.P1 through L.Kn−1 from L

            // Meaningless since Our Leaf Nodes' children are NULL by set up 
            // LPrime->accessChildren()[ORDER_M] = L->accessChildren()[ORDER_M]; 
            // Not inCompatible to our own design!!!
            // L->accessChildren()[ORDER_M] = LPrime; 

            LPrime->setNext(L->getNext()); // set LPrime next pointer to point to L next 
            L->setNext(LPrime); // set next pointer of L to point to LPrime 
            LPrime->setPrev(L); // set LPrime's prev pointer to L

            // Extra step:
            // In case there exist node in LPrime->getNext()
            // then set the Prev pointer of LPrime->getNext() to point to LPrime
            if (LPrime->getNext() != NULL)
            {
                (LPrime->getNext())->setPrev(LPrime);
            }
            
   



            unsigned int mDividedByTwoCeiling = ceil((ORDER_M - 1) / 2.0); // through T.K⌈n∕2⌉

            // Copy Valid keys from 1st half of T to L 
            L->setSlots(mDividedByTwoCeiling);
            for (unsigned int i = 0; i < L->getSlots(); ++i)
            {   
                L->accessKeys()[i] = T->accessKeys()[i]; 
            }


            // std::cout << "what are the Valid Keys from T in the leaft node L? " << std::endl;
            // for (unsigned int i=0; i<L->getSlots(); ++i)
            // {
            //     std::cout << L->accessKeys()[i] << " " ; 
            // }
            // std::cout << std::endl; 



            // Copy Valid keys from 2nd half of T to LPRIME 
            LPrime->setSlots(ORDER_M - mDividedByTwoCeiling); // update slots to T.P⌈n∕2⌉+1 onward
            for (unsigned int i = 0; i < LPrime->getSlots(); ++i) //ceil(ORDER_M / 2.0); i < ORDER_M; ++i)
            {
                LPrime->accessKeys()[i] = T->accessKeys()[i + mDividedByTwoCeiling];
            }





            // std::cout << "what are the Valid Keys from T in the leaft node LPrime? " << std::endl;
            // for (unsigned int i=0; i<LPrime->getSlots(); ++i)
            // {
            //     std::cout << LPrime->accessKeys()[i] << " " ; 
            // }
            // std::cout << std::endl; 




            int KPrime = LPrime->accessKeys()[0]; // KPrime == the smallest key-value in L′

            // std::cout << "What is KPrime to be promoted? " << KPrime << std::endl; 

            this->InsertInParent(L, KPrime, LPrime);

            delete T; 
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
//             Set L′.Pn = L.Pn; Set L.Pn = L′
//             Erase L.P1 through L.Kn−1 from L
//             Copy T.P1 through T.K⌈n∕2⌉ from T into L starting at L.P1
//             Copy T.P⌈n∕2⌉+1 through T.Kn from T into L′ starting at L′.P1
//             Let K′ be the smallest key-value in L′
//             insert in parent(L, K′, L′)
//         end


// TESTED, kind of ?????????
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



// NOT TESTED YET!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
void BPlusTree::InsertInParent(Node* N, int KPrime, Node* NPrime)
{
    if (this->getRootNode() == N)
    {

        int arr[] = {KPrime}; 
        Node* R = new Node("rootR", 0, false, 1, arr);


        R->accessChildren()[0] = N;             // Left pointer 
        R->accessChildren()[1] = NPrime;        // Mid1 pointer 
        
        this->setRootNode(R);

        // std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; 

        return; 
    }
    Node* P = this->getParentNode(N); // Set Node* P to the Parent Node of N 


    // std::cout << std::endl;
    // std::cout << "P at the moment should be the Root node?" << std::endl;
    // for (unsigned int i=0; i < P->getSlots(); ++i)
	// {
	// 	std::cout << P->accessKeys()[i] << " " ;
	// }
	// std::cout << std::endl;
    // std::cout << std::endl;



    if (P != NULL)
    {
        // if P still have space for key-value and child pointer 
        if (P->getSlots() < ORDER_M - 1)
        {
            // then insert (K′, N′) in P just after N
            InsertInInternalNode(P, N, KPrime, NPrime);
        }
        else // Split P and promote!!!
        {
            Node* T = new Node(P->getData(), P->getLevel(), P->getLeaf(), P->getSlots(), P->accessKeys(), P->accessChildren()); 
            InsertInInternalNode(T, N, KPrime, NPrime); // Should be OVERFULL after this line 


            // std::cout << "What is in P during SPLIT P case?" << std::endl;
            // for (unsigned int i=0; i<P->getSlots(); ++i)
            // {
            //     std::cout << P->accessKeys()[i] << " "; 
            // }
            // std::cout << std::endl; 

            // std::cout << "What is in T during SPLIT P case, after copying from P and inserting KPrime, NPrime?" << std::endl;
            // for (unsigned int i=0; i<T->getSlots(); ++i)
            // {
            //     std::cout << T->accessKeys()[i] << " "; 
            // }
            // std::cout << std::endl; 




            unsigned int mPlusOneDividedByTwoCeiling = ceil(ORDER_M / 2.0);

            // std::cout << "ORDER_M + 1 / 2.0 " << ORDER_M + 1 / 2.0 << std::endl;
            // std::cout << "What is ORDER_M ? " << ORDER_M << std::endl;
            // std::cout << "What is the mPlusOneDividedByTwoCeiling? " << mPlusOneDividedByTwoCeiling << std::endl;

            // Erase all entries from P; Create node P′

            // May not necessary since we use getSlots() to track the valid keys and getSlots() + 1 to track valid children
            // P->clear();
            // P->setLeaf(false);


            Node* PPrime = new Node();
            PPrime->setLeaf(P->getLeaf()); // set PPrime to have the SAME leaf status as P 


            // Copy Valid keys AND children from 1st half of T to P
            P->setSlots(mPlusOneDividedByTwoCeiling - 1);
            // copying keys 
            for (unsigned int i = 0; i < P->getSlots(); ++i)
            {   
                P->accessKeys()[i] = T->accessKeys()[i]; 
            }
            // copying children 
            for (unsigned int i = 0; i < P->getSlots() + 1; ++i)
            {   
                P->accessChildren()[i] = T->accessChildren()[i]; 
            }

            // Reset out of bound children to NULL???????????????????????
            for (unsigned int i = P->getSlots() + 1; i <= ORDER_M + 1; ++i)
            {   
                P->accessChildren()[i] = NULL; 
            }




            // std::cout << std::endl;
            // std::cout << "What is in P's Keys after copying from tmp T? " << std::endl;
            // for (unsigned int i=0; i<P->getSlots(); ++i)
            // {
            //     std::cout << P->accessKeys()[i] << " " ;
            // } 
            // std::cout << std::endl;

            // std::cout << "What is in P's Children after copying from tmp T? " << std::endl;
            // for (unsigned int i=0; i<P->getSlots()+1; ++i)
            // {
            //     std::cout << P->accessChildren()[i] << " " ;
            // } 
            // std::cout << std::endl;








            // Copy Valid keys  AND children from 2nd half of T to PPRIME 
            PPrime->setSlots(ORDER_M - mPlusOneDividedByTwoCeiling); // ????????????????????????
            // copying keys
            for (unsigned int i = 0; i < PPrime->getSlots(); ++i) //??????????????
            {
                PPrime->accessKeys()[i] = T->accessKeys()[i + mPlusOneDividedByTwoCeiling];
            }
            // copying children 
            for (unsigned int i = 0; i < PPrime->getSlots() + 1; ++i) //???????????
            {
                PPrime->accessChildren()[i] = T->accessChildren()[i + mPlusOneDividedByTwoCeiling]; //??????????????
            }
            // Reset out of bound children to NULL 
            for (unsigned int i = PPrime->getSlots() + 1; i <= ORDER_M + 1; ++i) //???????????
            {
                PPrime->accessChildren()[i] = NULL;
            }




            // std::cout << std::endl;
            // std::cout << "What is in PPrime's Keys after copying from tmp T? " << std::endl;
            // for (unsigned int i=0; i<PPrime->getSlots(); ++i)
            // {
            //     std::cout << PPrime->accessKeys()[i] << " " ;
            // } 
            // std::cout << std::endl;

            // std::cout << "What is in PPrime's Children after copying from tmp T? " << std::endl;
            // for (unsigned int i=0; i<PPrime->getSlots()+1; ++i)
            // {
            //     std::cout << PPrime->accessChildren()[i] << " " ;
            // } 
            // std::cout << std::endl;


            // Let K′′ = T.K⌈(n+1)∕2⌉
            int KPrimePrime = T->accessKeys()[mPlusOneDividedByTwoCeiling - 1];

            // std::cout << std::endl;
            // std::cout << "What is the index to get KPrimePrime value? " << mPlusOneDividedByTwoCeiling - 1 << std::endl;
            // std::cout << "What is KPrimePrime now? " << KPrimePrime << std::endl;
            // int KPrime = LPrime->accessKeys()[0]; // KPrime == the smallest key-value in L′
            
            // std::cout << std::endl;
            // std::cout << "What is the Root before calling InsertInParent() recirsively? "<< std::endl;
            // for (unsigned int i=0; i<this->getRootNode()->getSlots(); ++i)
            // {
            //     std::cout << this->getRootNode()->accessKeys()[i] << " ";
            // }
            // std::cout << std::endl;

            Node* rootnode = this->getRootNode();
            // std::cout << "Is Node P the same as Root node? "<< std::endl;
            // std::cout << P << " should have the same address as " << this->getRootNode() << std::endl;



            this->InsertInParent(P, KPrimePrime, PPrime);
            delete T; 
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

// Briefly TESTED 
Node* BPlusTree::getParentNode(Node* N)
{
    Node* C = this->getRootNode(); // C start from Root node of the BPlusTree 

    // use 1st key in node N as guidance to traverse
    int key = N->accessKeys()[0]; 

    bool found = false; 

    while(C->getLeaf() != true && found == false)
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
        else if (key == C->getKeyByIndex((unsigned int) i))
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





// then insert (K′, N′) in P just after N
// INSERT given KPrime key-value and NPrime Node to the Parent node P right after where N is !!!!!!!!!!!!!!!!!!!!!!!!!!!!
void BPlusTree::InsertInInternalNode(Node* P, Node* N, int KPrime, Node* NPrime) // P == Parent of N, KPrime == the smallest key-value in N′
{

    int key = N->accessKeys()[0]; // get key of N to find our way to insert KPrime, NPrime after N inside P
    int i = this->IndexOfKiSmallestKeyGeqV(P, key);

    // std::cout << "The index i should be ZERO here: " << i << std:: endl; 

    int index_for_KPrime = -1; 
    int index_for_NPrime = -1;

    // then insert (K′, N′) in P just after N
    if (i == -1)
    {
        unsigned int m = P->getSlots();

        // P->accessChildren()[m] == N
        if (N == P->accessChildren()[m])
        {
            index_for_KPrime = m;
            index_for_NPrime = index_for_KPrime + 1;
        }
    }
    else if (key == P->getKeyByIndex((unsigned int) i))
    {
        // P->accessChildren()[i+1] == N
        if (N == P->accessChildren()[i+1])
        {
            index_for_KPrime = i + 1;
            index_for_NPrime = index_for_KPrime + 1;
        }
    }
    else
    {
        // P->accessChildren()[i] == N
        if (N == P->accessChildren()[i])
        {
            index_for_KPrime = i;
            index_for_NPrime = index_for_KPrime + 1;
        }
    }

    // move keys down by 1 slot to the right 
    for (int i = P->getSlots()-1;  i >=index_for_KPrime; --i)
    {
        P->accessKeys()[i+1] = P->accessKeys()[i];
    }

    // move Children down by 1 slot to the right 
    for (int i = P->getSlots();  i >= index_for_NPrime; --i)
    {
        P->accessChildren()[i+1] = P->accessChildren()[i];
    }



    P->setSlots(P->getSlots() + 1);
    P->accessKeys()[index_for_KPrime] = KPrime;
    P->accessChildren()[index_for_NPrime] = NPrime;


}


bool BPlusTree::Delete(int k)
{
    bool ret = false; 
    // find the leaf node L that contains (K, P)
    Node* found_in_node = this->find(k);
    if (found_in_node != NULL)
    {
        // delete entry(L, K, P)
        this->delete_entry(found_in_node, k, NULL);
        ret = true; 
    }

    return ret;
}



// procedure delete(value K, pointer P)
//     find the leaf node L that contains (K, P)
//     delete entry(L, K, P)


bool BPlusTree::delete_entry(Node* N, int K, Node* pointer)
{   


    // Removing the element 

    // delete key-pointer pair (K, P) from N
    unsigned int index_of_K = N->getIndexByKey(K);
    for (unsigned int i = index_of_K; i < N->getSlots(); ++i)
    {   
        N->accessKeys()[i] = N->accessKeys()[i+1]; 
    }


    // if N != Leaf, also remove the child pointer 
    if (N->getLeaf() != true && pointer != NULL)
    {
    

        int index_of_pointer = N->getIndexByChildPointer(pointer);
        for (unsigned int i = index_of_pointer; i < N->getSlots() + 1; ++i)
        {   
            N->accessChildren()[i] = N->accessChildren()[i+1]; 
        }


        delete pointer;
    }

    // update slots aget deleting key 
    N->setSlots(N->getSlots() - 1);




    // ROOT case 
    // if (N is root node AND N has 0 Keys left AND N has 0 Children left )
    if (N == this->getRootNode() && N->getNumOfChildren() == 0 && N->getSlots() == 0)
    {
        this->setRootNode(nullptr); 
        delete N; 
    }


    // else if (N is the root AND N has only one remaining child (which also imples 1 Child pointer left by B+Tree invariant ))
    // N->getNumOfChildren() == 1 SAME AS N->getSlots() == 0 by the B+Tree Invariant 
    else if (N == this->getRootNode() && N->getNumOfChildren() == 1 && N->getSlots() == 0)
    {
        Node* child_of_N = N->getTheRemainingChild();
        this->setRootNode(child_of_N); 
        delete N; 
    }


    // NON ROOT case 

    // else if (N has too few values/pointers AND N is Not the Root Node) then begin
    // if N is the Root Node, then do nothing
    // becuase the Root Node is NOT bounded to have at least ⌈(ORDER_M - 1) / 2⌉ Keys
    else if (N->hasTooFewValuesOrPointersRemain() == true && N != this->getRootNode())
    {

        Node* Parent = this->getParentNode(N); 



        // std::cout << "Parent should be [24, 30]" << std::endl;
        // for (unsigned int i=0 ; i<Parent->getSlots(); ++i)
        // {
        //     std::cout << Parent->accessKeys()[i] << " ";
        // }
        // std::cout << std::endl;




        Node* NPrime = NULL; // to be passed by reference!! 
        // Check whether N is Left OR Mid1 child of P 
        // Let N′ be the previous or next child of parent(N) 
        bool prev_true_next_false = this->getPrevOrNextChildOfParentOfN(Parent, N, NPrime); // NPrime is Pass by Reference!!!!!
        


        // prev_true_next_false == true when retrieved the prev child 
        // prev_true_next_false == false when retrieved the next child 

        // Let K′ be the value between pointers N and N′ in parent(N)
        int index_for_KPrime = this->findIndexOfKPrime(Parent, N, NPrime, prev_true_next_false);
        int KPrime = Parent->accessKeys()[index_for_KPrime]; 




        std::cout << "Or in Delete(14) iteration Parent should be [15, 17]" << std::endl; 
        std::cout << "Or in Delete(14) iteration Parent should be [13]" << std::endl; 
        for (unsigned int i=0; i < Parent->getSlots(); ++i)
        {
            std::cout << Parent->accessKeys()[i]<< " ";
        }
        std::cout << std::endl;

        std::cout << "Or in Delete(14) iteration N should be [13]" << std::endl; 
        std::cout << "Or in Delete(14) iteration N should be [17]" << std::endl; 
        for (unsigned int i=0; i < N->getSlots(); ++i)
        {
            std::cout << N->accessKeys()[i]<< " ";
        }
        std::cout << std::endl;

        std::cout << "Or in Delete(14) iteration NPrime should be [15, 16]" << std::endl;
        std::cout << "Or in Delete(14) iteration NPrime should be [5, 7, 9, 11]" << std::endl;
        for (unsigned int i=0; i < NPrime->getSlots(); ++i)
        {
            std::cout << NPrime->accessKeys()[i]<< " ";
        }
        std::cout << std::endl;
                
        std::cout << "Or in Delete(14) iteration KPrime should be 15: " << std::endl;
        std::cout << "Or in Delete(14) iteration KPrime should be 13: " << std::endl;
        std::cout << KPrime << std::endl; 







        // if (entries in N and N′ can fit in a single node)
        // if ((N->getSlots() + NPrime->getSlots()) <= ORDER_M - 1)
        // if stealing 1 elem from sibling makes the sibling NPrime become having TOO FEW values
        // then merge
        if ((NPrime->getSlots() - 1) < ceil((ORDER_M - 1) / 2.0))
        {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~ Merge/Combine case ~~~~~~~~~~~~~~~~~~~~~~~~~~
            // then begin /* Coalesce nodes */


            // if (N is a predecessor of N′) then swap variables(N, N′)
            if (Parent->getIndexByChildPointer(N) < Parent->getIndexByChildPointer(NPrime))
            {
                // The procedure swap_variables(N, N′) merely swaps the values of 
                // the (pointer) variables N and N′ 
                // this swap has no effect on the tree itself
                this->swap_variables(N, NPrime);

            }


            std::cout << "We want N to have [3, 4], and NPrime to have [2]" << std::endl;
            std::cout << "OR in 2nd Iteration want N to have [9, 11], and NPrime to have [5]" << std::endl;
            std::cout << "OR in Delete(14) iteration we want N to have [15, 16], and NPrime to have [13]" << std::endl;
            std::cout << "" <<  std::endl;
            std::cout << "Insdie N: " << std::endl;
            for (unsigned int i=0; i<N->getSlots(); ++i)
            {
                std::cout << N->accessKeys()[i] << " "; 
            }
            std::cout << std::endl; 
            std::cout << "Insdie NPrime : " << std::endl;
            for (unsigned int i=0; i<NPrime->getSlots(); ++i)
            {
                std::cout << NPrime->accessKeys()[i] << " "; 
            }
            std::cout << std::endl; 




            // if (N is not a leaf)
            if (N->getLeaf() != true)
            {
                this->appendKPrimeAndNToNPrime(NPrime, KPrime, N);

                std::cout << "In 2nd Iteration" << std::endl;
                std::cout << "NPrime should have [5, 7, 9, 11]" << std::endl;
                for (unsigned int i=0; i<NPrime->getSlots(); ++i)
                {
                    std::cout << NPrime->accessKeys()[i] << " "; 
                }
                std::cout << std::endl; 
            
            }
            // else N is a Leaf 
            else
            {
                this->appendNToNPrime(NPrime, N);


                // Update Next and Prev Pointers of NPimre, (N is to be Deleted, so does not matter)
                NPrime->setNext(N->getNext());
                if (NPrime->getNext() != NULL)
                {
                    NPrime->getNext()->setPrev(NPrime);
                }
            }

  



            std::cout << "We should have NPrime with all the Keys from NPrime and N" << std::endl;
            std::cout << "where NPrime Keys is NOW [2, 3, 4]" << std::endl;
            std::cout << "Or in 2 nd Iteration where NPrime Keys is NOW [5, 7, 9, 11]" << std::endl;
            std::cout << "Or in Delete(14) interation where NPrime Keys is NOW [13, 15, 16]" << std::endl;
            std::cout << "" << std::endl;
           
            for (unsigned int i=0; i<NPrime->getSlots(); ++i)
            {
                std::cout <<NPrime->accessKeys()[i] << " "; 
            }
            std::cout << std::endl; 
            std::cout << std::endl; 





            delete_entry(Parent, KPrime, N);


        }


        // else when (NPrime->getSlots() - 1)  >=  ceil((ORDER_M - 1) / 2.0)
        // begin /* Redistribution: borrow an entry from N′ */
        // steal key-value from the sibling node 

        // NPrime still have Valid # of Keys after being stolen Keys - 1 
        else
        {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~ Stealing From the Sibiling ~~~~~~~~~~~~~~~~~~~~~~~~~~

            // if (N′ is a predecessor of N) then begin  [NPrime] -> [N]
            // if (NPrime->getNext() == N && N->getPrev() == NPrime) NO!!!!!!!! NOT work for internal node!!!!!!!

            // if index of child in Parent node of NPrime is < index of child in Parent node of N
            // then NPrime is a predecessor of N ??????????????????????????
            // I think...????????????????????????????


            if (Parent->getIndexByChildPointer(NPrime) < Parent->getIndexByChildPointer(N))
            {
                // ~~~~~~~~~~~~~~ N′ is a predecessor of N ~~~~~~~~~~~~~~~~~

                // if (N is a nonleaf node) then begin
                if (N->getLeaf() != true)
                {   
                    

                    // let m be such that N′.Pm is the last child pointer in N′
                    unsigned m = NPrime->getSlots();

                    // retrieve mth child pointer and m-1th Key of NPrime for later before deleting from NPrime 
                    Node* mth_child_of_NPrime = NPrime->accessChildren()[m];
                    int mth_minus_one_key_of_NPrime = NPrime->accessKeys()[m-1];

                    // remove (N′.Km−1, N′.Pm) from N′
                    // And update the Slots count 
                    NPrime->accessKeys()[m-1] = 0;
                    NPrime->accessChildren()[m] = NULL;
                    NPrime->setSlots(NPrime->getSlots() - 1);


                    // insert (N′.Pm, K′) as the first pointer and value in N,
                    // by shifting other pointers and values right

                    // shifting Keys to the right by 1 slot 
                    for (int i = N->getSlots() - 1; i >= 0; --i)
                    {
                        N->accessKeys()[i + 1] = N->accessKeys()[i];  
                    }
                    // insert K′ as the first Key 
                    N->accessKeys()[0] = KPrime;

                    // shifting Children to the right by 1 slot 
                    for (int i = N->getSlots(); i >= 0; --i)
                    {
                        N->accessChildren()[i + 1] = N->accessChildren()[i];  
                    }
                    // insert N′.Pm as the first child 
                    N->accessChildren()[0] = mth_child_of_NPrime;

                    // SLot increment by 1 
                    N->setSlots(N->getSlots() + 1);

                    // replace K′ in parent(N) by N′.Km−1
                    int index_of_KPrime = Parent->getIndexByKey(KPrime);
                    Parent->accessKeys()[index_of_KPrime] = mth_minus_one_key_of_NPrime; 

                }


                // else: N is a Leaf Node 
                else
                {



                    // let m be such that (N′.Pm, N′.Km) is the last pointer/value pair in N′
                    // Since we don't use key-point pair at Leaf but to store data in Leaf directly 
                    // We set m to index of last Key in NPrime 
                    int m = NPrime->getSlots() - 1;
                    int mth_key_of_NPrime = NPrime->accessKeys()[m];

                    // remove (N′.Pm, N′.Km) from N′
                    // skipped N′.Pm because our B+Tree don't have it 
                    NPrime->accessKeys()[m] = 0;
                    // for (unsigned int i = m; i<NPrime->getSlots(); ++i)
                    // {
                    //     NPrime->accessKeys()[i] = NPrime->accessKeys()[i+1];
                    // }
                    NPrime->setSlots(NPrime->getSlots() - 1);

                    // insert (N′.Pm, N′.Km) as the first pointer and value in N,
                    // by shifting other pointers and values right
                    for (int i = N->getSlots() - 1; i >= 0; --i)
                    {
                        N->accessKeys()[i + 1] = N->accessKeys()[i];  
                    }
                    // slot in to index 0 as the 1 st elem 
                    N->accessKeys()[0] = mth_key_of_NPrime;



                    // SLot increment by 1 
                    N->setSlots(N->getSlots() + 1);

                    std::cout << "What is themth_key_of_NPrime?, Is it 8? " << std::endl;
                    std::cout << mth_key_of_NPrime << std::endl;



                    // replace K′ in parent(N) by N′.Km
                    int index_of_KPrime = Parent->getIndexByKey(KPrime);
                    Parent->accessKeys()[index_of_KPrime] = mth_key_of_NPrime;
                }
            }


            // SYMMETRIC MEans? 

            // else if (N is a predecessor of N′) then begin    [N] -> [NPrime]
            // then use  symmetric case

            // else if (N->getNext() == NPrime && NPrime->getPrev() == N)???????????????????????


            // ~~~~~~~~~~~~~~~~~ SYMMETRIC ~~~~~~~~~~~~~~~~~
            else if (Parent->getIndexByChildPointer(N) < Parent->getIndexByChildPointer(NPrime))
            {

                // if (NPrime is a nonleaf node) then begin
                if (NPrime->getLeaf() != true)
                {   
                    // let m be such that N′.Pm is the 1st (by SYMMETRIC) child pointer in N
                    unsigned m = 0;// N->getSlots();

                    // retrieve mth child pointer and mth   which is the 1st (by SYMMETRIC) Key of N for later before deleting from N′
                    Node* mth_child_of_NPrime = NPrime->accessChildren()[m];
                    int mth_key_of_NPrime = NPrime->accessKeys()[m];


                    // move the Keys and Children Array to the Left by 1 slot to cover the removed slot 
                    for (unsigned int i = 0; i < NPrime->getSlots(); ++i)
                    {
                        NPrime->accessKeys()[i] = NPrime->accessKeys()[i+1];
                    }
                    for (unsigned int i = 0; i < NPrime->getSlots() + 1; ++i)
                    {
                        NPrime->accessChildren()[i] = NPrime->accessChildren()[i+1];
                    }
                    
                    // since the whole array of Keys and Children have moved to the Left by 1 Slot,
                    // Set the last elem to 0 and NULL just in case 
                    // And update the Slots count 
                    NPrime->accessKeys()[NPrime->getSlots() - 1] = 0;
                    NPrime->accessChildren()[NPrime->getSlots()] = NULL;
                    NPrime->setSlots(NPrime->getSlots() - 1);




                    // insert (N′.Pm, K′) as the Last pointer and value in N (by SYMMETRIC),
                    // by shifting other pointers and values right

                    // insert K′ as the Last Key of N(by SYMMETRIC)
                    NPrime->accessKeys()[NPrime->getSlots()] = KPrime;

                    // insert N′.Pm as the Last child of N (by SYMMETRIC)
                    NPrime->accessChildren()[NPrime->getSlots() + 1] = mth_child_of_NPrime;

                    // N and N′ share the SAME parent? ????????
                    // replace K′ in parent(N) by N′.Km−1?????????????????????????????????
                    int index_of_KPrime = Parent->getIndexByKey(KPrime);
                    Parent->accessKeys()[index_of_KPrime] = mth_key_of_NPrime; 

                }


                // else: NPrime IS a Leaf Node 
                else
                {
                    // 最尾 else case tested only 

                    

                    // std::cout << "We should be here for removing 20? " << std::endl;


                    // let m be such that (N.Pm, N.Km) is the FIRST(by SYMMETRIC) pointer/value pair in N
                    // Since we don't use key-point pair at Leaf but to store data in Leaf directly 
                    // We set m to index of last Key in N
                    int m = 0; //NPrime->getSlots() - 1;
                    /// GETTING 1st elem of NPrime, SYMMETRIC in terms of indexing, but not N and NPrime???


                    // STEAL 1st elem from NPrime to N ????!!!!!

                    int mth_key_of_NPrime = NPrime->accessKeys()[m];

                    // remove (N′.Pm, N′.Km) from N′
                    NPrime->accessKeys()[m] = 0;

                    for (unsigned int i = m; i<NPrime->getSlots(); ++i)
                    {
                        NPrime->accessKeys()[i] = NPrime->accessKeys()[i+1];
                    }
                    NPrime->setSlots(NPrime->getSlots() - 1);
                    



                    // insert (N′.Pm, N′.Km) as the LAST(by SYMMETRIC) pointer and value in N,
                    // by shifting other pointers and values right

                    N->accessKeys()[N->getSlots()] = mth_key_of_NPrime;
                    N->setSlots(N->getSlots() + 1);

                    // for (int i = N->getSlots() - 1; i >= 0; --i)
                    // {
                    //     N->accessKeys()[i + 1] = NPrime->accessKeys()[i];  
                    // }
                    // N->accessKeys()[0] = mth_key_of_NPrime;


                    // replace K′ in parent(N) by N′.Km
                    int index_of_KPrime = Parent->getIndexByKey(KPrime);
                    Parent->accessKeys()[index_of_KPrime] = NPrime->accessKeys()[m];
                }

            }

        }

    }
    return false; 
}

// procedure delete entry(node N, value K, pointer P)
//     delete (K, P) from N
//     if (N is the root AND N has only one remaining child)
//         then make the child of N the new root of the tree and delete N
//     else if (N has too few values/pointers) then begin
//         Let N′ be the previous or next child of parent(N)
//         Let K′ be the value between pointers N and N′ in parent(N)
//         if (entries in N and N′ can fit in a single node)
//             then begin /* Coalesce nodes */
//                 if (N is a predecessor of N′) then swap variables(N, N′)
//                 if (N is not a leaf)
//                     then append K′ and all pointers and values in N to N′
//                 else append all (Ki, Pi) pairs in N to N′; set N′.Pn = N.Pn
//                 delete entry(parent(N), K′, N); delete node N
//             end
//         else begin /* Redistribution: borrow an entry from N′ */
//             if (N′ is a predecessor of N) then begin
//                 if (N is a nonleaf node) then begin
//                     let m be such that N′.Pm is the last pointer in N′
//                     remove (N′.Km−1, N′.Pm) from N′
//                     insert (N′.Pm, K′) as the first pointer and value in N,
//                         by shifting other pointers and values right
//                     replace K′ in parent(N) by N′.Km−1
//                 end
//                 else begin
//                     let m be such that (N′.Pm, N′.Km) is the last pointer/value
//                         pair in N′
//                     remove (N′.Pm, N′.Km) from N′
//                     insert (N′.Pm, N′.Km) as the first pointer and value in N,
//                         by shifting other pointers and values right
//                     replace K′ in parent(N) by N′.Km
//                 end
//             end
//             else … symmetric to the then case …
//         end
//     end





bool BPlusTree::getPrevOrNextChildOfParentOfN(Node* P, Node* N, Node* &NPrime) // NPrime is Pass by Reference!!!!!
{
    bool ret;
    // if N == Last Child of P
    // NPrime = Previous Child
    if (P->accessChildren()[P->getSlots()] == N)
    {
        NPrime = P->accessChildren()[P->getSlots() - 1];
        ret = true; // true == retrieved Prev Child  
    }
    // else if N != Last Child of P
    // NPrime = Next Child 
    else
    {
        for (unsigned int i=0; i < P->getSlots();++i)
        {
            if (P->accessChildren()[i] == N)
            {
                NPrime = P->accessChildren()[i + 1];
                ret = false; // false = retrieved Next Child 
                break;
            }
        }
    }
    return ret; 
}

int BPlusTree::findIndexOfKPrime(Node* P, Node* N, Node* NPrime, bool prev_true_next_false)
{
    // Let K′ be the value between pointers N and N′ in parent(N)
    int index_of_KPrime; 
    // if prev_true_next_false == true, KPrime == same index as NPrime 
    if (prev_true_next_false == true)
    {
        int index_of_NPrime = P->getIndexByChildPointer(NPrime);
        if (index_of_NPrime != -1)
        {
            index_of_KPrime = index_of_NPrime;
        }
    }
    // else if prev_true_next_false == false, KPrime == same index as N 
    else 
    {
        int index_of_N = P->getIndexByChildPointer(N);
        if (index_of_N != -1)
        {
            index_of_KPrime = index_of_N;
        }
    }
    return index_of_KPrime; 
}

void BPlusTree::swap_variables(Node* &N, Node* &NPrime)
{
    // swap the 2 pointers 
    Node* tmp = N;
    N = NPrime; 
    NPrime = tmp;
}


void BPlusTree::appendKPrimeAndNToNPrime(Node* &NPrime, int KPrime, Node* N)
{   
    // append KPrime 
    NPrime->accessKeys()[NPrime->getSlots()] = KPrime; 


    // NPrime_slots for reference 
    // int NPrime_slots = NPrime->getSlots();
    NPrime->setSlots(NPrime->getSlots() + 1);


    // append keys from N to NPrime 
    for(unsigned int i = 0; i < N->getSlots(); ++i)
    {   
        NPrime->accessKeys()[i + NPrime->getSlots()] = N->accessKeys()[i];
    }
    // append children from N to NPrime 
    for (unsigned int i = 0; i < N->getSlots() + 1; ++i)
    {
        NPrime->accessChildren()[i + NPrime->getSlots()] = N->accessChildren()[i];
        // if the children are Leaf nodes AND the Leaf node are NOT out of the bounded index 
        if (NPrime->accessChildren()[i + NPrime->getSlots()]->getLeaf() == true && (i + NPrime->getSlots() - 1) >= 0)
        {
            // Update Next and Prev Pointers in Leaf Nodes 
            NPrime->accessChildren()[(i + NPrime->getSlots() - 1)]->setNext(NPrime->accessChildren()[i + NPrime->getSlots()]);
            NPrime->accessChildren()[i + NPrime->getSlots()]->setPrev(NPrime->accessChildren()[(i + NPrime->getSlots() - 1)]);
        }
    }
    // 1 for KPrime 
    NPrime->setSlots(N->getSlots() + NPrime->getSlots());

}

void BPlusTree::appendNToNPrime(Node* &NPrime, Node* N)
{

    // NPrime_slots for reference 
    int NPrime_slots = NPrime->getSlots();

    // append keys from N to NPrime 
    for(unsigned int i = 0; i < N->getSlots(); ++i)
    {   
        NPrime->accessKeys()[i + NPrime_slots] = N->accessKeys()[i];
    }
    NPrime->setSlots(N->getSlots() + NPrime->getSlots());
}






