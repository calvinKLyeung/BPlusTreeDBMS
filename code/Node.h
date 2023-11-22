#ifndef NODE_H__
#define NODE_H__

#include <iostream>
#include <memory>

// using namespace std;

#define ORDER_M 5

class Node {
private:
    std::string data;
    unsigned int level;
    bool leaf;


    unsigned int slots; // how many empty slots remain?
    // OR 
    unsigned int num_keys; // number of valid keys in keys[]


    int keys[ORDER_M];
    std::shared_ptr<Node> children[ORDER_M + 1];

    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;



public:
    // Public Node members in this block are implemented for you.
    Node(std::string s);
    ~Node();
    std::string getData();
    bool IsLeaf();
    int getKey(unsigned int i);

    const int * Node::getArrayPointer() const;

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

