#include "ntree.h"
#include "ntreenode.h"

int main()
{
	nTree* prueba = new nTree();
	nTreeNode* aux = prueba->getNode(0, "");
	std::cout << aux->getName() << std::endl;
	prueba->insert(NULL,aux,"JAJA", "");
	prueba->insert(NULL,aux,"JAJA2", "JAJA");
	prueba->insert(NULL,aux,"JAJAFile", "JAJA2");
	std::cout << prueba->getNode(aux, "JAJA")->getName()<<std::endl;
	prueba->erase(NULL,"JAJA/JAJA2/JAJAFile");
	std::cout << prueba->getNode(aux, "JAJA/JAJA2/JAJAFile")<<std::endl;
	return 0;
}