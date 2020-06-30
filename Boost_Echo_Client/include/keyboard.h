//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_KEYBOARD_H
#define SPL_A3_KEYBOARD_H

#include "connectionHandler.h"
#include "BookClub.h"
#include "protocol.h"
#include <vector>
#include <string>

using namespace std;

class keyboard {
private:
    BookClub &bookclub;
    ConnectionHandler *CH;
    Protocol &protocol;
    int receiptID;
public:
    keyboard(BookClub &bookclub,ConnectionHandler *CH,Protocol &protocol);
    void operator()();
    virtual ~keyboard();
    keyboard& operator=(const keyboard& other);
    vector<string> split(string s,string delimiter);
};


#endif //SPL_A3_KEYBOARD_H
