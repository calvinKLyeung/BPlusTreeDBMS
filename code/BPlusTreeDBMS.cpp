#include "BPlusTreeDBMS.h"



// constructor, initialize class variables and pointers here if need.
BPlusTreeDBMS::BPlusTreeDBMS(){
  // Your code here
  // top_ptr_ = NULL; // top_ptr_ already in private data section 
    
}

//deconstructor,
BPlusTreeDBMS::~BPlusTreeDBMS(){
}

bool BPlusTreeDBMS::Create(int key, std::string value)
{

  bool ret;
  
  if (this->_bplustree == NULL)
  {
    this->_bplustree = new BPlusTree;
    this->_bplustree->Insert(key, value);


    ret = true;
  }
  else if (this->_bplustree != NULL && this->_bplustree->Find(key) == NULL)
  {
    this->_bplustree->Insert(key, value);
  }
  else if (this->_bplustree != NULL && this->_bplustree->Find(key) != NULL)
  {
    std::cout << "Record already exist!" << std::endl; 
    ret = false;
  }

  return ret; 

}


bool BPlusTreeDBMS::ReadByKey(int key)
{
  bool ret = false; 
  if (this->_bplustree != NULL)
  {
    Node* result_node;
    if ((result_node = this->_bplustree->Find(key)) != NULL)
    {
      // read from the node 
      std::cout << "Key : Values pair found with the given key" << std::endl;
      std::cout << key << " : " << result_node->accessValues()[result_node->getIndexByKey(key)] << std::endl;


      ret = true;
    } 
    else
    {
      // tell the user the key is NOT in the database
      std::cout << "Given key is not in the database." << std::endl;
    }
  }
  else
  {
    std::cout << "Database is empty. Unable to read anything with the given key. " << std::endl;
  }
  return ret; 
}

bool BPlusTreeDBMS::ReadByRange(int lower_bound, int upper_bound)
{
  bool ret = false; 
  if (this->_bplustree != NULL)
  {
    std::vector <Node *> result_vect; 
    if ((result_vect = this->_bplustree->FindRange(lower_bound, upper_bound)).size() != 0)
    {
      std::cout << "Key : Values pairs found in the given range" << std::endl;
      for (unsigned int i = 0 ; i < result_vect.size(); ++i)
      {

        unsigned int slots_of_ith_node = result_vect.at(i)->getSlots();

        for(unsigned int j = 0; j < slots_of_ith_node; ++j)
        {
          std::cout << result_vect.at(i)->accessKeys()[j] << " : " << result_vect.at(i)->accessValues()[j] << std::endl;
        }
      }
      std::cout << std::endl;

      ret = true;
    }
    else
    {
      // tell the user the range of keys is NOT in the database
      std::cout << "Given range of keys is not in the database." << std::endl;
    }
  }
  else
  {
    std::cout << "Database is empty. Unable to read anything with the given range of keys. " << std::endl;
  }
  return ret; 
}


bool BPlusTreeDBMS::Update(int key, std::string value)
{
  bool ret = false;
  if (this->_bplustree != NULL)
  {
    Node* result_node;
    if ((result_node = this->_bplustree->Find(key)) != NULL)
    {
      result_node->accessValues()[result_node->getIndexByKey(key)] = value;
      std::cout << "Updated successfully." << std::endl;
      std::cout << key << " : " << result_node->accessValues()[result_node->getIndexByKey(key)] << std::endl;

      ret = true; 
    }
    else
    {
      std::cout << "Unable to update. Given key is not in the database." << std::endl;
    }

  }
  else
  {
    std::cout << "Database is empty. Unable to update anything with the given key : value pair. " << std::endl;
  }
  return ret; 
}


bool BPlusTreeDBMS::Delete(int key)
{
  bool ret = false; 
  if (this->_bplustree != NULL)
  {
    bool deleted = this->_bplustree->Delete(key);

    if (deleted == true)
    {
      std::cout << "Deleted successfully. " << std::endl;
    }
    else
    {
      std::cout << "Unable to delete. Given key is not in the database." << std::endl;
    }
  }
  else
  {
    std::cout << "Database is empty. Unable to delete anything." << std::endl;
  }



  return ret; 
}


BPlusTree* BPlusTreeDBMS::getBPlusTree()
{
  return this->_bplustree; 
}


