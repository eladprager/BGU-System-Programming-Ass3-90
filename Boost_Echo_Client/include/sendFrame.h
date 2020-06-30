//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL_A3_SENDFRAME_H
#define SPL_A3_SENDFRAME_H


#include <string>
#include <boost/algorithm/string/split.hpp>
#include <vector>

using namespace std;


class sendFrame {
private:
    string destination;
    string name;
    string second_name;
    string book;
    string command;
    vector<string> message;
    string msg;
    string statusBooks;

public:

    sendFrame(string book, string destination, string command,string name,string secondname);
    string tostring();
};



#endif //SPL_A3_SENDFRAME_H
