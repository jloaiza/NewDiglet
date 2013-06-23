#ifndef TREE_NODE
#define TREE_NODE


template <class t>

class TreeNode{
private:
	t* _data;
	TreeNode* _parent;
	TreeNode* _leftChild;
	TreeNode* _rightChild;
public:
	TreeNode(t* pData){
		_data = pData;
		_parent = _leftChild = _rightChild = 0;
	}

	t* getData() const {

		return _data;
	}

	TreeNode* getParent() const {
		return _parent;
	}

	TreeNode* getGrandpa() const {
		if (_parent != 0){
			return _parent->getParent();
		}
	}

	TreeNode* getLeftChild() const {
		return _leftChild;
	}

	TreeNode* getRightChild() const {
		return _rightChild;
	}

	void setData(t* pData){
		_data = pData;
	}

	void setParent(TreeNode* pNode){
		_parent = pNode;
	}

	void setRightChild(TreeNode* pNode){
		_rightChild = pNode;
	}

	void setLeftChild(TreeNode* pNode){
		_leftChild = pNode;
	}

	bool isLeftChild() const;
	bool isRightChild() const;
	bool isLeaf() const;
	bool haveBothChilds() const;
	bool haveLeftChild() const;
	bool haveRightChild() const;
};

#endif /*TREE_NODE*/

//-------------------------Declaración de los métodos------------------------------------

template <class t>
bool TreeNode<t>::isRightChild() const {
	if (_parent != 0){
		if (_parent->getRightChild() == this){
			return true;
		}
	}
	return false;
}

template <class t>
bool TreeNode<t>::isLeftChild() const {
	if (_parent != 0){
		if (_parent->getLeftChild() == this){
			return true;
		}
	}
	return false;
}

template <class t>
bool TreeNode<t>::isLeaf() const {
	return _leftChild == 0 && _rightChild == 0;
}

template <class t>
bool TreeNode<t>::haveBothChilds() const {
	return _leftChild != 0 && _rightChild != 0;
}

template <class t>
bool TreeNode<t>::haveRightChild() const{
	return _rightChild != 0;
}

template <class t>
bool TreeNode<t>::haveLeftChild() const{
	return _leftChild != 0;
}