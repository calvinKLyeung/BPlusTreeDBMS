#include "Node.h"

Node::Node() {

    this->node_identifier = "";
    this->level = 0; 
    this->leaf = true; 
    this->slots = 0; 
    for (unsigned int i = 0; i < ORDER_M; ++i)
    {   
        this->keys[i] = 0;
    }
    for (unsigned int i = 0; i < ORDER_M; ++i)
    {
        this->values[i] = "";
    }
    for (unsigned int i = 0; i < ORDER_M + 1; ++i)
    {   
        this->children[i] = NULL;
    }

    this->next = NULL;
    this->prev = NULL;


}

Node::Node(std::string _node_identifier, unsigned int _level, bool _leaf, unsigned int _slots, 
            int _keys[])
            :
            node_identifier{_node_identifier},
            level{_level},
            leaf{_leaf},
            slots{_slots}
{
     for (unsigned int i=0; i<_slots;++i)
    {
        keys[i] = _keys[i];
    }

    for (unsigned int i = 0; i < ORDER_M + 1; ++i)
    {   
        this->children[i] = NULL;
    }
    this->next = NULL;
    this->prev = NULL;
}




Node::Node(std::string _node_identifier, unsigned int _level, bool _leaf, unsigned int _slots, 
            int _keys[], std::string _values[])
            :
            node_identifier{_node_identifier},
            level{_level},
            leaf{_leaf},
            slots{_slots}
{
    // this->node_identifier = _node_identifier;
    // this->level = _level;
    // this->leaf = _leaf;
    // this->slots = _slots;
    for (unsigned int i=0; i<_slots;++i)
    {
        keys[i] = _keys[i];
    }
    for (unsigned int i=0; i<_slots;++i)
    {
        values[i] = _values[i];
    }

    for (unsigned int i = 0; i < ORDER_M + 1; ++i)
    {   
        this->children[i] = NULL;
    }


    this->next = NULL;
    this->prev = NULL;

}

Node::Node(std::string _node_identifier, unsigned int _level, bool _leaf, unsigned int _slots, 
            int _keys[], std::string _values[], Node* _children[])
            :
            node_identifier{_node_identifier},
            level{_level},
            leaf{_leaf},
            slots{_slots}
{

    for (unsigned int i=0; i<_slots;++i)
    {
        keys[i] = _keys[i];
    }
    for (unsigned int i=0; i<_slots;++i)
    {
        values[i] = _values[i];
    }
    for (unsigned int i=0; i<_slots + 1;++i)
    {
        children[i] = _children[i];
    }

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


void Node::clear()
{
    this->node_identifier = "";
    this->level = 0; 
    this->leaf = true; 
    this->slots = 0; 
    for (unsigned int i = 0; i < ORDER_M; ++i)
    {   
        this->keys[i] = 0;
    }
    for (unsigned int i = 0; i < ORDER_M + 1; ++i)
    {   
        this->children[i] = NULL;
    }
}


std::string Node::getNodeIdentifier() {
    // DONE FOR YOU
    return node_identifier;
}

void Node::setNodeIdentifier(std::string node_identifier)
{
    this->node_identifier = node_identifier;
}

unsigned int Node::getLevel()
{
    return this->level;
}

void Node::setLevel(unsigned int level)
{
    this->level = level;
}


bool Node::getLeaf()
{
    // return status of node to check if node is leaf or not 
    return this->leaf;
}

void Node::setLeaf(bool leaf)
{
    this->leaf = leaf;
}


int Node::getKeyByIndex(unsigned int i)
{
    // get the key from keys arr at given index i 
    return this->keys[i];
}

int Node::getIndexByKey(int key)
{
    // not found == -1 
    int index = -1; 
    for (unsigned int i=0; i<this->getSlots(); ++i)
    {
        if (this->accessKeys()[i] == key)
        {
            index = i; 
            break; 
        }
    }
    return index; 
}

int Node::getIndexByChildPointer(Node* child)
{   
    int index = -1;
    for (unsigned int i = 0; i < this->getSlots() + 1; ++i)
    {
        if (this->accessChildren()[i] == child)
        {
            index = i;
            break;
        }
    }
    return index; 
}



unsigned int Node::getSlots()
{
    return this->slots;
}

void Node::setSlots(unsigned int slots)
{
    this->slots = slots;
}

unsigned int Node::getNumOfChildren()
{   
    unsigned int ret = 0; 
    for (unsigned int i=0; i < this->getSlots() + 1; ++i)
    {
        if (this->accessChildren()[i] != NULL)
        {
            ret++; 
        }
    }
    return ret; 
}


Node* Node::getTheRemainingChild()
{
    for(unsigned int i=0; i < this->getSlots() + 1; ++i)
    {
        if (this->accessChildren()[i] != NULL)
        {
            return this->accessChildren()[i];
        }
    }
    return NULL;
}

bool Node::hasTooFewValuesOrPointersRemain()
{
    
    bool ret = false;

    // if non-leaf internal nodes, has children < ⌈ORDER_M / 2⌉
    if (this->getLeaf() != true) 
    {
        if (this->getNumOfChildren() < (unsigned int)ceil(ORDER_M / 2.0))
        {
            ret = true; 
        }
    }
    // else if leaf nodes, has Keys <  ⌈(ORDER_M - 1) / 2⌉
    else
    {
        if (this->getSlots() < (unsigned int)ceil((ORDER_M - 1) / 2.0))
        {
            ret = true;
        }
    }
    return ret; 
}






void Node::setPrev(Node* node)
{
    // set the node's prev pointer 
    this->prev = node;
}

Node* Node::getPrev()
{
    // get the prev pointer from the invoking Node 
    return this->prev;
}



void Node::setNext(Node* node)
{
    // set the node's next pointer 
    this->next = node;
}

Node* Node::getNext()
{
    // get the next pointer from the invoking Node 
    return this->next;
}




int* Node::accessKeys()
{
    // allow access to the private keys[] arr 
    return this->keys; 
}

Node** Node::accessChildren()
{
    // allow acces to the private children[] arr of pointers 
    return this->children;
}

std::string* Node::accessValues()
{
    // allow access to the private keys[] arr 
    return this->values; 
}



// overloading operator << lets you put a Node object into an output
// stream.
std::ostream &operator << (std::ostream& out, Node node) {
    for (unsigned int i = 0; i < node.getSlots(); ++i)
    {
        out << node.accessKeys()[i] << " : " << node.accessValues()[i] << "\n"; 
    }

    // out << node.node_identifier;
    return out;
}
