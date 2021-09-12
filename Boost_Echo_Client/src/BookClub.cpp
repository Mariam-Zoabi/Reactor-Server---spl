//
// Created by arielron@wincs.cs.bgu.ac.il on 19/01/2020.
//
#include <algorithm>
#include "BookClub.h"
BookClub::BookClub(std::mutex& _mutex1,
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
                   std::mutex& _mutex16):
        _mutex1(_mutex1), _mutex2(_mutex2), _mutex3(_mutex3),_mutex4(_mutex4),_mutex5(_mutex5),
        _mutex6(_mutex6),_mutex7(_mutex7),_mutex8(_mutex8),_mutex9(_mutex9),_mutex10(_mutex10),
        _mutex11(_mutex11),_mutex12(_mutex12),_mutex13(_mutex13),_mutex14(_mutex14),_mutex15(_mutex15),_mutex16(_mutex16){


    this->receiptID=0;
    this->topicID=0;
}

int BookClub::getReceiptID() {
    return this->receiptID;
}

void BookClub::increaseReceiptID() {
    this->receiptID++;
}

void BookClub::increaseTopicID() {
    this->topicID++;

}

int BookClub::getTopicID() {
    return this->topicID;
}

BookClub::BookClub(BookClub const &club):
        _mutex1(_mutex1), _mutex2(_mutex2), _mutex3(_mutex3),_mutex4(_mutex4),_mutex5(_mutex5),
        _mutex6(_mutex6),_mutex7(_mutex7),_mutex8(_mutex8),_mutex9(_mutex9),_mutex10(_mutex10),
        _mutex11(_mutex11),_mutex12(_mutex12),_mutex13(_mutex13),_mutex14(_mutex14),_mutex15(_mutex15),_mutex16(_mutex16) {

}


void BookClub::setUserName(std::string name) {
    this->username = name;

}

std::string BookClub::getUserName() {
    return this->username;
}

void BookClub::subToTopic(std::string topic) {
   std::string topic_id = this->tempSubToTopics.at(topic);
   this->subToTopics.insert({topic,topic_id});
   this->tempSubToTopics.erase(topic);

}

void BookClub::subToTempTopic(std::string topic,std::string id) {
    this->tempSubToTopics.insert({topic,id});

}

void BookClub::addToReceiptMap(int receiptID, std::pair<std::string, std::string> s) {
    this->receiptMap.insert({receiptID,s});

}


void BookClub::removeTopic(std::string topic) {
    this->subToTopics.erase(topic);

}

void BookClub::addToTempInv(std::string bookName, std::string nameToReturn) {
    this->tempUserInventory.insert({bookName,nameToReturn});



}

void BookClub::addToTempTopicBooksMap(std::string topic, std::string bookName) {

    if(this->tempTopicBooksMap.empty())
    {
        std::vector<std::string>vec;
        vec.push_back(bookName);
        this->tempTopicBooksMap.insert({topic,vec});
    }
    else {
        std::map<std::string, std::vector<std::string>>::iterator it;
        it = this->tempTopicBooksMap.find(topic);
        if(1==1) {
            std::lock_guard<std::mutex> lock(_mutex3);

            if (it != this->tempTopicBooksMap.end()) {
                this->tempTopicBooksMap.at(topic).push_back(bookName);
            } else {
                std::vector<std::string> vec;
                vec.push_back(bookName);
                this->tempTopicBooksMap.insert({topic, vec});
            }
        }

    }



}

void BookClub::addBorrowRequest(std::string bookName) {
    this->borrowRequest.insert({bookName,std::string("PENDING")});

}

void BookClub::returnBook(std::string topic, std::string bookName) {

    this->syncUserInv(bookName);

        std::vector<std::string>::iterator itr = std::find(this->topicBooksMap.at(topic).begin(),
                                                           this->topicBooksMap.at(topic).end(), bookName);
    if(1==1) {
        std::lock_guard<std::mutex> lock(_mutex4);
        this->topicBooksMap.at(topic).erase(itr);
    }
}

std::string BookClub::getUserToReturn(std::string bookName) {
    std::lock_guard<std::mutex> lock(_mutex1);
    return this->userInventory.at(bookName);
}

std::pair<std::string, std::string> BookClub::getPairForReceipt(int receipt_id) {
    std::lock_guard<std::mutex> lock(_mutex7);
    return this->receiptMap.at(receipt_id);
}

void BookClub::cleanBooks() {
    this->receiptID.exchange(0);
    this->topicID.exchange(0);
    this->setUserName(std::string(""));
    this->userInventory.clear();
    this->tempUserInventory.clear();
    this->topicBooksMap.clear();
    this->tempTopicBooksMap.clear();
    this->subToTopics.clear();
    this->tempSubToTopics.clear();
    this->receiptMap.clear();
    this->borrowRequest.clear();

}

void BookClub::addNewBook(std::string topic, std::string book) {

    syncUserInvInsert(book);

    if(this->topicBooksMap.empty())
    {
        std::vector<std::string>vec;
        vec.push_back(book);
        this->topicBooksMap.insert({topic,vec});
    }
    else {

        std::map<std::string, std::vector<std::string>>::iterator it;
        it = this->topicBooksMap.find(topic);
        if(1==1) {
            std::lock_guard<std::mutex> lock(_mutex8);

            if (it != this->topicBooksMap.end()) {
                this->topicBooksMap.at(topic).push_back(book);
            } else {
                std::vector<std::string> vec;
                vec.push_back(book);
                this->topicBooksMap.insert({topic, vec});

            }
        }
    }
    if(1==1)
    {
        std::lock_guard<std::mutex> lock(_mutex2);
        this->tempUserInventory.erase(book);
    }

    std::vector<std::string>::iterator it2 = std::find(this->tempTopicBooksMap.at(topic).begin(), this->tempTopicBooksMap.at(topic).end(), book);

    if(1==1) {
        std::lock_guard<std::mutex> lock(_mutex5);
        this->tempTopicBooksMap.at(topic).erase(it2);
    }


}

bool BookClub::contains(std::string bookName) {
    std::lock_guard<std::mutex> lock(_mutex6);
    if(!this->userInventory.empty()) {
        std::map<std::string, std::string>::iterator it;
        it = this->userInventory.find(bookName);
        if (it != this->userInventory.end())
            return true;
    }
    else{
        return false;
    }
    return false;
}

bool BookClub::canTake(std::string bookName) {
    std::lock_guard<std::mutex> lock(_mutex9);
    if(this->borrowRequest.empty()) {
        return false;
    }
    std::map<std::string,std::string>::iterator it;
    it = this->borrowRequest.find(bookName);
    if (it !=  this->borrowRequest.end()) {
        if(borrowRequest.at(bookName) == "PENDING")
        {
            borrowRequest.at(bookName) = "COMPLETED";

            return true;
        }
        return false;
    }
    else{
        return false;
    }

}

std::string BookClub::makeBooksOfTopicString(std::string topic) {
    std::lock_guard<std::mutex> lock(_mutex10);
    std:: string res ="";
    std::map<std::string,std::vector<std::string>>::iterator it;
    it = this->topicBooksMap.find(topic);
    if (it !=  this->topicBooksMap.end())
    {

        if(!this->topicBooksMap.at(topic).empty())
        {

            res = this->topicBooksMap.at(topic).at(0);
            for(int i=1; i<this->topicBooksMap.at(topic).size();i++)
            {


                res = res + ","+this->topicBooksMap.at(topic).at(i);
            }
        }
    }
    return res;

}

bool BookClub::checkTemp(std::string bookName) {
    std::lock_guard<std::mutex> lock(_mutex11);

    try {
        this->tempUserInventory.at(bookName);
        return true;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}

std::string BookClub::getIDForTopic(std::string topic) {
    std::lock_guard<std::mutex> lock(_mutex12);
    return this->subToTopics.at(topic);
}

bool BookClub::findTopic(std::string topic) {
    std::lock_guard<std::mutex> lock(_mutex13);

    if(this->subToTopics.empty())
        return false;
    std::map<std::string, std::string>::iterator it;
    it = this->subToTopics.find(topic);
    if (it != this->subToTopics.end()) {
        return true;
    } else {
        return false;
    }
}

void BookClub::changeReturnName(std::string bookName, std::string returnName) {
    std::lock_guard<std::mutex> lock(_mutex16);

    this->userInventory.at(bookName)=returnName;

}

void BookClub::syncUserInv(std::string book) {
    std::lock_guard<std::mutex> lock(_mutex14);
    this->userInventory.erase(book);

}

void BookClub::syncUserInvInsert(std::string book) {

    std::lock_guard<std::mutex> lock(_mutex15);
    this->userInventory.insert({book,std::string(getUserName())});
}






