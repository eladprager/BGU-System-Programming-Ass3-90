//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include <iostream>
#include "../include/sendFrame.h"

sendFrame::sendFrame(string book, string destination, string command, string name, string  secondname): book(book), destination(destination), command(command), name(name),second_name(secondname) {
    this->msg="SEND\ndestination:"+destination+"\n\n";
    if (command=="add"){
        this->msg=msg+name+" has added the book "+book+"\n^@";
    }
    if (command=="borrow"){
        this->msg=msg+name+" wish to borrow "+book+"\n^@";
    }
    if (command=="has"){
        this->msg=msg+name+" has "+book+"\n^@";
    }
    if (command=="taking"){
        this->msg=msg+"Taking "+book+" from "+second_name+"\n^@";
    }
    if (command=="return"){
        this->msg=msg+"Returning "+book+" to "+second_name+"\n^@";
    }
    if (command=="status"){
        this->msg=msg+"book status\n^@";
    }
    if (command==":"){
        this->msg=msg+name+":";
    }
}

string sendFrame::tostring() {
    return this->msg;
}


