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
    std::string node_identifier;
    unsigned int level;
    bool leaf;


    unsigned int slots;  // number of valid keys in keys[]     BUT NOT     // how many empty slots remain?
    // OR 
    // unsigned int num_keys; // number of valid keys in keys[]

    // NOT STANDARD PRACTICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int keys[ORDER_M];  // ORDER_M - 1 == max keys 
    Node* children[ORDER_M + 1]; // ORDER_M == max children 

    std::string values[ORDER_M]; // ORDER_M - 1 == max string data, since key and value are 1 to 1

    Node* prev;
    Node* next;



    



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

