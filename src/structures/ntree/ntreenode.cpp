
#include <string>
#include "ntreenode.h"


nTreeNode::nTreeNode(iFile* pFile, std::string pName, std::string pUser){
	_file = pFile;
	_name = pName;
	_user = pUser;
	_parent = 0;
	_children = new AVLTree<nTreeNode, std::string>();	
}

std::string nTreeNode::getFilesRep(){
	return getFilesRepAux(_children->getRoot());
}

std::string nTreeNode::getFilesRepAux(TreeNode<nTreeNode>* pNode){
	if (pNode == 0){
		return "";
	}
	std::string left = getFilesRepAux(pNode->getLeftChild());
	std::string current = pNode->getData()->getName();
	std::string right = getFilesRepAux(pNode->getRightChild());
	return right + std::string(left != ""?" ":"") + current + std::string(" ") + left + std::string(right != ""?" ":"");
}