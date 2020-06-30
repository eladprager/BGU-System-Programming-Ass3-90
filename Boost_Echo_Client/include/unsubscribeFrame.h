//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_UNSUBSCRIBEFRAME_H
#define SPL_A3_UNSUBSCRIBEFRAME_H


#include <string>

using namespace std;

class unsubscribeFrame {
public:
    unsubscribeFrame(int id, int receiptId);
    string toString();
private:
    string msg;
};


#endif //SPL_A3_UNSUBSCRIBEFRAME_H
