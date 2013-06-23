
#ifndef NODE_H
#define NODE_H

#include "../../include/comparable.h"

class Node {

public:
    Comparable* data;
    Node* next;
	
    Node(Comparable* pData);
	void print();
};

#endif
