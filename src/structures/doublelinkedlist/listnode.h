#ifndef LISTNODE
#define LISTNODE

template <class t>
class ListNode{

public:

	ListNode(t* pData){
		_data = pData;
		_next = 0;
		_previous = 0;
	}

	t* getData() const{
		return _data;
	}

	void setData(t* pData){
		_data = pData;
	}

	ListNode<t>* getNext() const{
		return _next;
	}

	ListNode<t>* getPrevious() const{
		return _previous;
	}

	void setNext(ListNode<t>* pNode){
		_next = pNode;
	}

	void setPrevious(ListNode<t>* pNode){
		_previous = pNode;
	}


private:
	t* _data;
	ListNode<t>* _next;
	ListNode<t>* _previous;
};

#endif /* LISTNODE */