//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//


#include "../include/keyboard.h"
#include "../include/connectFrame.h"
#include "../include/subscribeFrame.h"
#include "../include/sendFrame.h"
#include "../include/disconnectFrame.h"
#include "../include/unsubscribeFrame.h"

using namespace std;
keyboard::keyboard(BookClub &bookclub,ConnectionHandler *CH,Protocol &protocol) : bookclub(bookclub),CH(CH),protocol(protocol) {
//    this->bookclub=bookclub;
    this->receiptID=0;
}

//keyboard::keyboard(const keyboard &other) {
//
//}

void keyboard::operator()() {
//        bool wantedLogout= false;

    while(!this->protocol.isTerminated()) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        string newline = "";


        std::vector<std::string> splitmsg = split(line, " ");
        if (splitmsg[0] == "login") {
            short port = stoi(split(splitmsg[1],":")[1]);
            string host = split(splitmsg[1],":")[0];
            this->CH->setHostPort(host,port);
            if (!this->CH->connect()) {
                std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
                break;
            }
            string name = splitmsg[2];
            string password = splitmsg[3];
            this->bookclub.setName(name);
            connectFrame frame = connectFrame(host, name, password);
//            std::cout << frame.toString() << std::endl;
            newline = frame.toString();
        }
        if (splitmsg[0] == "join") {
            string destination = splitmsg[1];
            subscribeFrame frame = subscribeFrame(destination, this->bookclub.getSubID(), receiptID);
            pair<string, string> s = make_pair("join", destination);
            this->bookclub.addToReceiptMap(this->receiptID, s);
            this->bookclub.subscribe(destination);
            this->receiptID++;
//            std::cout << frame.toString() << std::endl;
            newline = frame.toString();
        }
        if (splitmsg[0] == "exit") {
            string destination = splitmsg[1];
            unsubscribeFrame frame = unsubscribeFrame(this->bookclub.getSubIDbyGenre(destination), receiptID);
            pair<string, string> s = make_pair("exit", destination);
            bookclub.addToReceiptMap(this->receiptID, s);
            this->receiptID++;
//            std::cout << frame.toString() << std::endl;
            newline = frame.toString();
        }
        if (splitmsg[0] == "add") {
            string destination = splitmsg[1];
            string book = splitmsg[2];
            for (size_t i = 3;i < splitmsg.size(); i++) {
                book = book + " " + splitmsg[i];
            }
            sendFrame frame = sendFrame(book, destination, "add", this->bookclub.getName(), "");
//            std::cout << frame.tostring() << std::endl;
            newline = frame.tostring();
        }
        if (splitmsg[0] == "borrow") {
            string destination = splitmsg[1];
            string book = splitmsg[2];
            size_t i = 3;
            for (size_t i = 3; i < splitmsg.size(); i++) {
                book = book + " " + splitmsg[i];
            }
            this->bookclub.addRequest(book);
            sendFrame frame = sendFrame(book, destination, "borrow", this->bookclub.getName(), "");
//            std::cout << frame.tostring() << std::endl;
            newline = frame.tostring();
        }
        if (splitmsg[0] == "return") {
            string destination = splitmsg[1];
            string book = splitmsg[2];
            for (size_t i = 3; i < splitmsg.size(); i++) {
                book = book + " " + splitmsg[i];
            }
//            this->bookclub.deleteBookByGenre(destination, book);
            sendFrame frame = sendFrame(book, destination, "return", this->bookclub.getName(),
                                        this->bookclub.WhoToReturn(book));
//            std::cout << frame.tostring() << std::endl;
            newline = frame.tostring();
        }
        if (splitmsg[0] == "status") {
            string destination = splitmsg[1];
            sendFrame frame = sendFrame("", destination, "status", this->bookclub.getName(), "");
//            std::cout << frame.tostring() << std::endl;
            newline = frame.tostring();
        }
        if (splitmsg[0] == "logout") {
            disconnectFrame frame = disconnectFrame(receiptID);
            pair<string, string> s = make_pair("logout", "");
            bookclub.addToReceiptMap(this->receiptID, s);
            this->receiptID++;
//            std::cout << frame.toString() << std::endl;
            newline = frame.toString();
//            wantedLogout= true;;
            this->protocol.Terminate();
        }
        int len = newline.length();
        if (!this->CH->sendLine(newline)) {
            this->protocol.Terminate();
            this->CH->close();
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        this->CH->setConnected();
        std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;

    }




}


vector<std::string> keyboard::split(string s,string delimiter) {
    std::vector<std::string> list;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

keyboard::~keyboard() {

}

keyboard &keyboard::operator=(const keyboard &other) {

}

