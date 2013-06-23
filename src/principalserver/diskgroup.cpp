#include "diskroup.h"

bool DiskGroup::operator==(std::string& pID){
	return _id == pID;
}

bool DiskGroup::operator>(std::string& pID){
	return _id > pID;
}

bool DiskGroup::operator>=(std::string& pID){
	return _id >= pID;
}

bool DiskGroup::operator<(std::string& pID){
	return _id < pID;
}

bool DiskGroup::operator<=(std::string& pID){
	return _id <= pID;
}

bool DiskGroup::operator!=(std::string& pID){
	return _id != pID;
}

bool DiskGroup::operator==(DiskGroup& pDiskGroup){
	return _id == pDiskGroup.getID();
}

bool DiskGroup::operator>(DiskGroup& pDiskGroup){
	return _id > pDiskGroup.getID();
}
bool DiskGroup::operator>=(DiskGroup& pDiskGroup){
	return _id >= pDiskGroup.getID();
}

bool DiskGroup::operator<(DiskGroup& pDiskGroup){
	return _id < pDiskGroup.getID();
}

bool DiskGroup::operator<=(DiskGroup& pDiskGroup){
	return _id <= pDiskGroup.getID();
}

bool DiskGroup::operator!=(DiskGroup& pDiskGroup){
	return _id != pDiskGroup.getID();
}

