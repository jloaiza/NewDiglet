
#include <string>
#include <iostream>
#include "ntreenode.h"
#include "ifile.h"
#include "../simplelist/simplelist.h"


nTreeNode::nTreeNode(Comparable* pPath, std::string pUser)
{

}

void nTreeNode::addChild(nTreeNode pNode)
{

}

iFile* nTreeNode::getChild(std::string pName)
{

}

/*
SimpleList* nTreeNode::getChildrenList(){
    return _children;
}
*/

bool nTreeNode::searchChild(std::string pName)
{
    return _children->search(pName);
}	
	
void nTreeNode::eraseChild(std::string pName)
{
    /** TODO **/
}


void nTreeNode::print()
{
	_file->print();
}
