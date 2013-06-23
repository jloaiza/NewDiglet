#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <string>

class Comparable{

public:

    /**
     * @brief eql
     * @param arg
     * @return
     */
    virtual bool eql(Comparable* arg) = 0;

    /**
     * @brief gtr
     * @param arg
     * @return
     */
    virtual bool gtr(Comparable* arg) = 0;

    /**
     * @brief lss
     * @param arg
     * @return
     */
    virtual bool lss(Comparable* arg) = 0;

    /**
     * @brief print
     */
    virtual void print() = 0;


    /**
     * @brief name
     */
    std::string name;
};


#endif // COMPARABLE_H
