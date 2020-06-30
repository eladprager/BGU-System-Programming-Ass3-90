//
// Created by eladpr@wincs.cs.bgu.ac.il on 15/01/2020.
//

#ifndef SPL_A3_BOOKCLUB_H
#define SPL_A3_BOOKCLUB_H

//#include <unordered_map>
#include <map>
#include <vector>
#include <atomic>
#include <mutex>


using namespace std;

class BookClub{
private:
    int subID;
    string name;
    vector<string> request;
    map<int,pair<string,string>> receipteMap; //receiprID<user,command>
    map<int,string> subIDgenreMap;
    map<string,vector<string>> genreBookMap;
    map<string,string> borrowMap;
public:
    BookClub();
    BookClub(const BookClub& other);
    int getSubID();
    bool AmItheBorrower(string book,string name);
    int getSubIDbyGenre(string genre);
    void addToReceiptMap(int receiptID, pair<string,string> commandGenrePair);
    void addToSubIdMap(int subID,string genre);
    void addBookByGenre(string genre,string bookName);
    string getCommandByIndex(int index);
    string getDestinationByIndex(int index);
    bool deleteBookByGenre(string genre,string bookName);
    void setName(string name);
    void addRequest(string request);
    void deleteRequest(string request);
    bool containsRequest(string request);
    void subscribe(string genre);
    void borrow(string bookName,string userName);
    void deleteFromBorrowMap(string bookName);
    string WhoToReturn(string bookName);
    string getName();
    vector<string> getBooksByGenre(string genre);



};

#endif //SPL_A3_BOOKCLUB_H
