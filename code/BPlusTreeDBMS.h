#ifndef BPLUSTREEDBMS_H__
#define BPLUSTREEDBMS_H__

#include <string>
#include <memory>
#include <iostream>
#include "Node.h"
#include "BPlusTree.h"

// using namespace std;





class BPlusTreeDBMS {

private:
  BPlusTree* _bplustree = NULL;




public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set top pointer to a null shared_ptr of node
  BPlusTreeDBMS();

  //deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~BPlusTreeDBMS();


  bool Create(int key, std::string value);
  bool ReadByKey(int key);
  bool ReadByRange(int lower_bound, int upper_bound);
  bool Update(int key, std::string value);
  bool Delete(int key);

  BPlusTree* getBPlusTree();

      
      


    
};

#endif  // BPLUSTREEDBMS_H__