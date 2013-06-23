#ifndef AVL_TREE
#define AVL_TREE

#include "abstractbinarytree.h"


template <class t, typename c>
class AVLTree : public AbstractBinaryTree<t, c>{
public:
	AVLTree();
	void insert(t* pData);
	t* erase(c* pData);
	t* search(c* pData);
private:
	void leftRightRotation(TreeNode<t>* pNode);
	void rightLeftRotation(TreeNode<t>* pNode);
	void balanceTree(TreeNode<t>* pNode);
	int balanceFactor(TreeNode<t>* pNode);
};

#endif /*AVL_TREE*/

//-----------------------------Declaración de metodos--------------------------------------------

template <class t, typename c>
t* AVLTree<t, c>::erase(c* pData){
	TreeNode<t>* erased = this->eraseAux(pData);
	if (erased != 0){
		balanceTree(erased->getParent());
		return erased->getData();
	} else {
		return 0;
	}	
}

template <class t, typename c>
t* AVLTree<t, c>::search(c* pData){
	TreeNode<t>* searched = this->searchAux(pData);
	if (searched != 0){
		return searched->getData();
	} else {
		return 0;
	}
}

template <class t, typename c>
void AVLTree<t, c>::insert(t* pData){
	TreeNode<t>* inserted = this->insertAux(pData);
	if (inserted != 0){
		balanceTree(inserted);
	}
}

template <class t, typename c>
AVLTree<t, c>::AVLTree(){
	this->_root = 0;
}

template <class t, typename c>
void AVLTree<t, c>::leftRightRotation(TreeNode<t>* pNode){
	if (pNode->getGrandpa() == this->_root){
		this->_root = pNode;
	}
	this->leftLeftRotation(pNode);
	this->rightRightRotation(pNode);
}

template <class t, typename c>
void AVLTree<t, c>::rightLeftRotation(TreeNode<t>* pNode){
	if (pNode->getGrandpa() == this->_root){
		this->_root = pNode;
	}
	this->rightRightRotation(pNode);
	this->leftLeftRotation(pNode);
}

template <class t, typename c>
int AVLTree<t, c>::balanceFactor(TreeNode<t>* pNode){
	if (pNode == 0){
		return 0;
	}
	int lH = this->height(pNode->getLeftChild());
	int rH = this->height(pNode->getRightChild());
	return rH - lH;
}

template <class t, typename c>
void AVLTree<t, c>::balanceTree(TreeNode<t>* pNode){

	bool balanced = false;

	while (pNode != 0 && !balanced){

		int currentH = balanceFactor(pNode);

		int parentH = balanceFactor(pNode->getParent());

		if (currentH == 1){

			if (parentH == 2){
				this->leftLeftRotation(pNode);
				balanced = true;
			} else if (parentH == -2 ){
				leftRightRotation(pNode->getRightChild());
				balanced = true;
			} else {
				pNode = pNode->getParent();
			}

		} else if (currentH == -1){

			if (parentH == 2){
				rightLeftRotation(pNode->getLeftChild());
				balanced = true;
			} else if (parentH == -2 ){
				this->rightRightRotation(pNode);
				balanced = true;
			} else {
				pNode = pNode->getParent();
			}

		} else {

			if (currentH >= 2){
				pNode = pNode->getRightChild();
			} else if (currentH <= -2){
				pNode = pNode->getLeftChild();
			} else {
				pNode = pNode->getParent();
			}

		}
	}
	if (pNode != 0 && pNode->getParent() == 0){
		this->_root = pNode;
	}
}