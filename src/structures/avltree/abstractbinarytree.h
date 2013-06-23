#ifndef ABSTRACT_BINARY_TREE
#define ABSTRACT_BINARY_TREE

#include "treenode.h"
#include <iostream>
using namespace std;

template <class t, typename c>
class AbstractBinaryTree{
private:


protected:
	TreeNode<t>* _root;

	TreeNode<t>* insertAux(t* pData);
	TreeNode<t>* searchAux(c* pData) const;
	TreeNode<t>* eraseAux(c* pData);
	TreeNode<t>* findGreater(TreeNode<t>* pNode) const;

	void eraseLeaf(TreeNode<t>* pNode);
	void eraseWithNoLeft(TreeNode<t>* pNode);
	void eraseWithNoRight(TreeNode<t>* pNode);
	void eraseWithChilds(TreeNode<t>* pNode);

	int height(TreeNode<t>* pNode) const;

	void leftLeftRotation(TreeNode<t>* pNode);
	void rightRightRotation(TreeNode<t>* pNode);

	void inOrderTraversal(TreeNode<t>* pNode);
	void preOrderTraversal(TreeNode<t>* pNode);
	void postOrderTraversal(TreeNode<t>* pNode);
public:
	static const int IN_ORDER_TRAVERSAL = 0;
	static const int POST_ORDER_TRAVERSAL = 1;
	static const int PRE_ORDER_TRAVERSAL = 2;

	virtual void insert(t* pData) = 0;
	virtual t* search(c* pData) = 0;
	virtual t* erase(c* pData) = 0;

	void printTree(int pTraversal);

	TreeNode<t>* getRoot() const{
		return _root;
	}

};

#endif /* ABSTRACT_BINARY_TREE */

//---------------------------------------Declaración de métodos---------------------------------

template <class t, typename c>
void AbstractBinaryTree<t, c>::preOrderTraversal(TreeNode<t>* pNode){
	if (pNode != 0){
		cout<<*pNode->getData()<<endl;
		preOrderTraversal(pNode->getLeftChild());
		preOrderTraversal(pNode->getRightChild());
	}
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::inOrderTraversal(TreeNode<t>* pNode){
	if (pNode != 0){
		inOrderTraversal(pNode->getLeftChild());
		cout<<*pNode->getData()<<endl;
		inOrderTraversal(pNode->getRightChild());
	}
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::postOrderTraversal(TreeNode<t>* pNode){
	if (pNode != 0){
		postOrderTraversal(pNode->getLeftChild());
		postOrderTraversal(pNode->getRightChild());
		cout<<*pNode->getData()<<endl;
	}
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::printTree(int pTraversal){
	if (pTraversal == IN_ORDER_TRAVERSAL){
		inOrderTraversal(_root);
	} else if (pTraversal == PRE_ORDER_TRAVERSAL){
		preOrderTraversal(_root);
	} else if (pTraversal == POST_ORDER_TRAVERSAL){
		postOrderTraversal(_root);
	} else {
		cerr<<"GET SERIOUS. TRVERSAL NOT DEFINED. USE THE CLASS DEFINITIONS"<<endl;
	}
}

template <class t, typename c>
TreeNode<t>* AbstractBinaryTree<t, c>::insertAux(t* pData){
	TreeNode<t>* newNode = new TreeNode<t>(pData);
	if (_root == 0){
		_root = newNode;
	} else {
		TreeNode<t>* iNode = _root;
		bool inserted = false;
		while (!inserted){
			if (*iNode->getData() > *pData){
				if (iNode->getLeftChild() == 0){
					newNode->setParent(iNode);
					iNode->setLeftChild(newNode);
					inserted = true;
				} else {
					iNode = iNode->getLeftChild();
				}

			} else if (*iNode->getData() < *pData){
				if (iNode->getRightChild() == 0){
					newNode->setParent(iNode);
					iNode->setRightChild(newNode);
					inserted = true;
				} else {
					iNode = iNode->getRightChild();
				}
			} else {
				return 0;
			}
		}
	}
	return newNode;
}

template <class t, typename c>
TreeNode<t>* AbstractBinaryTree<t, c>::searchAux(c* pData) const{
	TreeNode<t>* iNode = _root;
	while (iNode != 0){
		if (*iNode->getData() > *pData){
			iNode = iNode->getLeftChild();
		} else if (*iNode->getData() < *pData){
			iNode = iNode->getRightChild();
		} else {
			return iNode;
		}
	}
	return 0;
}

template <class t, typename c>
TreeNode<t>* AbstractBinaryTree<t, c>::eraseAux(c* pData){
	TreeNode<t>* toErase = searchAux(pData);
	if (toErase != 0){
		std::cout<<"founded"<<std::endl;
		if (toErase->isLeaf()){
			eraseLeaf(toErase);
		} else if (toErase->haveBothChilds()){
			std::cout<<"both"<<std::endl;
			eraseWithChilds(toErase);
		} else if (toErase->haveLeftChild()){
			eraseWithNoRight(toErase);
		} else {
			eraseWithNoLeft(toErase);
		}
	}
	return toErase;
}

template <class t, typename c>
TreeNode<t>* AbstractBinaryTree<t, c>::findGreater(TreeNode<t>* pNode) const{
	pNode = pNode->getRightChild();
	while (pNode->getLeftChild() != 0){
		pNode = pNode->getLeftChild();
	}
	return pNode;
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::eraseLeaf(TreeNode<t>* pNode){
	if (pNode->isLeftChild()){
		pNode->getParent()->setLeftChild(0);
	} else if (pNode->isRightChild()) {
		pNode->getParent()->setRightChild(0);
	} else {
		_root = 0;
	}
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::eraseWithNoLeft(TreeNode<t>* pNode){

	if (pNode->isLeftChild()){
		pNode->getParent()->setLeftChild(pNode->getRightChild());

	} else if (pNode->isRightChild()) {
		pNode->getParent()->setRightChild(pNode->getRightChild());

	} else {
		_root = pNode->getRightChild();
	}
	pNode->getRightChild()->setParent(pNode->getParent());
	//Setear el replacement a parent para que pueda ser accedido posteriormente
	pNode->setParent(pNode->getRightChild());
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::eraseWithNoRight(TreeNode<t>* pNode){
	if (pNode->isLeftChild()){
		pNode->getParent()->setLeftChild(pNode->getLeftChild());
	} else if (pNode->isRightChild()) {
		pNode->getParent()->setRightChild(pNode->getLeftChild());
	} else {
		_root = pNode->getLeftChild();
	}
	pNode->getLeftChild()->setParent(pNode->getParent());
	//Setear el replacement a parent para que pueda ser accedido posteriormente
	pNode->setParent(pNode->getLeftChild());
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::eraseWithChilds(TreeNode<t>* pNode){
	TreeNode<t>* replace = findGreater(pNode);

	//Set replace atributtes

	replace->setLeftChild(pNode->getLeftChild());
	replace->getLeftChild()->setParent(replace);

	if (replace->getParent() != pNode){

		replace->getParent()->setLeftChild(replace->getRightChild());
		if (replace->getRightChild() != 0){
			replace->getRightChild()->setParent(replace->getParent());
		}

		replace->setRightChild(pNode->getRightChild());
		replace->getRightChild()->setParent(replace);
	}

	replace->setParent(pNode->getParent());

	//Set parent child
	if (pNode->isLeftChild()){
		replace->getParent()->setLeftChild(replace);
	} else if (pNode->isRightChild()){
		replace->getParent()->setRightChild(replace);
	} else {
		_root = replace;
	}

	//Setear el replacement a parent para que pueda ser accedido posteriormente
	pNode->setParent(replace);
}

template <class t, typename c>
int AbstractBinaryTree<t, c>::height(TreeNode<t>* pNode) const{
	if (pNode == 0){
		return 0;
	} else {
		int leftH = height(pNode->getLeftChild());
		int rightH = height(pNode->getRightChild());
		return leftH >= rightH ? leftH + 1 : rightH + 1;
	}
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::leftLeftRotation(TreeNode<t>* pNode){

	pNode->getParent()->setRightChild(pNode->getLeftChild());

	if (pNode->getLeftChild() != 0){
		pNode->getLeftChild()->setParent(pNode->getParent());
	}

	if (pNode->getGrandpa() != 0){
		if (pNode->getParent()->isLeftChild()){
			pNode->getGrandpa()->setLeftChild(pNode);
		} else {
			pNode->getGrandpa()->setRightChild(pNode);
		}
	}

	TreeNode<t>* nextParent = pNode->getGrandpa();
	pNode->setLeftChild(pNode->getParent());
	pNode->getParent()->setParent(pNode);
	pNode->setParent(nextParent);
}

template <class t, typename c>
void AbstractBinaryTree<t, c>::rightRightRotation(TreeNode<t>* pNode){

	pNode->getParent()->setLeftChild(pNode->getRightChild());

	if (pNode->getRightChild() != 0){
		pNode->getRightChild()->setParent(pNode->getParent());
	}

	if (pNode->getGrandpa() != 0){
		if (pNode->getParent()->isLeftChild()){
			pNode->getGrandpa()->setLeftChild(pNode);
		} else {
			pNode->getGrandpa()->setRightChild(pNode);
		}
	}

	TreeNode<t>* nextParent = pNode->getGrandpa();
	pNode->setRightChild(pNode->getParent());
	pNode->getParent()->setParent(pNode);
	pNode->setParent(nextParent);
}