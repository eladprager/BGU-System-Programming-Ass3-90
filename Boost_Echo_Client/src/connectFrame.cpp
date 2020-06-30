//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include <iostream>
#include "../include/connectFrame.h"


connectFrame::connectFrame(string host,string name,string password){
    this->msg="CONNECT\naccept-version:1.2\nhost:" +host+"\nlogin:"+name+"\npasscode:"+password+"\n\n^@";
}

string connectFrame::toString() {
    return this->msg;
}
