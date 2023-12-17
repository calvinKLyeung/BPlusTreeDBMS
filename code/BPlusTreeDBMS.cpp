#include "BPlusTreeDBMS.h"



// constructor, initialize class variables and pointers here if need.
BPlusTreeDBMS::BPlusTreeDBMS(){
  this->_bplustree = NULL;
    
}

//deconstructor,
BPlusTreeDBMS::~BPlusTreeDBMS(){
}

bool BPlusTreeDBMS::Create(int key, std::string value)
{

  bool ret = false;
  
  if (this->_bplustree == NULL)
  {
    this->_bplustree = new BPlusTree;
    this->_bplustree->Insert(key, value);
    std::cout << "Created successfully. " << key << " : " << value << " is now in the database." << std::endl; 

    ret = true;
  }
  else if (this->_bplustree != NULL)
  {
    if (this->_bplustree->Find(key) == NULL)
    {
      this->_bplustree->Insert(key, value);
      std::cout << "Created successfully. " << key << " : " << value << " is now in the database." << std::endl; 
      ret = true; 
    }
    else
    {
      std::cout << "Unable to create. Given key already exist in record!" << std::endl;
    }
    
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
      std::cout << " ----- Key : Value pair found with the given key ----- " << std::endl;
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
      std::cout << " ----- Key : Values pairs found in the given range ----- " << std::endl;

      for (unsigned int i = 0 ; i < result_vect.size(); ++i)
      {
        unsigned int slots_of_ith_node = result_vect.at(i)->getSlots();

        for(unsigned int j = 0; j < slots_of_ith_node; ++j)
        {
          int key = result_vect.at(i)->accessKeys()[j];
          if (key >= lower_bound && key <= upper_bound)
          {
            std::cout << key << " : " << result_vect.at(i)->accessValues()[j] << std::endl;
          }
        }
      }

      ret = true;
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
      //std::cout << key << " : " << result_node->accessValues()[result_node->getIndexByKey(key)] << std::endl;

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
      ret = true; 
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


