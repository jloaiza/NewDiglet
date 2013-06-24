
#include <string>
#include "ntreenode.h"

nTreeNode::nTreeNode(iFile* pFile, std::string pName, std::string pUser){
	_file = pFile;
	_name = pName;
	_user = pUser:
	_parent = 0;
	_children = new AVLTree<nTreeNode, std::string>();
}