#ifndef NODE_H__
#define NODE_H__

#include <iostream>
#include <memory>
#include <vector>

// using namespace std;

#define ORDER_M 5

class Node {
private:
    std::string data;
    unsigned int level;
    bool leaf;


    unsigned int slots;  // number of valid keys in keys[]     BUT NOT     // how many empty slots remain?
    // OR 
    // unsigned int num_keys; // number of valid keys in keys[]

    int keys[ORDER_M] = {0};
    Node* children[ORDER_M + 1] = {NULL};

    Node* prev = NULL;
    Node* next = NULL;



public:
    // Public Node members in this block are implemented for you.
    Node();
    Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, 
        int _keys[], Node* _children[]);

    ~Node();
    std::string getData();
    bool IsLeaf();
    int getKey(unsigned int i);
    unsigned int getSlots();

    // const int * accessKeysArray() const;
    int* accessKeysArray();
    Node* accessChildren();

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

