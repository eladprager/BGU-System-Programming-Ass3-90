//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_PROTOCOL_H
#define SPL_A3_PROTOCOL_H


#include "connectionHandler.h"
#include "BookClub.h"

using namespace std;

class Protocol {
private:
    ConnectionHandler *connectionHandler;
    BookClub &bookclub;
    bool shouldTerminate;
public:
    Protocol(ConnectionHandler *connectionHandler,BookClub &bookclub);
//    Protocol(const Protocol& Protocol);
//    Protocol& operator=(const Protocol& Protocol);
    void operator()();
    void Terminate();
    bool isTerminated();

    vector<std::string> split(string s,string delimiter);
};


#endif //SPL_A3_PROTOCOL_H
