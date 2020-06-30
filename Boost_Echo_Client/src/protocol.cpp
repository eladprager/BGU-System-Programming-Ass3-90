//
// Created by eladpr@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/protocol.h"
#include "../include/sendFrame.h"


using namespace std;
//using namespace boost;

Protocol::Protocol(ConnectionHandler *connectionHandler,BookClub &bookclub) : bookclub(bookclub), connectionHandler(connectionHandler){
    this->shouldTerminate=false;
}

//Protocol::Protocol(const Protocol &Protocol) {
//
//}

//Protocol &Protocol::operator=(const Protocol &Protocol) {
//    return <#initializer#>;
//}

void Protocol::operator()() {
    while(!this->shouldTerminate) {
        while(!connectionHandler->isConnected()){
        }
        std::string answer;
        if (!connectionHandler->getLine(answer)) {
            this->Terminate();
            connectionHandler->close();
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }


        std::cout << "\n" + answer + "\n" << std::endl;
        vector<string> splitmsg = split(answer, "\n");
        bool added = false;
        if (splitmsg.size() == 0) {

        }
        if (splitmsg[0].compare("CONNECTED") == 0) {
            std::cout << "Login successful" << std::endl;;

        }

        if (splitmsg[0].compare("RECEIPT") == 0) {
            vector<string> splitmsg1 = split(splitmsg[1], ":");
            int index = stoi(splitmsg1[1]);
            string command = this->bookclub.getCommandByIndex(index);
            string destination = this->bookclub.getDestinationByIndex(index);
            if (command == "join") {
                std::cout << "Joined club " + destination << std::endl;
            }
            if (command == "exit") {
                std::cout << "Exit club " + destination << std::endl;;
            }
            if (command == "logout") {
                connectionHandler->setDisconnect(2);
            }
        }

        if (splitmsg[0].compare("ERROR") == 0) {
            connectionHandler->increaseDisconnect();
        }

        if (splitmsg[0].compare("MESSAGE") == 0) {
            vector<string> splitmsg2 = split(splitmsg[5], " ");
            if (splitmsg2.size() > 2 && splitmsg2[2] == "added") {
                added = true;
                string destination = split(splitmsg[3], ":")[1];
                string book = splitmsg2[5];
                for (size_t i = 6; i < splitmsg2.size(); i++) {
                    book = book + " " + splitmsg2[i];
                }
                if(bookclub.getName()== splitmsg2[0]) {
                    this->bookclub.addBookByGenre(destination, book);
                }
            }
            if (splitmsg2.size() > 2 && splitmsg2[3] == "borrow") {
                string genre = split(splitmsg[3], ":")[1];
                vector<string> splitmsgBorrow = split(splitmsg[5], " ");
                string book = splitmsgBorrow[4];
                for (size_t i = 5; i < splitmsgBorrow.size(); i++) {
                    book = book + " " + splitmsgBorrow[i];
                }
                if (this->bookclub.deleteBookByGenre(genre, book)) {
                    sendFrame frame = sendFrame(book, genre, "has", this->bookclub.getName(), this->bookclub.getName());
                    string toSend = frame.tostring();
                    int len = toSend.size();
                    if (!connectionHandler->sendLine(toSend)) {
                        this->Terminate();
                        connectionHandler->close();
                        std::cout << "Disconnected. Exiting...\n" << std::endl;
                        break;
                    }
                }

            }
            if (splitmsg2.size() > 2 && splitmsg2[1] == "has" && splitmsg2[2] != "added") {
                string genre = split(splitmsg[3], ":")[1];
                string secondname = splitmsg2[0];
                string book = splitmsg2[2];
                for (size_t i = 3;i < splitmsg2.size();i++) {
                    book = book + " " + splitmsg2[i];
                }
                if (this->bookclub.containsRequest(book)) {
                    sendFrame frame = sendFrame(book, genre, "taking", this->bookclub.getName(), secondname);
                    string toSend = frame.tostring();
                    int len = toSend.size();
                    if (!connectionHandler->sendLine(toSend)) {
                        this->Terminate();
                        connectionHandler->close();
                        std::cout << "Disconnected. Exiting...\n" << std::endl;
                        break;
                    }
                }
//            check for subid in map if yes send fame i have book and delte it
            }
            if (splitmsg2[0] == "Taking") {
                string genre = split(splitmsg[3], ":")[1];
                int j = 0;
                for (size_t i = 0; i < splitmsg2.size(); i++) {
                    if (splitmsg2.at(i) == "from") {
                        j = i;
                        break;
                    }
                }
                string book = splitmsg2[1];
                for (size_t k = 2; k < j; k++) {
                    book = book + " " + splitmsg2[k];
                }
                string secondname = splitmsg2[j + 1];
                if (this->bookclub.containsRequest(book)) {
//                sendFrame frame = sendFrame(book, genre, "taking", this->bookclub.getName(), secondname);
//                    this->bookclub.addBookByGenre(genre, book);
                    this->bookclub.deleteRequest(book);
                    this->bookclub.borrow(book, secondname);
                    this->bookclub.addBookByGenre(genre, book);
                }
            }
            if (splitmsg2[0] == "Returning") {
                string genre = split(splitmsg[3], ":")[1];
                int j = 0;
                for (size_t i = 0; i < splitmsg2.size(); i++) {
                    if (splitmsg2.at(i) == "to") {
                        j = i;
                        break;
                    }
                }
                string book = splitmsg2[1];
                for (size_t k = 2; k < j; k++) {
                    book = book + " " + splitmsg2[k];
                }
                string secondname = splitmsg2[j + 1];

                if (this->bookclub.AmItheBorrower(book,secondname)) {
                    this->bookclub.deleteFromBorrowMap(book);
                    this->bookclub.deleteBookByGenre(genre,book);
                }
                if (this->bookclub.getName() == secondname) {
                    this->bookclub.addBookByGenre(genre, book);
                }

            }
            if (splitmsg2.size() > 1 && splitmsg2[1] == "status") {
                string genre = split(splitmsg[3], ":")[1];
                vector<string> tmp = this->bookclub.getBooksByGenre(genre);
                if(!tmp.empty()) {
                    string books = tmp[0];
                    for (size_t i = 1; i < tmp.size(); i++) {
                        books = books + ", " + tmp[i];
                    }
                    sendFrame frame = sendFrame("", genre, ":", this->bookclub.getName(), "");
                    string toSend = frame.tostring() + books + "\n^@";
                    int len = toSend.size();
                    if (!connectionHandler->sendLine(toSend)) {
                        this->Terminate();
                        connectionHandler->close();
                        std::cout << "Disconnected. Exiting...\n" << std::endl;
                    }
                }
//            std::cout << "\n"+toSend << std::endl;

//            std::string answer;
//            std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
//            if (!connectionHandler->getLine(answer)) {
//                connectionHandler->close();
//                std::cout << "Disconnected. Exiting...\n" << std::endl;
//            }
            }

        }

        if (connectionHandler->getDisconnect() == 2) {
            this->Terminate();
            connectionHandler->close();
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
        int len = answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len - 1);
//        std::cout << "\nReply:\n\n" << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            this->Terminate();
            connectionHandler->close();
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }



}




vector<std::string> Protocol::split(string s,string delimiter) {
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


bool Protocol::isTerminated() {
    return this->shouldTerminate;
}

void Protocol::Terminate() {
    this->shouldTerminate=true;

}

