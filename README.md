# Mini Database with B+Tree 

## Running the program
Follow the below steps to set up and run the program:
1. Go to build dir by ```cd build/```
2. Clear existing files and subdirs in build by ```rm -r *```
3. Run ```cmake ..```
4. Run ```make```
5. Run ```./run_app```

## About the program
Unable to store the data in persistent storage. <br>
Instead, store the data within the Leaf Nodes. <br>
At the moment, the so called B+Tree mini database feels more like an associative array in practice. <br>
In the sense than the B+Tree with CRUD support key : value pair insertion, deletion, and look up. <br> 
But the data are all store in the Leaf nodes of the self balancing B+Tree. <br>
Which should be quicker to read and write. <br>  
Turns out designing a data structure from scratch including the test cases is way more tricky than I thought. <br> 
And Memory allocation and management for more than a few lines of code is way more difficult than expected. <br>



## Current Status
I thought the project might be a good place to practice pointer and memory management. <br> 
And decided to use the normal pointer instead of the smart pointer. <br>
Which ended up in infinite loop of memory leaks debugging. <br>   

main.cpp <br> 
```
==1789== LEAK SUMMARY:
==1789==    definitely lost: 8 bytes in 1 blocks
==1789==    indirectly lost: 5,342 bytes in 46 blocks
==1789==      possibly lost: 0 bytes in 0 blocks
==1789==    still reachable: 0 bytes in 0 blocks
==1789==         suppressed: 0 bytes in 0 blocks
==1789==
==1789== For lists of detected and suppressed errors, rerun with: -s
==1789== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

Test file<br>
```
==1790== LEAK SUMMARY:
==1790==    definitely lost: 392 bytes in 14 blocks
==1790==    indirectly lost: 24,358 bytes in 113 blocks
==1790==      possibly lost: 0 bytes in 0 blocks
==1790==    still reachable: 4,896 bytes in 17 blocks
==1790==         suppressed: 0 bytes in 0 blocks
==1790==
==1790== For lists of detected and suppressed errors, rerun with: -s
==1790== ERROR SUMMARY: 24 errors from 19 contexts (suppressed: 0 from 0)
```



## CRUD operations of the B+Tree mini database
How to use the CRUD operations: <br>
- Create <br>

- Read <br>
Read by key: 
Read by Range: 

- Update <br>

- Delete <br>


## B+Tree functions
How to use the B+Tree: <br> 





### What Mini Database?
A data storing structure implemented with B+Tree and support basic CRUN operations. 

### What is an B+Tree?

### Why is B+Tree?


## Data Structure


