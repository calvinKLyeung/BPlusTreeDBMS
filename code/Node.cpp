#include "Node.h"

Node::Node(std::string s) {
    // DONE FOR YOU
    data = s;
}

Node::~Node() {
    // "DONE" FOR YOU
    //
    // This is equivalent to the default destructor the compiler will
    // generate for you. As a rule of thumb, you only need to `delete`
    // member variables that were created with `new` inside this
    // class. So, you don't need to do anything here. It could have been
    // left out of the header/impl file entirely.
}

std::string Node::getData() {
    // DONE FOR YOU
    return data;
}

bool Node::IsLeaf()
{
    // return status of node to check if node is leaf or not 
    return this->leaf;
}

int Node::getKey(unsigned int i)
{
    // get the key from keys arr at given index i 
    return this->keys[i];
}

const int *  Node::getArrayPointer() const 
{
    // allow read only access to the private keys[] arr in 
    return this->keys; 
}


// overloading operator << lets you put a Node object into an output
// stream.
std::ostream &operator << (std::ostream& out, Node node) {
    // DONE FOR YOU
    out << node.data;
    return out;
}
