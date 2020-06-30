//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include <iostream>
#include "../include/subscribeFrame.h"

subscribeFrame::subscribeFrame(string genre, int id, int receiptId) {
    this->msg="SUBSCRIBE\ndestination:"+genre+"\nid:"+to_string(id)+"\nreceipt:"+to_string(receiptId)+"\n\n^@";

}

string subscribeFrame::toString() {
    return this->msg;
}
