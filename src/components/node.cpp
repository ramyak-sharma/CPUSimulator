#include "node.h"

unsigned int Node::ID = 0;

Node::Node(){
    ID++;
    id = ID;
}

