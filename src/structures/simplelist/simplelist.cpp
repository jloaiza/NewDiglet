#include "simplelist.h"
#include <iostream>
#include "node.h"
#include "../../include/comparable.h"

SimpleList::SimpleList()
{
	_size = 0;
    _head = NULL;
}

void SimpleList::insert(Comparable *pData)
{
    Node* newNode = new Node(pData);
    newNode->next = _head;
	_head = newNode;
	_size++;
}

bool SimpleList::search(std::string pName)
{
    Node* iterNode = _head;
    while (iterNode != 0)
    {
        if ((iterNode->data)->name.compare(pName) == 0)
        {
            return true;
        }
        iterNode = iterNode->next;
    }
    return false;
}


void SimpleList::erase(Comparable *pData)
{
    if (_head == 0) { /* Nothing to erase */ }
    else 
    {
        if (_size == 1 && pData->eql(_head->data))
        {
            Node* tmp = _head->next;
            _head->next = NULL; 
            _head = tmp;
        }
        else 
        {
            Node* iterNode = _head;
            while( iterNode->next != NULL && !((iterNode->next)->data)->eql(pData) )
            {
                iterNode = iterNode->next;
            }
            Node* tmp = iterNode->next;
            iterNode->next = tmp->next;
            tmp->next = NULL;
        }
        _size--;
	}
}

Comparable* SimpleList::get(std::string pName)
{
    Node* iterNode = _head;
    while (iterNode != NULL)
    {
        if ((iterNode->data)->name.compare(pName) == 0)
        {
            return iterNode->data;
        }
        iterNode = iterNode->next;
    }
    return 0;
}

void SimpleList::print()
{
    Node* iterNode = _head;
    if (_head == NULL)
    {
        std::cout << "Empty List";
	}
    else
	{
        while(iterNode != NULL)
		{
            (iterNode->data)->print();
            iterNode = iterNode->next;
		}	
	}
	std::cout << std::endl;
}
