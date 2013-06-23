#ifndef BLOCKDIRECTION
#define BLOCKDIRECTION


class BlockDirection
{

private:

	std::string _IP;
	short _disk;
	short _block;
	char * OriginalDirection;
public:

	BlockDirection(char* pDir);
	char* getDirection();
	void setDirection(char* pDir);
	std::string getIP();
	short getDisk();
	short getBlock();

};


#endif /* DATABUFFER */
