#include <qt4/QtGui/QApplication>
#include "diskgroupsxml.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	diskgroupsxml::createXMLFile("diskgroup.xml");
	diskgroupsxml::addDiskGroup("diskgroup.xml");
	diskgroupsxml::addDiskGroupAttribute("diskgroup.xml",1,"id","hola");
	diskgroupsxml::addDiskGroupAttribute("diskgroup.xml",1,"blocksize","1024");
	diskgroupsxml::addDiskGroupAttribute("diskgroup.xml",1,"maxsize","1073741824");
	diskgroupsxml::addDiskGroupAttribute("diskgroup.xml",1,"raid","-1");
	diskgroupsxml::addDiskGroupAttribute("diskgroup.xml",1,"functional","true");
	diskgroupsxml::addDiskGroupAttribute("diskgroup.xml",1,"working","false");
	diskgroupsxml::addDiskGroupDisk("diskgroup.xml",1);
	diskgroupsxml::addDiskGroupDisk("diskgroup.xml",1);
	diskgroupsxml::addDiskGroupDisk("diskgroup.xml",1);
	diskgroupsxml::addDiskGroupDisk("diskgroup.xml",1);
	diskgroupsxml::addDiskGroupDisk("diskgroup.xml",1);
	diskgroupsxml::addDiskGroupDiskAttribute("diskgroup.xml",1,2,"ip","127.0.0.1");
	diskgroupsxml::addDiskGroupDiskAttribute("diskgroup.xml",1,1,"ip","127.0.0.1");
	diskgroupsxml::addDiskGroupDiskAttribute("diskgroup.xml",1,3,"ip","127.0.0.1");
	diskgroupsxml::addDiskGroupDiskAttribute("diskgroup.xml",1,4,"ip","127.0.0.1");
	diskgroupsxml::addDiskGroupDiskAttribute("diskgroup.xml",1,5,"ip","127.0.0.1");
	std::string mama = diskgroupsxml::getDiskGroupId("diskgroup.xml",2);
	std::cout<<mama.size()<<std::endl;
	std::cout<<mama<<std::endl;
	std::cout << "LOL: " << (mama == "" ?"true":"false") << std::endl;
	return app.exec();
}