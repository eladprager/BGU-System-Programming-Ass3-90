//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/disconnectFrame.h"

disconnectFrame::disconnectFrame(int receiptId) {
    this->msg="DISCONNECT\nreceipt:"+to_string(receiptId)+"\n\n^@";
}

string disconnectFrame::toString() {
    return this->msg;
}
