#ifndef BPLUSTREEDBMS_H__
#define BPLUSTREEDBMS_H__

#include <string>
#include <memory>

using namespace std;

struct node {
  int data;               // data: the value of this node
  shared_ptr<node> next;  // next: pointer to the next node in the list, or NULL if this is the last node.
};

// Linked List Invariant: following the 'next' links in a linked list
// node must eventually lead to a NULL reference signifying the end of
// the list. (E.g. no circular references are allowed.)
class BPlusTreeDBMS {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set top pointer to a null shared_ptr of node
  BPlusTreeDBMS();

  //deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~BPlusTreeDBMS();

  int BPlusTreeDBMSFunc();
    
    

private:
  shared_ptr<node> top_ptr_;

  // you can add add more private member variables and member functions here if you need
    
    
    
};

#endif  // BPLUSTREEDBMS_H__