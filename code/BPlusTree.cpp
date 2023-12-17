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

            int i = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(curr_node, v);

            if (i == -1) // -1 == there is no such number i where K_{i} is smallest number such that v ≤ C.Ki
            {
                unsigned int m = curr_node->getSlots();  // m == index of last non-null pointer in the node, slot IS ALREADY the last pointer as Exclusive End indexing [0, 4)
                curr_node = curr_node->accessChildren()[m]; // Pointer at index m
            }
            else if (v == curr_node->getKeyByIndex(i))
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


int BPlusTree::IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(Node* curr_node, int given_key)
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
            int i = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(curr_node, lower_bound);
            if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
            {
                unsigned int m = curr_node->getSlots();
                curr_node = curr_node->accessChildren()[m];
            }
            else if (lower_bound == curr_node->getKeyByIndex(i))
            {
                curr_node = curr_node->accessChildren()[i+1];
            }
            else
            {
                curr_node = curr_node->accessChildren()[i]; // where lb < C.Ki
            }
        }

        // if i != -1 == key exists or within range of current leaf node 
        int i; // = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(C, lb);  
        // else, walk right to valid leaf node 
        while(curr_node != NULL && -1 == (i = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(curr_node, lower_bound)))
        {
            curr_node = curr_node->getNext(); // access the next sibling on the right
        }

        int j; // = this->test(C, ub);
        while(curr_node != NULL && -1 == (j = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(curr_node, upper_bound))) 
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
            int i = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(Leaf, key);
            if (i == -1)   // -1 ==  there is no such number i such that lb <= C.Ki
            {
                unsigned int m = Leaf->getSlots();
                Leaf = Leaf->accessChildren()[m];
            }
            else if (key == Leaf->getKeyByIndex(i))
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

        // else if (L does NOT have enough space for 1 more key)  /* L has n − 1 key values already, split it */
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




// TESTED 
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
        
        int i = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(curr_node, key);

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
        else if (key == curr_node->getKeyByIndex(i))
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
// INSERT given KPrime key-value and Child node NPrime Node to the Parent node P right after where N is !
void BPlusTree::InsertInInternalNode(Node* Parent, Node* N, int KeyPrime, Node* NPrime) // P == Parent of N, KPrime == the smallest key-value in N′
{

    int key = N->accessKeys()[0]; // get key of N to find our way to insert KPrime, NPrime after N inside P
    int i = this->IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(Parent, key);

    int index_for_KeyPrime = -1; 
    int index_for_NPrime = -1;

    // insert (K′, N′) in P right after N
    // if (i is -1, means key is Smaller Than ALL Keys) then insert KPrime, NPrime at the end 
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
    else if (key == Parent->getKeyByIndex(i))
    {
        // P->accessChildren()[i+1] == N
        if (N == Parent->accessChildren()[i+1])
        {
            index_for_KeyPrime = i + 1;
            index_for_NPrime = index_for_KeyPrime + 1;
        }
    }
    else // ?
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

    // insert the KPrime key and NPrime child and set Slots + 1
    Parent->accessKeys()[index_for_KeyPrime] = KeyPrime;
    Parent->accessChildren()[index_for_NPrime] = NPrime;
    Parent->setSlots(Parent->getSlots() + 1);

}


bool BPlusTree::Delete(int key)
{
    bool ret = false; 
    // find the leaf node L that contains (K, P)
    Node* found_in_node = this->Find(key);
    if (found_in_node != NULL)
    {
        // delete entry(L, K, P)
        this->delete_entry(found_in_node, key, NULL);
        ret = true; 
    }

    return ret;
}




bool BPlusTree::delete_entry(Node* N, int key, Node* pointer)
{   
    // delete key-pointer pair (K, P) from N
    unsigned int index_of_key = N->getIndexByKey(key);
    for (unsigned int i = index_of_key; i < N->getSlots(); ++i)
    {   
        N->accessKeys()[i] = N->accessKeys()[i+1]; 
    }

    // if N is Leaf node, also remove the Value of the key-value pair 
    if (N->getLeaf() == true)
    {
        for (unsigned int i = index_of_key; i < N->getSlots(); ++i)
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

    // update slots after deleting key 
    N->setSlots(N->getSlots() - 1);






    // ROOT case 
    if (N == this->getRootNode())
    {
        // if (N has No remaining Key AND NO remaining child pointer)
        if (N->getNumOfChildren() == 0 && N->getSlots() == 0)
        {
            this->setRootNode(nullptr); 
            delete N; 
        }
        // else if (N has No remaining Key AND 1 remaining Child pointer)
        // B+Tree Invariant matters
        else if (N->getNumOfChildren() == 1 && N->getSlots() == 0)
        {
            Node* child_of_N = N->getTheRemainingChild();
            this->setRootNode(child_of_N); 
            delete N; 
        }


    }



    // NON ROOT case 
    else // N != this->getRootNode()
    {

    // else if (N has too few values/pointers after deleting the given Key and Pointer) then begin
    // Note: The case of (N has too few values/pointers AND N is Root) is not important
    // as Root is NOT bounded by to have at least ⌈(ORDER_M - 1) / 2⌉ Keys
        if (N->hasTooFewRemainingValuesOrPointers() == true)
        {
            Node* Parent = this->getParentNode(N); 

            Node* NPrime = NULL;
            // Check whether N is Left OR Mid1 child of P 
            // Let N′ be the previous or next child of parent(N) 
            bool prev_true_next_false = this->getPrevOrNextChildFromParentOfN(Parent, N, NPrime); // NPrime is Pass by Reference!
            
            // prev_true_next_false == true when retrieved the prev child 
            // prev_true_next_false == false when retrieved the next child 

            // Let K′ be the value between pointers N and N′ in parent(N)
            int index_for_KeyPrime = this->findIndexOfKPrime(Parent, N, NPrime, prev_true_next_false);
            int KeyPrime = Parent->accessKeys()[index_for_KeyPrime]; 


            // if stealing 1 elem from sibling NPrime makes the sibling NPrime become having TOO FEW values
            // then merge/combine/coalesce
            if ((NPrime->getSlots() - 1) < ceil((ORDER_M - 1) / 2.0))
            {
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~ Merge/Combine case ~~~~~~~~~~~~~~~~~~~~~~~~~~

                // if (N is a predecessor of N′) then swap variables(N, N′)
                if (Parent->getIndexByChildPointer(N) < Parent->getIndexByChildPointer(NPrime))
                {
                    // swaps the pointers of N and NPrime 
                    this->swap_pointers(N, NPrime);

                }



                // if (N is not a Leaf node)
                if (N->getLeaf() != true)
                {
                    this->appendKPrimeAndNToNPrime(NPrime, KeyPrime, N);
                
                }
                // else if (N is a Leaf node)
                else
                {
                    this->appendNToNPrime(NPrime, N);
                    // Update Next and Prev Pointers of NPimre, (N is to be Deleted, so does not matter)
                    NPrime->setNext(N->getNext());
                    // just in case, NPrime->getNext() could be NULL
                    if (NPrime->getNext() != NULL)
                    {
                        NPrime->getNext()->setPrev(NPrime);
                    }
                }

                // recurse to delete KPrime and N from Parent in 1 level higher up
                delete_entry(Parent, KeyPrime, N);

            }


            // else when (NPrime->getSlots() - 1)  >=  ceil((ORDER_M - 1) / 2.0)
            // NPrime still have Valid # of Keys after being stolen Keys - 1 
            else
            {
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~ Stealing From the Sibiling ~~~~~~~~~~~~~~~~~~~~~~~~~~

                // if (NPrime is a predecessor of N) 
                if (Parent->getIndexByChildPointer(NPrime) < Parent->getIndexByChildPointer(N))
                {

                    // if (N is a Not a Leaf node)
                    if (N->getLeaf() != true)
                    {   
                        // let m be such that N′.Pm is the last child pointer in N′
                        unsigned m = NPrime->getSlots();

                        // retrieve mth child pointer and m-1th Key of NPrime for later, before deleting from NPrime 
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
                        N->accessKeys()[0] = KeyPrime;

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
                        int index_of_KPrime = Parent->getIndexByKey(KeyPrime);
                        Parent->accessKeys()[index_of_KPrime] = mth_minus_one_key_of_NPrime; 

                    }


                    // else if (N is a Leaf Node)
                    else
                    {
                        // let m be such that (N′.Pm, N′.Km) is the last pointer/Key pair in N′
                        // Since we don't use key-point pair in Leaf but to store data in Leaf directly 
                        // We set m to same index of last Key in NPrime 
                        int m = NPrime->getSlots() - 1;
                        int mth_key_of_NPrime = NPrime->accessKeys()[m];
                        std::string mth_value_of_NPrime = NPrime->accessValues()[m];

                        // remove (N′.Pm, N′.Km) from N′
                        // skipped N′.Pm and replace with removing string value at index m 
                        NPrime->accessKeys()[m] = 0;
                        NPrime->accessValues()[m] = "";
                        NPrime->setSlots(NPrime->getSlots() - 1);

                        // insert (N′.Pm, N′.Km) as the first pointer and value in N,
                        // by shifting other Keys and Values right
                        for (int i = N->getSlots() - 1; i >= 0; --i)
                        {
                            N->accessKeys()[i + 1] = N->accessKeys()[i];  
                        }
                        for (int i = N->getSlots() - 1; i >= 0; --i)
                        {
                            N->accessValues()[i + 1] = N->accessValues()[i];  
                        }


                        // slot in to index 0 as the 1 st elem 
                        N->accessKeys()[0] = mth_key_of_NPrime;
                        N->accessValues()[0] = mth_value_of_NPrime;


                        // SLot increment by 1 
                        N->setSlots(N->getSlots() + 1);


                        // replace K′ in parent(N) by N′.Km
                        int index_of_KPrime = Parent->getIndexByKey(KeyPrime);

                        // take mth_key_of_NPrime is the mth key BEFORE the stealing operations 
                        Parent->accessKeys()[index_of_KPrime] = mth_key_of_NPrime;
                        
                    }
                }

                // ~~~~~~~~~~~~~~~~~ SYMMETRIC CASES ~~~~~~~~~~~~~~~~~
                // else if (N is a predecessor of NPrime) 
                else if (Parent->getIndexByChildPointer(N) < Parent->getIndexByChildPointer(NPrime))
                {

                    // if (NPrime is a nonleaf node) then begin
                    if (NPrime->getLeaf() != true)
                    {   
                        // let m be such that N′.Pm is the 1st (by SYMMETRIC) child pointer in N
                        unsigned int m = 0;

                        // retrieve 1th child pointer and 1th Key of N (by SYMMETRIC) for later before deleting from N′
                        Node* mth_child_of_NPrime = NPrime->accessChildren()[m];
                        int mth_key_of_NPrime = NPrime->accessKeys()[m];


                        // move the Keys and Children Array to the Left by 1 slot to cover the removed slot 
                        for (unsigned int i = m; i < NPrime->getSlots(); ++i)
                        {
                            NPrime->accessKeys()[i] = NPrime->accessKeys()[i+1];
                        }
                        for (unsigned int i = m; i < NPrime->getSlots() + 1; ++i)
                        {
                            NPrime->accessChildren()[i] = NPrime->accessChildren()[i+1];
                        }
                        
                        // since the whole array of Keys and Children have moved to the Left by 1 Slot,
                        // just in case, Set the last elem to 0 and NULL
                        // And update the Slots count 
                        NPrime->accessKeys()[NPrime->getSlots() - 1] = 0;
                        NPrime->accessChildren()[NPrime->getSlots()] = NULL;
                        NPrime->setSlots(NPrime->getSlots() - 1);




                        // insert (N′.Pm, K′) as the Last pointer and value in N (by SYMMETRIC),

                        // insert K′ as the Last Key of N(by SYMMETRIC)
                        N->accessKeys()[N->getSlots()] = KeyPrime;

                        // insert N′.Pm as the Last child of N (by SYMMETRIC)
                        N->accessChildren()[N->getSlots() + 1] = mth_child_of_NPrime;

                        // SLot increment by 1 
                        N->setSlots(N->getSlots() + 1);

                        // replace K′ in parent(N) by N′.Km−1?
                        int index_of_KeyPrime = Parent->getIndexByKey(KeyPrime);
                        Parent->accessKeys()[index_of_KeyPrime] = mth_key_of_NPrime; 

                    }
                    // else is (NPrime is a Leaf Node)
                    else
                    {
                        // let m be such that (N.Pm, N.Km) is the 1st (by SYMMETRIC) pointer/value pair in N
                        // Since we don't use key-point pair at Leaf but to store data in Leaf directly 
                        // We set m to index 1st Key in N
                        int m = 0; 

                        // STEAL 1st elem from NPrime to N 
                        int mth_key_of_NPrime = NPrime->accessKeys()[m];
                        std::string mth_value_of_NPrime = NPrime->accessValues()[m];

                        // remove (N′.Value_m, N′.Km) from N′
                        // 
                        NPrime->accessKeys()[m] = 0;
                        NPrime->accessValues()[m] = "";

                        for (unsigned int i = m; i<NPrime->getSlots(); ++i)
                        {
                            NPrime->accessKeys()[i] = NPrime->accessKeys()[i+1];
                        }
                        for (unsigned int i = m; i<NPrime->getSlots(); ++i)
                        {
                            NPrime->accessValues()[i] = NPrime->accessValues()[i+1];
                        }

                        NPrime->setSlots(NPrime->getSlots() - 1);

                        
                        // insert (N′.Value_m, N′.Km) as the LAST(by SYMMETRIC) pointer and value in N,
                        N->accessKeys()[N->getSlots()] = mth_key_of_NPrime;
                        N->accessValues()[N->getSlots()] = mth_value_of_NPrime;
                        N->setSlots(N->getSlots() + 1);

                        // replace K′ in parent(N) by N′.Km
                        int index_of_KPrime = Parent->getIndexByKey(KeyPrime);

                        // take mth key of NPrime is the mth key AFTER the stealing operations 
                        Parent->accessKeys()[index_of_KPrime] = NPrime->accessKeys()[m];
                    }

                }

            }

        }

    }
    return false; 
}


// set NPrime to Either the prev child OR next child of N in P
// THIS FUNCTION CAN BE OPTIMIZE by also checking if the sibiling node have enough keys to steal from immediately
// But the test cases has settled with the current design of this function, So no refactoring or optimization at the moment  : (
bool BPlusTree::getPrevOrNextChildFromParentOfN(Node* P, Node* N, Node* &NPrime) // NPrime is Pass by Reference
{
    bool ret = false;
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






