
#include <string>
#include "ntreenode.h"

nTreeNode::nTreeNode(iFile* pFile, std::string pName){
	_file = pFile;
	_name = pName;
	_parent = 0;
	_children = new AVLTree<nTreeNode, std::string>();
}