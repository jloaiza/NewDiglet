
#ifndef STORAGE_CLIENT
#define STORAGE_CLIENT 

#include <string>

class StorageClient
{

public:
  std::string getIP();
  std::string readBlock(int pID, int pBlock);

  int writeBlock(int pID, std::string pData);
  int writeBytes(int pID, int pBlock, int pOffset, int pSize, std::string pData);

  std::string readBytes(int pID, int pBlock, int pOffset, int pSize);

  bool isAlive(int pID);

};

#endif