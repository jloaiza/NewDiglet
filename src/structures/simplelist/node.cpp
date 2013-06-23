
#include "node.h"

Node::Node(Comparable *pData) {
    data = pData;
    next = NULL;
}

void Node::print() {
    data->print();
}
