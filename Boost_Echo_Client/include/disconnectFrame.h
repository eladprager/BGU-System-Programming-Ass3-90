//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_DISCONNECTFRAME_H
#define SPL_A3_DISCONNECTFRAME_H

#include <string>

using namespace std;

class disconnectFrame {
public:
    disconnectFrame(int receiptId);
    string toString();
private:
    string msg;
};


#endif //SPL_A3_DISCONNECTFRAME_H
