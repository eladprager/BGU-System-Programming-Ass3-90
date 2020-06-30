//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include <iostream>
#include "../include/unsubscribeFrame.h"

unsubscribeFrame::unsubscribeFrame(int id, int receiptId) {
    this->msg="UNSUBSCRIBE\nid:"+to_string(id)+"\nreceipt:"+to_string(receiptId)+"\n\n^@";
}

string unsubscribeFrame::toString() {
    return this->msg;
}
