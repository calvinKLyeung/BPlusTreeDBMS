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
    // Public Node members in this block are implemented for you.
    Node();
    Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, 
        int _keys[]);

    Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, 
            int _keys[], Node* _children[]);

    ~Node();

    void clear();

    std::string getNodeIdentifier();
    void setNodeIdentifier(std::string data);

    unsigned int getLevel();
    void setLevel(unsigned int level);

    bool getLeaf();
    void setLeaf(bool leaf);

    int getKeyByIndex(unsigned int i);
    int getIndexByKey(int key);

    int getIndexByChildPointer(Node* child);

    unsigned int getSlots();
    void setSlots(unsigned int slots);

    unsigned int getNumOfChildren();
    Node* getTheRemainingChild();
    bool hasTooFewValuesOrPointersRemain();

    void setPrev(Node* node);
    Node* getPrev();
    void setNext(Node* node);
    Node* getNext();

    // const int * accessKeys() const;
    int* accessKeys();
    Node** accessChildren();
    std::string* accessValues();



    // Have you ever wondered when you say cout << "hello world!" << endl; what <<
    // means? how is it implemented? these are operator methods that you can
    // define for your classes. Bellow is an example on how you can define <<
    // operator for this class and here we choose to define it as passing the data
    // of current node in string formate to the stream, which could later be like
    // Node mynode;
    // cout << mynode;
    // and that would print the data of the node.
    // you can define similar operators like +,-,* for you classes and define what
    // it means to sum two of this class's objects.
    friend std::ostream &operator<<(std::ostream &out, Node node);


};

#endif // NODE_H__

