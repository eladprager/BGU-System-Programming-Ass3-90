//
// Created by eladpr@wincs.cs.bgu.ac.il on 15/01/2020.
//

#include "../include/BookClub.h"



void BookClub::addToSubIdMap(int subID, string genre) {

}

BookClub::BookClub() :
subID(0),name(""),request(),receipteMap(),subIDgenreMap(),genreBookMap(),borrowMap() {
}

void BookClub::addToReceiptMap(int receiptID, pair<string, string> commandGenrePair) {
    this->receipteMap.insert(make_pair(receiptID,commandGenrePair));
}


void BookClub::addBookByGenre(string genre, string bookName) {
    map<string,vector<string>>::iterator it = this->genreBookMap.find(genre);
    if (it != this->genreBookMap.end()){
        this->genreBookMap.at(genre).push_back(bookName);
    }
    else {
        vector<string> v;
        v.push_back(bookName);
        pair<string,vector<string>> p = make_pair(genre,v);
        this->genreBookMap.insert(p);
    }
}

bool BookClub::deleteBookByGenre(string genre,string bookName) {
    map<string,vector<string>>::iterator it = this->genreBookMap.find(genre);
    if (it != this->genreBookMap.end()){
        for (size_t i = 0; i < this->genreBookMap.at(genre).size(); i++){
            if (this->genreBookMap.at(genre)[i] == bookName){
                this->genreBookMap.at(genre).erase(this->genreBookMap.at(genre).begin()+i);
                return true;
            }
        }
    }
    return false;
}

void BookClub::setName(string name) {
    this->name=name;
}

string BookClub::getName() {
    return this->name;
}

void BookClub::addRequest(string request) {
    this->request.push_back(request);
}

bool BookClub::containsRequest(string request) {
    for (size_t i = 0; i < this->request.size(); i++){
        if (this->request[i] == request){
            return true;
        }
    }
    return false;
}

void BookClub::deleteRequest(string request) {
    for (size_t i = 0;i < this->request.size(); i++){
        if (this->request[i]==request){
            this->request.erase(this->request.begin()+i);
        }
    }
}

void BookClub::borrow(string bookName, string userName) {
    pair<string,string> p = make_pair(bookName,userName);
    this->borrowMap.insert(p);
}

void BookClub::deleteFromBorrowMap(string bookName) {
    this->borrowMap.erase(bookName);
}

vector<string> BookClub::getBooksByGenre(string genre) {
    return this->genreBookMap.at(genre);
}

string BookClub::getCommandByIndex(int index) {
    return this->receipteMap.at(index).first;
}

string BookClub::getDestinationByIndex(int index) {
    return this->receipteMap.at(index).second;
}

void BookClub::subscribe(string genre) {
    map<string,vector<string>>::iterator it = this->genreBookMap.find(genre);
    if (it != this->genreBookMap.end()){
        this->subIDgenreMap.insert(make_pair(subID,genre));
        this->subID++;
        return;
    }
    else {
        vector<string> k;
        this->genreBookMap.insert(make_pair(genre, k));
        this->subIDgenreMap.insert(make_pair(subID, genre));
        this->subID++;
    }
}

int BookClub::getSubID() {
    return this->subID;
}

int BookClub::getSubIDbyGenre(string genre) {
    for (const auto& kv : this->subIDgenreMap) {
        if (kv.second==genre) return kv.first;
    }
    return -1;
}

string BookClub::WhoToReturn(string bookName) {
    string toReturn = this->borrowMap.at(bookName);
    return toReturn;
}

bool BookClub::AmItheBorrower(string book, string name) {
    map<string,string>::iterator it = this->borrowMap.find(book);
    if(it != this->borrowMap.end())
    {
        if (it->second==name) return true;
    }
    return false;
}






