#import "datanode.h"

void DataNode::releaseDependencyList(){
	DataNode* iNode = this;
	while (iNode != 0){
		DataNode* tmp = iNode->getNext();
		delete iNode;
		iNode = tmp;
	}
}
