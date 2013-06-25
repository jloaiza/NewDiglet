#ifndef IFILE_H
#define IFILE_H

#include <string>
#include <iostream>

class iFile
{

private:

    std::string _diskID;
    int _regCount;
    int _startBlock;

public:

    iFile(std::string pDisk, int pStartBlock){
        _regCount = 0;
        _startBlock = pStartBlock;
        _diskID = pDisk;
    }

    void addRegCount() {
        _regCount++;
    }

    void removeRegCount() {
        if (_regCount == 0){
            std::cout<<"Error. Removing more registers than posibles. Check algorithms.";
        }
        _regCount--;
    }

    int getRegCount() const {
        return _regCount;
    }

    std::string getDisk() const {
        return _diskID;
    }

    void setDisk(std::string pDisk){
        _diskID = pDisk;
    }

    int getStartBlock() const{
        return _startBlock;
    }

    void setStartBlock(int pBlock){
        _startBlock = pBlock;
    }

};

#endif // IFILE_H
