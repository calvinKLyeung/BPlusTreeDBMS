#include "BPlusTree.h"

BPlusTree::BPlusTree()
{
    this->root = NULL;
}


BPlusTree::~BPlusTree()
{
    if (this->getRootNode() != NULL)
    {
        DestroyRecursive(this->getRootNode());
    }

}

void BPlusTree::DestroyRecursive(Node* node)
{
    if (node->getLeaf() == true)
    {
        return; 
    }

    for (unsigned int i=0; i < node->getSlots() + 1; ++i)
    {
        if (node->accessChildren()[i] != NULL)
        {
            DestroyRecursive(node->accessChildren()[i]);
            delete node->accessChildren()[i];
            node->accessChildren()[i] = NULL;
        }
    }
    // for (unsigned int i=0; i < node->getSlots() + 1; ++i)
    // {
    //     if (node->accessChildren()[i] != NULL)
    //     {
    //         delete node->accessChildren()[i];
    //         node->accessChildren()[i] = NULL;
    //     }
    // }
    delete node; 

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


Node* BPlusTree::Find(int v)
{
    /* Assumes no duplicate keys, and returns pointer to the record with
    * search key value v if such a record exists, and null otherwise */
   Node* ret = NULL;
   if (this->getRootNode() != NULL)
   {

        Node* curr_node = this->getRootNode();

        // while loop to traverse the B+Tree 
        while (curr_node != NULL && curr_node->getLeaf() != true)
        {

            int i = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(curr_node, v);

            if (i == -1) // -1 == there is no such number i where K_{i} is smallest number such that v ≤ C.Ki
            {
                unsigned int m = curr_node->getSlots();  // m == index of last non-null pointer in the node, slot IS ALREADY the last pointer as Exclusive End indexing [0, 4)
                curr_node = curr_node->accessChildren()[m]; // Pointer at index m
            }
            else if (v == curr_node->getKeyByIndex((unsigned int)i))
            {
                curr_node = curr_node->accessChildren()[i+1];
            }
            else // v < C.Ki  v strightly smaller than K_{i}
            {
                curr_node = curr_node->accessChildren()[i];
            }
        }
        // iterate through each key in the Leaf Node 
        for (unsigned int i=0; i<curr_node->getSlots(); ++i)
        {
            if (curr_node->accessKeys()[i] == v)
            {
                ret = curr_node;
                // return C->accessChildren()[i]; // return Pi, a pointer that point to the Actual Disk?????
            }
        }
    }
    return ret; // Not found 
}


int BPlusTree::IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(Node* curr_node, int given_key)
{
    // return index of K_{i} which is the smallest key >= v 
    for (unsigned int i = 0; i < curr_node->getSlots(); ++i)
    {
        if (given_key <= curr_node->accessKeys()[i])
        {   
            return i; 
        }
    }
    return -1; 
}

std::vector <Node *> BPlusTree::FindRange(int lower_bound, int upper_bound)
{
    // return a vector of pointer to nodes 
    std::vector <Node *> retVect; 
    if (this->getRootNode() != NULL)
    {

        Node* curr_node = this->getRootNode(); 
        // walk to the Leaf node first, following the lower bound 
        while (curr_node != NULL && curr_node->getLeaf() != true)
        {
            int i = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(curr_node, lower_bound);
            if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
            {
                unsigned int m = curr_node->getSlots();
                curr_node = curr_node->accessChildren()[m];
            }
            else if (lower_bound == curr_node->getKeyByIndex((unsigned int)i))
            {
                curr_node = curr_node->accessChildren()[i+1];
            }
            else
            {
                curr_node = curr_node->accessChildren()[i]; // where lb < C.Ki
            }
        }

        // if i != -1 == key exists or within range of current leaf node 
        int i; // = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(C, lb);  
        // else, walk right to valid leaf node 
        while(curr_node != NULL && -1 == (i = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(curr_node, lower_bound)))
        {
            curr_node = curr_node->getNext(); // access the next sibling on the right
        }

        int j; // = this->test(C, ub);
        while(curr_node != NULL && -1 == (j = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(curr_node, upper_bound))) 
        {
            retVect.push_back(curr_node);
            curr_node = curr_node->getNext();
        }
        // the last C->getNext() might be == NULL
        if (curr_node != NULL)
        {
            retVect.push_back(curr_node); 
        }

    }
    return retVect; // return empty vector if the BPlusTree is NULL OR found nothing within range 
}



bool BPlusTree::Insert(int key, std::string value)
{
    bool ret = false; 
    

    // if (tree is empty) create an empty leaf node to become the root node 
    if (this->getRootNode() == NULL)
    {
        int arr_keys[] = {key};
        std::string arr_values[] = {value};
        Node* new_root_node = new Node("root", 0, true, 1, arr_keys, arr_values); // leaf == true 
        this->setRootNode(new_root_node);


        ret = true; 
    }
    // else if (tree is NOT empty) Find the corresponding leaf node L that should contain key value K
    else
    {
        // walk to the leaf node L that should contain key value K
        Node* Leaf = this->getRootNode(); 
        while (Leaf->getLeaf() != true)
        {
            int i = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(Leaf, key);
            if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
            {
                unsigned int m = Leaf->getSlots();
                Leaf = Leaf->accessChildren()[m];
            }
            else if (key == Leaf->getKeyByIndex((unsigned int)i))
            {
                Leaf = Leaf->accessChildren()[i+1];
            }
            else
            {
                Leaf = Leaf->accessChildren()[i]; // where lb < C.Ki
            }
        }

        // if (L has less than n − 1 key values), which means there are still sapce for the new key
        if (Leaf->getSlots() < ORDER_M - 1)
        {
            this->InsertInLeaf(Leaf, key, value);
        }

        // else begin /* L has n − 1 key values already, split it */
        else  
        {
            // Create NEW node L′
            Node* LeafPrime = new Node();
            Node* tmp_node = new Node(Leaf->getNodeIdentifier(), Leaf->getLevel(), Leaf->getLeaf(), Leaf->getSlots(), Leaf->accessKeys(), Leaf->accessValues(), Leaf->accessChildren()); 
            this->InsertInLeaf(tmp_node, key, value); // should be OverFull after this line


            LeafPrime->setNext(Leaf->getNext()); // set LPrime next pointer to point to L next 
            Leaf->setNext(LeafPrime); // set next pointer of L to point to LPrime 
            LeafPrime->setPrev(Leaf); // set LPrime's prev pointer to L


            // In case there exist node in LPrime->getNext()
            // then set the Prev pointer of LPrime->getNext() to point to LPrime
            if (LeafPrime->getNext() != NULL)
            {
                (LeafPrime->getNext())->setPrev(LeafPrime);
            }
            
            
            unsigned int midIndexOfKeysArray = ceil((ORDER_M - 1) / 2.0); // through T.K⌈n∕2⌉

            // Copy Valid Keys from 1st half of T to L 
            Leaf->setSlots(midIndexOfKeysArray);
            for (unsigned int i = 0; i < Leaf->getSlots(); ++i)
            {   
                Leaf->accessKeys()[i] = tmp_node->accessKeys()[i]; 
            }
            // Copy Valid Values from 1st half of T to L
            for (unsigned int i = 0; i < Leaf->getSlots(); ++i)
            {   
                Leaf->accessValues()[i] = tmp_node->accessValues()[i]; 
            }




            // Copy Valid Keys from 2nd half of T to LPRIME 
            LeafPrime->setSlots(ORDER_M - midIndexOfKeysArray); // update slots to T.P⌈n∕2⌉+1 onward
            for (unsigned int i = 0; i < LeafPrime->getSlots(); ++i) 
            {
                LeafPrime->accessKeys()[i] = tmp_node->accessKeys()[i + midIndexOfKeysArray];
            }
            // Copy Valid Values from 2nd half of T to LPRIME 
            for (unsigned int i = 0; i < LeafPrime->getSlots(); ++i) 
            {
                LeafPrime->accessValues()[i] = tmp_node->accessValues()[i + midIndexOfKeysArray];
            }



            // =============== InsertInParent() does NOT need the value but only the key as reference ===============

            int KeyPrime = LeafPrime->accessKeys()[0]; // KPrime == the smallest key-value in L′, which is the first Key

            this->InsertInParent(Leaf, KeyPrime, LeafPrime);

            delete tmp_node; 
        }

        ret = true; 
    }
    return ret; 

}


// TESTED
void BPlusTree::InsertInLeaf(Node* Leaf, int key, std::string value)
{
    // if (key smaller than everything in Keys)
    if (key < Leaf->accessKeys()[0])
    {
        
        // move existing keys in L down by 1 slot to the right 
        for (int i = (Leaf->getSlots() - 1); i >= 0; --i)
        {   
            Leaf->accessKeys()[i+1] = Leaf->accessKeys()[i];
        }
        // move existing values in L down by 1 slot to the right 
        for (int i = (Leaf->getSlots() - 1); i >= 0; --i)
        {   
            Leaf->accessValues()[i+1] = Leaf->accessValues()[i];
        }
        // insert Key and Value to index 0
        Leaf->accessKeys()[0] = key;
        Leaf->accessValues()[0] = value; 
        Leaf->setSlots(Leaf->getSlots() + 1);
    }
    // else if (key is greater [Not necessary equal to since key in our B+Tree is unique] than any one of the keys)
    else
    {
        // Let Ki be the highest value Key in L that is less than or equal to K
        int index_of_ith_key = -1; 
        for (int i = Leaf->getSlots() - 1; i >= 0; --i)
        {
            if ((Leaf->accessKeys()[i] <= key))
            {
                index_of_ith_key = i;
                break; 
            }
        }
        if (index_of_ith_key != -1) // just in case? 
        {
            // move Keys down 1 slot to the right for key to slot into [i+1]
            for (int i = (Leaf->getSlots() - 1); i >= (index_of_ith_key + 1); --i)
            {
                Leaf->accessKeys()[i+1] = Leaf->accessKeys()[i];
            }
            // move Values down 1 slot to the right for key to slot into [i+1]
            for (int i = (Leaf->getSlots() - 1); i >= (index_of_ith_key + 1); --i)
            {
                Leaf->accessValues()[i+1] = Leaf->accessValues()[i];
            }
            // // insert Key and Value to index index_of_ith_key + 1
            Leaf->accessKeys()[index_of_ith_key + 1] = key; 
            Leaf->accessValues()[index_of_ith_key + 1] = value; 
            Leaf->setSlots(Leaf->getSlots() + 1);
        }
        // else if (index_of_ith_key == -1), then EVERYTHING blow up :  (
    }
}




// TESTED !!!!!!!!!!!!!!!!!!!!!!!!!! 
void BPlusTree::InsertInParent(Node* N, int KeyPrime, Node* NPrime)
{
    // if (N == Root)
    if (this->getRootNode() == N)
    {

        int arr[] = {KeyPrime}; 
        Node* new_root_node = new Node("rootR", 0, false, 1, arr); // Leaf = false 

        new_root_node->accessChildren()[0] = N;             // Left pointer 
        new_root_node->accessChildren()[1] = NPrime;        // Mid1 pointer 
        
        this->setRootNode(new_root_node);

        return; 
    }


    Node* Parent = this->getParentNode(N); // Set Node* P to the Parent Node of N 
    if (Parent != NULL)
    {
        // if P still have space for key-value and child pointer 
        if (Parent->getSlots() < ORDER_M - 1)
        {
            // then insert (K′, N′) in P just after N
            this->InsertInInternalNode(Parent, N, KeyPrime, NPrime);
        }
        else // Split P and promote!!!
        {
            Node* tmp_node = new Node(Parent->getNodeIdentifier(), Parent->getLevel(), Parent->getLeaf(), Parent->getSlots(), Parent->accessKeys(), Parent->accessValues(), Parent->accessChildren()); 
            this->InsertInInternalNode(tmp_node, N, KeyPrime, NPrime); // Should be OVERFULL after this line 


            unsigned int midIndexOfChildrenArray = ceil(ORDER_M / 2.0);


            // new ParentPrime node as the node to store the splitted half from Parent 
            Node* ParentPrime = new Node();
            ParentPrime->setLeaf(Parent->getLeaf()); // set PPrime to have the SAME leaf status as P 


            // Copy Valid keys AND children from 1st half of T to P
            Parent->setSlots(midIndexOfChildrenArray - 1);
            // copying keys 
            for (unsigned int i = 0; i < Parent->getSlots(); ++i)
            {   
                Parent->accessKeys()[i] = tmp_node->accessKeys()[i]; 
            }
            // copying children 
            for (unsigned int i = 0; i < Parent->getSlots() + 1; ++i)
            {   
                Parent->accessChildren()[i] = tmp_node->accessChildren()[i]; 
            }

            // Reset out of bound children to NULL???????????????????????
            for (unsigned int i = Parent->getSlots() + 1; i <= ORDER_M + 1; ++i)
            {   
                Parent->accessChildren()[i] = NULL; 
            }





            // Copy Valid keys  AND children from 2nd half of T to PPRIME 
            ParentPrime->setSlots(ORDER_M - midIndexOfChildrenArray); 
            // copying keys
            for (unsigned int i = 0; i < ParentPrime->getSlots(); ++i)
            {
                ParentPrime->accessKeys()[i] = tmp_node->accessKeys()[i + midIndexOfChildrenArray];
            }
            // copying children 
            for (unsigned int i = 0; i < ParentPrime->getSlots() + 1; ++i) 
            {
                ParentPrime->accessChildren()[i] = tmp_node->accessChildren()[i + midIndexOfChildrenArray];
            }
            // Reset out of bound children to NULL 
            for (unsigned int i = ParentPrime->getSlots() + 1; i <= ORDER_M + 1; ++i)
            {
                ParentPrime->accessChildren()[i] = NULL;
            }




            // Let K′′ = T.K⌈(n+1)∕2⌉
            int KPrimePrime = tmp_node->accessKeys()[midIndexOfChildrenArray - 1];

            this->InsertInParent(Parent, KPrimePrime, ParentPrime);

            delete tmp_node; 
        }
    }

    
        
}


// Briefly TESTED 
Node* BPlusTree::getParentNode(Node* N) // find the Parent node of the given node N 
{
    Node* curr_node = this->getRootNode(); // C start from Root node of the BPlusTree 

    // use 1st key in node N as guidance to traverse
    int key = N->accessKeys()[0]; 

    bool found = false; 

    while(curr_node->getLeaf() != true && found == false)
    {
        
        int i = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(curr_node, key);

        //  if (SmallestKey... not found == -1)
        if (i == -1)
        {
            unsigned int m = curr_node->getSlots();
            // 
            if (N == curr_node->accessChildren()[m])
            {
                found = true;  
            }
            else
            {
                // access 1 level lower 
                curr_node = curr_node->accessChildren()[m]; 
            }
        }
        // else if (the key is equal to the ith key in curr_node)
        else if (key == curr_node->getKeyByIndex((unsigned int) i))
        {
            // access the [i + 1] child, which is the Child on the Right of the Key
            if (N == curr_node->accessChildren()[i+1])
            {
                found = true;  
            }
            else
            {
                // access 1 level lower 
                curr_node = curr_node->accessChildren()[i+1]; 
            }
        }
        else
        {
            // access the [i] child, which is the Child on the Left of the Key
            if (N == curr_node->accessChildren()[i])
            {
                found = true; 
            }
            else
            {
                // access 1 level lower 
                curr_node = curr_node->accessChildren()[i]; 
            }
        }
    }

    return found == true ? curr_node : NULL;  // if Parent Node is found, return C, else return NULL 

}





// then insert (K′, N′) in P just after N
// INSERT given KPrime key-value and NPrime Node to the Parent node P right after where N is !!!!!!!!!!!!!!!!!!!!!!!!!!!!
void BPlusTree::InsertInInternalNode(Node* Parent, Node* N, int KeyPrime, Node* NPrime) // P == Parent of N, KPrime == the smallest key-value in N′
{

    int key = N->accessKeys()[0]; // get key of N to find our way to insert KPrime, NPrime after N inside P
    int i = this->IndexOfSmallestKeyGreaterThanOrEqualToGivenKey(Parent, key);

    int index_for_KeyPrime = -1; 
    int index_for_NPrime = -1;

    // then insert (K′, N′) in P just after N
    if (i == -1)
    {
        unsigned int m = Parent->getSlots();

        // P->accessChildren()[m] == N
        if (N == Parent->accessChildren()[m])
        {
            index_for_KeyPrime = m;
            index_for_NPrime = index_for_KeyPrime + 1;
        }
    }
    else if (key == Parent->getKeyByIndex((unsigned int) i))
    {
        // P->accessChildren()[i+1] == N
        if (N == Parent->accessChildren()[i+1])
        {
            index_for_KeyPrime = i + 1;
            index_for_NPrime = index_for_KeyPrime + 1;
        }
    }
    else
    {
        // P->accessChildren()[i] == N
        if (N == Parent->accessChildren()[i])
        {
            index_for_KeyPrime = i;
            index_for_NPrime = index_for_KeyPrime + 1;
        }
    }

    // move keys down by 1 slot to the right 
    for (int i = Parent->getSlots()-1;  i >=index_for_KeyPrime; --i)
    {
        Parent->accessKeys()[i+1] = Parent->accessKeys()[i];
    }

    // move Children down by 1 slot to the right 
    for (int i = Parent->getSlots();  i >= index_for_NPrime; --i)
    {
        Parent->accessChildren()[i+1] = Parent->accessChildren()[i];
    }

    Parent->accessKeys()[index_for_KeyPrime] = KeyPrime;
    Parent->accessChildren()[index_for_NPrime] = NPrime;
    Parent->setSlots(Parent->getSlots() + 1);

}


bool BPlusTree::Delete(int k)
{
    bool ret = false; 
    // find the leaf node L that contains (K, P)
    Node* found_in_node = this->Find(k);
    if (found_in_node != NULL)
    {
        // delete entry(L, K, P)
        this->delete_entry(found_in_node, k, NULL);
        ret = true; 
    }

    return ret;
}




bool BPlusTree::delete_entry(Node* N, int K, Node* pointer)
{   


    // Removing the element 

    // delete key-pointer pair (K, P) from N
    unsigned int index_of_K = N->getIndexByKey(K);
    for (unsigned int i = index_of_K; i < N->getSlots(); ++i)
    {   
        N->accessKeys()[i] = N->accessKeys()[i+1]; 
    }

    // if N is Leaf node, also remove the Value of the key-value pair 
    if (N->getLeaf() == true)
    {
        for (unsigned int i = index_of_K; i < N->getSlots(); ++i)
        {   
            N->accessValues()[i] = N->accessValues()[i+1]; 
        }
    }

    // if N != Leaf, also remove the child pointer 
    else if (N->getLeaf() != true && pointer != NULL)
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
        bool prev_true_next_false = this->getPrevOrNextChildFromParentOfN(Parent, N, NPrime); // NPrime is Pass by Reference!!!!!
        


        // prev_true_next_false == true when retrieved the prev child 
        // prev_true_next_false == false when retrieved the next child 

        // Let K′ be the value between pointers N and N′ in parent(N)
        int index_for_KPrime = this->findIndexOfKPrime(Parent, N, NPrime, prev_true_next_false);
        int KPrime = Parent->accessKeys()[index_for_KPrime]; 




        // std::cout << "Or in Delete(14) iteration Parent should be [15, 17]" << std::endl; 
        // std::cout << "Or in Delete(14) iteration Parent should be [13]" << std::endl; 
        // for (unsigned int i=0; i < Parent->getSlots(); ++i)
        // {
        //     std::cout << Parent->accessKeys()[i]<< " ";
        // }
        // std::cout << std::endl;

        // std::cout << "Or in Delete(14) iteration N should be [13]" << std::endl; 
        // std::cout << "Or in Delete(14) iteration N should be [17]" << std::endl; 
        // for (unsigned int i=0; i < N->getSlots(); ++i)
        // {
        //     std::cout << N->accessKeys()[i]<< " ";
        // }
        // std::cout << std::endl;

        // std::cout << "Or in Delete(14) iteration NPrime should be [15, 16]" << std::endl;
        // std::cout << "Or in Delete(14) iteration NPrime should be [5, 7, 9, 11]" << std::endl;
        // for (unsigned int i=0; i < NPrime->getSlots(); ++i)
        // {
        //     std::cout << NPrime->accessKeys()[i]<< " ";
        // }
        // std::cout << std::endl;
                
        // std::cout << "Or in Delete(14) iteration KPrime should be 15: " << std::endl;
        // std::cout << "Or in Delete(14) iteration KPrime should be 13: " << std::endl;
        // std::cout << KPrime << std::endl; 







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
                // The procedure swap_pointers(N, N′) merely swaps the values of 
                // the (pointer) variables N and N′ 
                // this swap has no effect on the tree itself
                this->swap_pointers(N, NPrime);

            }


            // std::cout << "We want N to have [3, 4], and NPrime to have [2]" << std::endl;
            // std::cout << "OR in 2nd Iteration want N to have [9, 11], and NPrime to have [5]" << std::endl;
            // std::cout << "OR in Delete(14) iteration we want N to have [15, 16], and NPrime to have [13]" << std::endl;
            // std::cout << "" <<  std::endl;
            // std::cout << "Insdie N: " << std::endl;
            // for (unsigned int i=0; i<N->getSlots(); ++i)
            // {
            //     std::cout << N->accessKeys()[i] << " "; 
            // }
            // std::cout << std::endl; 
            // std::cout << "Insdie NPrime : " << std::endl;
            // for (unsigned int i=0; i<NPrime->getSlots(); ++i)
            // {
            //     std::cout << NPrime->accessKeys()[i] << " "; 
            // }
            // std::cout << std::endl; 




            // if (N is not a leaf)
            if (N->getLeaf() != true)
            {
                this->appendKPrimeAndNToNPrime(NPrime, KPrime, N);

                // std::cout << "In 2nd Iteration" << std::endl;
                // std::cout << "NPrime should have [5, 7, 9, 11]" << std::endl;
                // for (unsigned int i=0; i<NPrime->getSlots(); ++i)
                // {
                //     std::cout << NPrime->accessKeys()[i] << " "; 
                // }
                // std::cout << std::endl; 
            
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

  



            // std::cout << "We should have NPrime with all the Keys from NPrime and N" << std::endl;
            // std::cout << "where NPrime Keys is NOW [2, 3, 4]" << std::endl;
            // std::cout << "Or in 2 nd Iteration where NPrime Keys is NOW [5, 7, 9, 11]" << std::endl;
            // std::cout << "Or in Delete(14) interation where NPrime Keys is NOW [13, 15, 16]" << std::endl;
            // std::cout << "" << std::endl;
           
            // for (unsigned int i=0; i<NPrime->getSlots(); ++i)
            // {
            //     std::cout <<NPrime->accessKeys()[i] << " "; 
            // }
            // std::cout << std::endl; 
            // std::cout << std::endl; 





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





bool BPlusTree::getPrevOrNextChildFromParentOfN(Node* P, Node* N, Node* &NPrime) // NPrime is Pass by Reference!!!!!
{
    bool ret = false;
    // int index_of_N = P->getIndexByChildPointer(N);
    // // check + 1 Children slot on the Right is Valid index
    // // just in case, also make use the Valid index is NOT accessing NULL
    // // check if stealing from sibiling will NOT break invariant 
    // if ((index_of_N + 1) <= (int)P->getSlots() && P->accessChildren()[index_of_N + 1] != NULL
    // && (P->accessChildren()[index_of_N + 1]->getSlots() - 1) < ceil((ORDER_M - 1) / 2.0))
    // {
    //     NPrime = P->accessChildren()[index_of_N + 1];
    //     ret = true; 
    // }
    // // If right is Not good sibiling to steal from 
    // // check the left sibiling 
    // else if ((index_of_N - 1) >= 0 && P->accessChildren()[index_of_N - 1] != NULL
    // && (P->accessChildren()[index_of_N - 1]->getSlots() - 1) < ceil((ORDER_M - 1) / 2.0))
    // {
    //     NPrime = P->accessChildren()[index_of_N - 1];
    //     ret = true; 
    // }
    // // if CANNOT steal from both Right or Left,
    // // then access Left if N is the Last Child of P
    // // Or access Right if N is NOT the Last Child of P
    // else
    // {
    //     // if N == Last Child of P
    //     // NPrime = Previous Child
    //     if (P->accessChildren()[P->getSlots()] == N)
    //     {
    //         NPrime = P->accessChildren()[P->getSlots() - 1];
    //         ret = true; // true == retrieved Prev Child  
    //     }
    //     // else if N != Last Child of P
    //     // NPrime = Next Child 
    //     else
    //     {
    //         for (unsigned int i=0; i < P->getSlots();++i)
    //         {
    //             if (P->accessChildren()[i] == N)
    //             {
    //                 NPrime = P->accessChildren()[i + 1];
    //                 ret = false; // false = retrieved Next Child 
    //                 break;
    //             }
    //         }
    //     }

    // }




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
                //ret = false; // false = retrieved Next Child 
                break;
            }
        }
    }
    return ret; 
}

int BPlusTree::findIndexOfKPrime(Node* P, Node* N, Node* NPrime, bool prev_true_next_false)
{
    // Let K′ be the value between pointers N and N′ in parent(N)
    int index_of_KPrime = -1; 
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

void BPlusTree::swap_pointers(Node* &N, Node* &NPrime)
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






