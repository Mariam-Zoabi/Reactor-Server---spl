#include <stdlib.h>
#include <connectionHandler.h>
#include <BookClub.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;


std::vector<std::string> split(std::string basicString, std::string basicString1);

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//        return -1;
//    }


    std::mutex _mutex1;
    std::mutex _mutex2;
    std::mutex _mutex3;
    std::mutex _mutex4;
    std::mutex _mutex5;
    std::mutex _mutex6;
    std::mutex _mutex7;
    std::mutex _mutex8;
    std::mutex _mutex9;
    std::mutex _mutex10;
    std::mutex _mutex11;
    std::mutex _mutex12;
    std::mutex _mutex13;
    std::mutex _mutex14;
    std::mutex _mutex15;
    std::mutex _mutex16;

    std::string host1 = "";
    short port1 = atoi("");
    ConnectionHandler *connectionHandler = new ConnectionHandler(host1, port1);
    //if (!connectionHandler->connect()) {
       // std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        //return 1;
    //}

   // EncoderDecoder encdc = EncoderDecoder();
    BookClub* bookClub = new BookClub(_mutex1, _mutex2, _mutex3, _mutex4, _mutex5, _mutex6,
                                      _mutex7, _mutex8,_mutex9, _mutex10, _mutex11, _mutex12, _mutex13, _mutex14, _mutex15, _mutex16);
    std::atomic<bool> *shouldTerminate = new std::atomic<bool>(false);
    std::atomic<bool> *canGetLine = new std::atomic<bool>(false);

    std::thread toServer([connectionHandler,shouldTerminate,bookClub,canGetLine]() {
    while(!*shouldTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        std::string space = " ";
        std::vector<std::string> splitstr = split(line, space);
        std::string strToSrv = "";
        if (splitstr[0] == "login") {
            std::string hostport = splitstr[1];
            std:: string newTwoDots = ":";
            std::vector<std::string> hostNport = split(hostport,newTwoDots);
            std::string host = hostNport[0];
            short port = std::stoi(hostNport[1]);
            std::string name = splitstr[2];
            std::string password = splitstr[3];
            connectionHandler->setIP(host,port);
            strToSrv = "CONNECT\naccept-version:1.2\nhost:" + hostport + "\nlogin:" + name + "\npasscode:" + password +
                       '\n' + '\n' + '\0';

            bookClub->setUserName(name);
            if (!connectionHandler->connect()) {
                std::cerr << "Cannot connect to "<< std::endl;
                return 1;
            }
            *canGetLine = true;



        }
        if (splitstr[0] == "join") {

            std::string destination = splitstr[1];
            int topicid = bookClub->getTopicID();
            bookClub->increaseTopicID();
            int receiptid = bookClub->getReceiptID();
            bookClub->increaseReceiptID();
            strToSrv = "SUBSCRIBE\ndestination:" + destination + "\nid:" + std::to_string(topicid) + "\nreceipt:" +
                       std::to_string(receiptid) + '\n' + '\n' + '\0';

            std::pair<std::string, std::string> s = {"join", destination};
            bookClub->addToReceiptMap(receiptid, s);
            bookClub->subToTempTopic(destination, std::to_string(topicid));

        }

        if (splitstr[0] == "exit") {
            std::string topic = splitstr[1];
            int receiptid = bookClub->getReceiptID();
            bookClub->increaseReceiptID();
            std::string topic_id ="";
            topic_id = bookClub->getIDForTopic(topic);
            strToSrv = "UNSUBSCRIBE\nreceipt:" + std::to_string(receiptid)+'\n'+"id:"+topic_id + '\n' + '\n' + '\0';

            std::pair<std::string, std::string> s = {"exit", topic};
            bookClub->addToReceiptMap(receiptid, s);
            bookClub->removeTopic(topic);

        }

        if (splitstr[0] == "add") {
            std::string topic = splitstr[1];
            std::string bookName = splitstr[2];
            for (int i = 3; i < splitstr.size(); i++) {
                bookName = bookName + " " + splitstr[i];
            }
            strToSrv = "SEND\ndestination:" + topic + '\n' + '\n' + bookClub->getUserName() + " has added the book " +
                       bookName + '\n' + '\0';

            if(bookClub->findTopic(topic))
            {
                bookClub->addToTempInv(bookName, std::string(bookClub->getUserName()));
                bookClub->addToTempTopicBooksMap(topic, bookName);
            }
            else{
                bookClub->addToTempInv(bookName, std::string(bookClub->getUserName()));
                bookClub->addToTempTopicBooksMap(topic, bookName);
                bookClub->addNewBook(topic, bookName);
            }
        }

        if (splitstr[0] == "borrow") {
            std::string topic = splitstr[1];
            std::string bookName = splitstr[2];
            for (int i = 3; i < splitstr.size(); i++) {
                bookName = bookName + " " + splitstr[i];
            }
            strToSrv = "SEND\ndestination:" + topic + '\n' + '\n' + bookClub->getUserName() + " wish to borrow " +
                       bookName + '\n' + '\0';

            bookClub->addBorrowRequest(bookName);


        }
        if (splitstr[0] == "return") {
            std::string topic = splitstr[1];
            std::string bookName = splitstr[2];
            std::string returnToName = bookClub->getUserToReturn(bookName);
            strToSrv = "SEND\ndestination:" + topic + '\n' + '\n' + "Returning " + bookName + " to " + returnToName +
                       '\n' + '\0';

            bookClub->returnBook(topic, bookName);

        }
        if (splitstr[0] == "status") {
            std::string topic = splitstr[1];
            strToSrv = "SEND\ndestination:" + topic + '\n' + '\n' + "book status" + '\n' + '\0';


        }
        if (splitstr[0] == "logout") {
            int receiptId = bookClub->getReceiptID();
            bookClub->increaseReceiptID();
            std::cout<<receiptId<<std::endl;
            std::cout<<bookClub->getReceiptID()<<std::endl;
            strToSrv = "DISCONNECT\nreceipt:" + std::to_string(receiptId) + '\n' + '\n' + '\0';
            std::cout<<strToSrv<<std::endl;
            std::pair<std::string, std::string> s = {"logout", "logout"};
            bookClub->addToReceiptMap(receiptId, s);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));


        }


        if (!connectionHandler->sendLine(strToSrv)) {
            std::cout<<"sendLine Error"<<std::endl;
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            *shouldTerminate = true;
        }


    }
    });
    std::thread fromServer([connectionHandler,shouldTerminate,bookClub,canGetLine]() {

        while(!*shouldTerminate) {
            std::string answer;
        if(*canGetLine)
        {
            if (!connectionHandler->getLine(answer)) {
                std::cout<<"getLine Error  "<<connectionHandler->getHost()<<std::endl;
                *shouldTerminate = true;
                std::cout << "Disconnected. Exiting...\n" << std::endl;
            }
            std::string newLine = "\n";
            std::vector<std::string> splitstr = split(answer, newLine);
            if (splitstr[0] == "CONNECTED") {
                std::cout << "Login successful" << std::endl;
                std::cout<<splitstr[1]<<std::endl;

            }
            if(splitstr[0] =="RECEIPT")
            {
                std::string dots2 = ":";
                std::vector<std::string> splitstr2 = split(splitstr[1], dots2);
                int receiptId = stoi(splitstr2[1]);
                std::pair<std::string,std::string> s = bookClub->getPairForReceipt(receiptId);
                std::string cmd = s.first;
                std::string topic = s.second;
                if(cmd == "exit")
                {
                    std::cout<<"Exited club "+topic<<std::endl;
                }
                if(cmd == "join") {
                    std::cout << "Joined club " + topic << std::endl;

                    bookClub->subToTopic(topic);
                }
                if(cmd=="logout")
                {
                    *canGetLine = false;
                    bookClub->cleanBooks();
                    connectionHandler->close();

                }
            }
            if(splitstr[0]=="ERROR")
            {
              for(int i=0; i<splitstr.size(); i++)
                  std::cout<<splitstr[i]<<std::endl;
            }
            if(splitstr[0] == "MESSAGE") {

                std::string body = splitstr[5];

                std::string destination = splitstr[3];
                std::string dots2 = ":";
                std::vector<std::string> toTopicVec = split(destination, dots2);
                std::string topic = toTopicVec[1];
                std::cout << body << std::endl;
                std::string space1 = " ";
                std::vector<std::string> splitstr3 = split(body, space1);
                int size = splitstr3.size();
                //check add
                if (size >= 6) {

                    if (splitstr3[0] == bookClub->getUserName() && splitstr3[1] == "has" && splitstr3[2] == "added" &&
                        splitstr3[3] == "the"
                        && splitstr3[4] == "book") {

                        std::string book = splitstr3[5];
                        for (int i = 6; i < size; i++) {
                            book = book + " " + splitstr3[i];
                        }
                        if (bookClub->checkTemp(book))
                            bookClub->addNewBook(topic, book);

                    }
                }
                //borrow
                //phase 1
                if (size >= 5) {
                    if (splitstr3[0] != bookClub->getUserName() && splitstr3[1] == "wish" && splitstr3[2] == "to" &&
                        splitstr3[3] == "borrow") {
                        std::cout<<"TEST::: In wish to add"<<std::endl;
                        std::string book = splitstr3[4];
                        for (int i = 5; i < size; i++) {
                            book = book + " " + splitstr3[i];
                        }
                        if (bookClub->contains(book)) {

                            std::string msgFrame =
                                    "SEND\ndestination:" + topic + '\n' + '\n' + bookClub->getUserName() + " has " +
                                    book + '\n' + '\n' + '\0';
                            std::cout<<msgFrame<<std::endl;
                            if (!connectionHandler->sendLine(msgFrame)) {
                                std::cout << "Disconnected. Exiting...\n" << std::endl;
                            }

                        }
                    }
                }

                //phase 2
                if (size >= 4) {
                    if (splitstr3[0] == "Taking" && splitstr3[size - 1] == bookClub->getUserName() &&
                        splitstr3[size - 2] == "from") {
                        std::cout<<"TEST::: In taking from"<<std::endl;
                        std::string book = splitstr3[1];
                        for (int i = 2; i < size - 2; i++) {
                            book = book + " " + splitstr3[i];
                        }
                        bookClub->returnBook(topic, book);
                    }
                    if (splitstr3[0] == "Returning" && splitstr3[size - 1] == bookClub->getUserName() &&
                        splitstr3[size - 2] == "to") {
                        std::cout<<"TEST::: In returning"<<std::endl;
                        std::string book = splitstr3[1];
                        for (int i = 2; i < size - 2; i++) {
                            book = book + " " + splitstr3[i];
                        }
                        bookClub->addToTempInv(book, std::string(bookClub->getUserName()));
                        bookClub->addToTempTopicBooksMap(topic, book);
                        bookClub->addNewBook(topic, book);

                    }

                }

                //phase 3
                if (size >= 3) {
                    if (splitstr3[0] != bookClub->getUserName() && splitstr3[1] == "has") {

                        std::string newBook = splitstr3[2];
                        for (int i = 3; i < size; i++) {
                            newBook = newBook + " " + splitstr3[i];

                        }

                        if (bookClub->canTake(newBook)) {

                            bookClub->addToTempInv(newBook, std::string(bookClub->getUserName()));
                            bookClub->addToTempTopicBooksMap(topic, newBook);
                            bookClub->addNewBook(topic, newBook);
                            bookClub->changeReturnName(newBook, splitstr3[0]);
                            std::string msgFrame2 =
                                    "SEND\ndestination:" + topic + '\n' + '\n' + "Taking " + newBook + " from " +
                                    splitstr3[0] + '\n' + '\0';
                            if (!connectionHandler->sendLine(msgFrame2)) {
                                std::cout << "Disconnected. Exiting...\n" << std::endl;
                            }
                        }
                    }

                }

                //status
                if (body == "book status") {
                    std::string tmpbody = bookClub->getUserName() + ":";
                    tmpbody = tmpbody + bookClub->makeBooksOfTopicString(topic);
                    std::string msgFrame3 = "SEND\ndestination:" + topic + '\n' + '\n' + tmpbody + '\n' + '\0';
                    if (!connectionHandler->sendLine(msgFrame3)) {
                        std::cout << "Disconnected. Exiting...\n" << std::endl;
                    }
                }


            }
            }
            }
    });
    toServer.join();
    fromServer.join();
    delete connectionHandler;
    delete shouldTerminate;


    return 0;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
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
