#include <stdlib.h>
#include "../include/connectionHandler.h"
#include "../include/keyboard.h"
#include <iostream>
#include <thread>

using namespace std;

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (/*int argc, char *argv[]*/) {
//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//        return -1;
//    }
    std::string host="";
    short port=0;
    
    ConnectionHandler connectionHandler(host,port);
//    if (!connectionHandler.connect()) {
//        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
//        return 1;
//    }
    BookClub bookClub = BookClub();
    Protocol protocol = Protocol(&connectionHandler,bookClub);
    keyboard key = keyboard(bookClub,&connectionHandler,protocol);
    thread t1(key);
    thread t2(protocol);
//    std::thread t2(protol);
	//From here we will see the rest of the ehco client implementation:
//    while (1) {
//        const short bufsize = 1024;
//        char buf[bufsize];
//        std::cin.getline(buf, bufsize);
//		std::string line(buf);
//
//		string newline = key.input(line);
//
//		int len=newline.length();
//        if (!connectionHandler.sendLine(newline)) {
//            connectionHandler.close();
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//
//		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
//        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
//
//
//        // We can use one of three options to read data from the server:
//        // 1. Read a fixed number of characters
//        // 2. Read a line (up to the newline character using the getline() buffered reader
//        // 3. Read up to the null character
//        std::string answer;
//        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
//        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
//        if (!connectionHandler.getLine(answer)) {
//            connectionHandler.close();
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//        protocol.process(answer);
//        if (connectionHandler.getDisconnect()==2){
//            connectionHandler.close();
//            std::cout << "Exiting...\n" << std::endl;
//            break;
//        }
//		len=answer.length();
//		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
//		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
//        answer.resize(len-1);
////        std::cout << "\nReply:\n\n" << answer << " " << len << " bytes " << std::endl << std::endl;
//        if (answer == "bye") {
//            connectionHandler.close();
//            std::cout << "Exiting...\n" << std::endl;
//            break;
//        }
//    }
    t1.join();
    t2.join();
    return 0;
}
