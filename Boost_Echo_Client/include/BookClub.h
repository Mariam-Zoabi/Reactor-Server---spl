//
// Created by arielron@wincs.cs.bgu.ac.il on 19/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOKCLUB_H
#define BOOST_ECHO_CLIENT_BOOKCLUB_H

#include <iostream>
#include <list>
#include <atomic>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <mutex>

using namespace std;
class BookClub {
private:

    std::mutex& _mutex1;
    std::mutex& _mutex2;
    std::mutex& _mutex3;
    std::mutex& _mutex4;
    std::mutex& _mutex5;
    std::mutex& _mutex6;
    std::mutex& _mutex7;
    std::mutex& _mutex8;
    std::mutex& _mutex9;
    std::mutex& _mutex10;
    std::mutex& _mutex11;
    std::mutex& _mutex12;
    std::mutex& _mutex13;
    std::mutex& _mutex14;
    std::mutex& _mutex15;
    std::mutex& _mutex16;
    std::atomic<int> receiptID;
    std::atomic<int> topicID;
    int errorCount;
    std::string username;
    std::map<std::string,std::string> userInventory;        //key bookname value person to return name or my username if self added
    std::map<std::string,std::string> tempUserInventory;
    std::map<std::string,std::vector<std::string>> tempTopicBooksMap;       //key topic value vector of all book of this topic
    std::map<std::string,std::vector<std::string>> topicBooksMap;
    std::map<std::string,std::string> subToTopics;                      //key topic value topicid
    std::map<std::string,std::string> tempSubToTopics;
    std::map<int,std::pair<std::string,std::string>> receiptMap;        //key receiptid value pair<join/exit/disconnect, topic/"">
    std::map<std::string,std::string> borrowRequest;                    //key bookName value PENDING/COMPLETED

    void syncUserInv(std::string book);
    void syncUserInvInsert(std::string book);

public:
    BookClub(std::mutex& _mutex1,
    std::mutex& _mutex2,
    std::mutex& _mutex3,
    std::mutex& _mutex4,
    std::mutex& _mutex5,
    std::mutex& _mutex6,
    std::mutex& _mutex7,
    std::mutex& _mutex8,
    std::mutex& _mutex9,
    std::mutex& _mutex10,
    std::mutex& _mutex11,
    std::mutex& _mutex12,
    std::mutex& _mutex13,
    std::mutex& _mutex14,
    std::mutex& _mutex15,
    std::mutex& _mutex16);
    BookClub(BookClub const &club);
    int getReceiptID();
    void increaseReceiptID();
    int getTopicID();
    void increaseTopicID();
    void setUserName(std::string name);
    std::string getUserName();
    void subToTopic(std::string topic);
    void subToTempTopic(std::string topic,std::string id);
    void addToReceiptMap(int receiptID,std::pair<std::string,std::string> s);
    void removeTopic(std::string topic);
    void addToTempInv(std::string bookName, std::string nameToReturn);
    void addToTempTopicBooksMap(std::string topic, std::string bookName);
    void addBorrowRequest(std::string bookName);
    void returnBook(std::string topic,std::string bookName);
    std::string getUserToReturn(std::string bookName);
    std::pair<std::string,std::string> getPairForReceipt(int receipt_id);
    void cleanBooks();
    void addNewBook(std::string topic, std::string book);
    bool contains(std::string bookName);
    bool canTake(std::string bookName);
    std::string makeBooksOfTopicString(std::string topic);
    bool checkTemp(std::string bookName);
    std::string getIDForTopic(std::string topic);
    bool findTopic(std::string topic);
    void changeReturnName(std::string bookName, std::string returnName);



};


#endif //BOOST_ECHO_CLIENT_BOOKCLUB_H
