#ifndef NODE_H__
#define NODE_H__

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

// using namespace std;

#define ORDER_M 5

class Node {
private:
    std::string node_identifier; // for testing purpose only, USELESS
    unsigned int level; // USELESS 




    bool leaf;                      // node is a Leaf node OR not  
    unsigned int slots;             // number of valid keys in keys[], e.g. if [2, 3, 5, 7] in the keys array, then slots == 4
    int keys[ORDER_M];              // ORDER_M - 1 == actual max keys, designed to have 1 extra slot to handle OVERFULL situation 
    Node* children[ORDER_M + 1];    // ORDER_M == actual max children, designed to have 1 extra slot to handle OVERFULL situation 
    std::string values[ORDER_M];    // ORDER_M - 1 == actual max string data, only being used in the Leaf node, designed to have 1 extra slot to handle OVERFULL situation 
    Node* prev;                     // pointer for Leaf node to link to the previous leaf node (on the left)
    Node* next;                     // pointer for Leaf node to link to the next leaf node (on the right)



    



public:
    // Constructors 
    Node();
    Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, 
        int _keys[]);
    Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, 
        int _keys[], std::string _values[]);

    Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, 
            int _keys[], std::string _values[], Node* _children[]);

    // Destructor 
    ~Node();

    void clear();

    std::string getNodeIdentifier();
    void setNodeIdentifier(std::string data);

    unsigned int getLevel();
    void setLevel(unsigned int level);

    bool getLeaf();
    void setLeaf(bool leaf);

    int getKeyByIndex(int i);
    int getIndexByKey(int key);

    int getIndexByChildPointer(Node* child);

    unsigned int getSlots();
    void setSlots(unsigned int slots);

    unsigned int getNumOfChildren();
    Node* getTheRemainingChild();
    bool hasTooFewRemainingValuesOrPointers();

    void setPrev(Node* node);
    Node* getPrev();
    void setNext(Node* node);
    Node* getNext();

    // const int * accessKeys() const;
    int* accessKeys();
    Node** accessChildren();
    std::string* accessValues();



    // overloading operator << lets you put a Node object into an output
    // stream.
    friend std::ostream &operator<<(std::ostream &out, Node node);


};

#endif // NODE_H__

