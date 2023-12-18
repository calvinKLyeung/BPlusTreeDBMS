# Mini Database with B+Tree 

## About the program
**Project goal** <br> 
This project plan to implement a mini database CRUD operations with B+Tree data structure and practice memory management with plane points. <br> 

**B+Tree on paper** <br>
B+Tree is a commonly seen data structure in databases. Unlike hash table which stores key-value pairs in unordered array and only allows single key lookup, B+ tree stores values in sorted order with indices and supports data retrieval lookup by index and range scan which speeds up query execution. Unlike B-tree which stores data in each node at every level which requires back-and-forth traversal, B+tree stores pointers or data in the linked leaf nodes only which allows range scans and sequential access along the leaf 
nodes at the bottom level. The self-balancing nature of B+tree allows O(log n) time complexity for traverse. The fact that all data are store only in the linked leaf nodes at the bottom allows range scans and sequential access along the leaf nodes in O(n) complexity. <br>
 
**B+Tree invariants**
- M-way search tree, within each node there can be up to M-paths to other nodes (Max children = order M)
- Perfectly balanced, where ALL leaf nodes are in the same level and reachable with O(log n) complexity
- Every node other than root must be At Least half full ⌈(ORDER_M - 1) / 2⌉ keys and ⌈(ORDER_M)/  2⌉ children
- Every inner node with k keys must has k+1 non-null children nodes
- Root node can hold fewer than ⌈(ORDER_M - 1) / 2⌉ pointers, however, it must hold at least two pointers, unless the tree consists of only one node

**B+Tree implementation** <br> 
I was not able to figure out how to assign pointers to point to persistent storage in the hard disk. Therefore, I decided to store the data within the Leaf Nodes in heap memory instead. It turns out implementing a data structure from scratch, like designing my own test cases with expected input and output values, is way more tricky than I thought. Also, Memory allocation and management with plane pointer for more than a few lines of code is way more difficult than expected. Right now, the so called B+Tree database feels like a associative array in practice but with the item in sorted order. <br>

**Memory Leaks Status** <br>
I thought the project might be a good chance to practice pointer and memory management.
And decided to use the normal pointer instead of the smart pointer. 
But ended up in an infinite loop of memory leaks debugging. <br>   

main.cpp <br> 
```
==2489== HEAP SUMMARY:
==2489==     in use at exit: 0 bytes in 0 blocks
==2489==   total heap usage: 191 allocs, 191 frees, 86,964 bytes allocated
==2489==
==2489== All heap blocks were freed -- no leaks are possible
==2489==
==2489== For lists of detected and suppressed errors, rerun with: -s
==2489== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0
```

Test file<br>
```
==2491== LEAK SUMMARY:
==2491==    definitely lost: 392 bytes in 14 blocks
==2491==    indirectly lost: 24,358 bytes in 113 blocks
==2491==      possibly lost: 0 bytes in 0 blocks
==2491==    still reachable: 4,896 bytes in 17 blocks
==2491==         suppressed: 0 bytes in 0 blocks
==2491== Reachable blocks (those to which a pointer was found) are not shown.
==2491== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==2491==
==2491== For lists of detected and suppressed errors, rerun with: -s
==2491== ERROR SUMMARY: 14 errors from 14 contexts (suppressed: 0 from 0
```


## Running the program demo
Follow the below steps to set up and run the program:
1. Go to build dir by ```cd build/```
2. Clear existing files and subdirs in build dir by ```rm -r *```
3. Run ```cmake ..```
4. Run ```make```
5. Run ```./run_app``` 

The demo uses the CRUD operations to store the CSPB courses in the B+Tree. The course code number serves as the index key and the course title serves as the content string value. <br>
You can modify the function calls in main.cpp to use the CRUD <br>



## BPlusTreeDBMS Class
How to use the CRUD operations: <br>
- ```Create(int, string)```: Create new record in the B+Tree with the given key and value. It invokes ```Insert(int, string)``` of the ```BPlusTree``` class. 

- ```ReadByKey(int)```: Read record from B+Tree using the given key. It invokes ```Find(int)``` of the ```BPlusTree``` class and print out the key:value pair retrieved from the B+Tree.<br>

- ```ReadByRange(int, int)```: Read record from B+Tree with the given range of index from lower bound to upper bound inclusively. It invokes ```FindRange(int, int)``` of the ```BPlusTree``` class and prints out all the key:value pairs reocrd within the range index. 

- ```Update(int, string)```: Find the record with the given key and replace value with the new one. It invokes the ```Find(int)``` of the ```BPlusTree``` class and modifies the value stored in the B+Tree Leaf node. <br> 

- ```Delete(int)```: Delete the key and the corresponding value in the B+Tree. It invokes ```Delete(int)``` of the ```BPlusTree``` class to perform the B+Tree traverse, deletion, and balancing mechanism. <br>


## BPlusTree Class
Major functions of the B+Tree: <br> 
- ```Find(int v)```: Traverse to the bottom level following the given index and walk through the linked leaf nodes to find the node that contains the given key.

- ```FindRange(int lower_bound, int upper_bound)```: Traverse to the bottom level following the given lower bound index. Then, walk through the linked leaf nodes and store the pointers of node which contains a key within the lower bound and upper bound index. 

- ```Insert(int key, std::string value)```: Insert the key:value pair to the corresponding leaf node while also maintaining the self-balanced condition of the B+Tree by splitting nodes and promoting key to upper level. 

- ```Delete(int key)```: Delete the key and the corresponding value from the B+Tree. It goes to the leaf node to delete the key:value pair while also maintaining the self-balanced condition of the B+Tree by splitting and merging nodes. 

## Node Class
What is in a node: <br> 
```
bool leaf;                      // node is a Leaf node OR not  
unsigned int slots;             // number of valid keys in keys[], e.g. if [2, 3, 5, 7] in the keys array, then slots == 4
int keys[ORDER_M];              // ORDER_M - 1 == actual max keys, designed to have 1 extra slot to handle OVERFULL situation 
Node* children[ORDER_M + 1];    // ORDER_M == actual max children, designed to have 1 extra slot to handle OVERFULL situation 
std::string values[ORDER_M];    // ORDER_M - 1 == actual max string data, only being used in the Leaf node, designed to have 1 extra slot to handle OVERFULL situation 
Node* prev;                     // pointer for Leaf node to link to the previous leaf node (on the left)
Node* next;                     // pointer for Leaf node to link to the next leaf node (on the right)
```


