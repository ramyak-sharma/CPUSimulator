#include "node.h"

unsigned int Node::ID = 0;

Node::Node(){
    ID++;
    m_id = ID;
}

