#ifndef DOUBLELINKEDLIST
#define DOUBLELINKEDLIST

#include "listnode.h"


template <class t, typename c>
class DoubleLinkedList{

public:

	DoubleLinkedList(){
		_head = _tail = 0;
	}

	void insertCrecient(t* pData);
	void insertDecrecient(t* pData);
	void insertEnd(t* pData);
	void insertStart(t* pData);

	t* search(c* pData);
	t* erase(c* pData);

private:
	ListNode<t>* searchAux(c* pDataDummy);
	ListNode<t>* _head;
	ListNode<t>* _tail;
};


//--------------Definición de los métodos--------------------------------------

template <class t, typename c>
void DoubleLinkedList<t, c>::insertCrecient(t* pData){
	ListNode<t>* newNode = new ListNode<t>(pData);
	if (_head == 0){
		_head = _tail = newNode;

	} else if (*_head.getData() > *pData){
		newNode->setNext(_head);
		_head->setPrevious(newNode);
		_head = newNode;

	} else if (*_tail->getData < *pData) {
		newNode->setPrevious(_tail);
		_tail->setNext(newNode);
		_tail = newNode;

	}else {
		ListNode<t>* iNode = _head;
		while (iNode != 0){
			if (*iNode->getData() > *pData){
				newNode->setNext(iNode);
				newNode->setPrevious(iNode->getPrevious());
				iNode->getPrevious()->setNext(iNode);
				iNode->getNext()->setPrevious(iNode);
				return;
			}
			iNode = iNode->getNext();
		}
	}
}

template <class t, typename c>
void DoubleLinkedList<t, c>::insertDecrecient(t* pData){
	ListNode<t>* newNode = new ListNode<t>(pData);
	if (_head == 0){
		_head = _tail = newNode;

	} else if (*_head.getData() < *pData){
		newNode->setNext(_head);
		_head->setPrevious(newNode);
		_head = newNode;

	} else if (*_tail->getData > *pData) {
		newNode->setPrevious(_tail);
		_tail->setNext(newNode);
		_tail = newNode;

	}else {
		ListNode<t>* iNode = _head;
		while (iNode != 0){
			if (*iNode->getData() < *pData){
				newNode->setNext(iNode);
				newNode->setPrevious(iNode->getPrevious());
				iNode->getPrevious()->setNext(iNode);
				iNode->getNext()->setPrevious(iNode);
				return;
			}
			iNode = iNode->getNext();
		}
	}
}

template <class t, typename c>
void DoubleLinkedList<t, c>::insertStart(t* pData){
	ListNode<t>* newNode = new ListNode<t>(pData);
	if (_head == 0){
		_head = _tail = newNode;
	} else {
		newNode->setNext(_head);
		_head->setPrevious(newNode);
		_head = newNode;
	}
	
}

template <class t, typename c>
void DoubleLinkedList<t, c>::insertEnd(t* pData){
	ListNode<t>* newNode = new ListNode<t>(pData);
	if (_head == 0){
		_head = _tail = newNode;
	} else {
		newNode->setPrevious(_tail);
		_tail->setNext(newNode);
		_tail = newNode;
	}
	
}

template <class t, typename c>
ListNode<t>* DoubleLinkedList<t, c>::searchAux(c* pData){
	ListNode<t>* iNode = _head;
	while (iNode != 0 && *iNode->getData() != *pData){
		iNode = iNode->getNext();
	}
	return iNode;
}

template <class t, typename c>
t* DoubleLinkedList<t, c>::search(c* pData){
	ListNode<t>* searched = searchAux(pData);
	return searched != 0 ? searched->getData() : 0;
}

template <class t, typename c>
t* DoubleLinkedList<t, c>::erase(c* pData){
	ListNode<t>* toErase = searchAux(pData);
	if (toErase != 0){

		if (_head == _tail && toErase == _head){
			_head = _tail = 0;
			
		} else if (toErase == _head){
			toErase->getNext()->setPrevious(0);
			_head = toErase->getNext();

		} else if (toErase == _tail){
			toErase->getPrevious()->setNext(0);
			_tail = toErase->getPrevious();

		} else {
			toErase->getPrevious()->setNext(toErase->getNext());
			toErase->getNext()->setPrevious(toErase->getPrevious);
		}

		t* tmp = toErase->getData();
		delete toErase;
		return tmp;
			
	} else{
		return 0;
	}
}

#endif /* DOUBLELINKEDLIST */