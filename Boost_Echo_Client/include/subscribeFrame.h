//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_SUBSCRIBEFRAME_H
#define SPL_A3_SUBSCRIBEFRAME_H


#include <string>

using namespace std;

class subscribeFrame {
public:
    subscribeFrame(string genre,int id, int receiptId);
    string toString();
private:
    string msg;
};



#endif //SPL_A3_SUBSCRIBEFRAME_H
