
//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_CONNECTFRAME_H
#define SPL_A3_CONNECTFRAME_H


#include <string>

using namespace std;

class connectFrame{
private:
    string msg;
public:
    connectFrame(string host,string name,string password);
    string toString();
};



#endif //SPL_A3_CONNECTFRAME_H
