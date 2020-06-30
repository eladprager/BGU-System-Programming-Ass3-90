CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system
THREADFLAGS:=-pthread

default: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/BookClub.o bin/connectFrame.o bin/connectionHandler.o bin/disconnectFrame.o bin/keyboard.o bin/protocol.o bin/sendFrame.o bin/subscribeFrame.o bin/unsubscribeFrame.o bin/StompBookClubClient.o $(LDFLAGS) $(THREADFLAGS)

StompBookClubClient: bin/BookClub.o bin/connectFrame.o bin/connectionHandler.o bin/disconnectFrame.o bin/keyboard.o bin/protocol.o bin/sendFrame.o bin/StompBookClubClient.o bin/subscribeFrame.o bin/unsubscribeFrame.o

bin/BookClub.o: src/BookClub.cpp
	g++ $(CFLAGS) -o bin/BookClub.o src/BookClub.cpp

bin/connectFrame.o: src/connectFrame.cpp
	g++ $(CFLAGS) -o bin/connectFrame.o src/connectFrame.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/disconnectFrame.o: src/disconnectFrame.cpp
	g++ $(CFLAGS) -o bin/disconnectFrame.o src/disconnectFrame.cpp

bin/keyboard.o: src/keyboard.cpp
	g++ $(CFLAGS) -o bin/keyboard.o src/keyboard.cpp

bin/protocol.o: src/protocol.cpp
	g++ $(CFLAGS) -o bin/protocol.o src/protocol.cpp

bin/sendFrame.o: src/sendFrame.cpp
	g++ $(CFLAGS) -o bin/sendFrame.o src/sendFrame.cpp

bin/StompBookClubClient.o: src/StompBookClubClient.cpp
	g++ $(CFLAGS) -o bin/StompBookClubClient.o src/StompBookClubClient.cpp

bin/subscribeFrame.o: src/subscribeFrame.cpp
	g++ $(CFLAGS) -o bin/subscribeFrame.o src/subscribeFrame.cpp

bin/unsubscribeFrame.o: src/unsubscribeFrame.cpp
	g++ $(CFLAGS) -o bin/unsubscribeFrame.o src/unsubscribeFrame.cpp

.PHONY: clean
clean:
	rm -f bin/*