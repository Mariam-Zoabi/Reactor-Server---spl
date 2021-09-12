CPPFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
BOOSTFLAGS:=-lboost_system
THREADFLAGS:=-pthread

default: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/BookClub.o bin/connectionHandler.o bin/StompBookClubClient.o $(BOOSTFLAGS) $(THREADFLAGS)


StompBookClubClient: bin/BookClub.o bin/connectionHandler.o bin/StompBookClubClient.o

bin/BookClub.o: src/BookClub.cpp
	g++ $(CPPFLAGS) -o bin/BookClub.o src/BookClub.cpp


bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CPPFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp


bin/StompBookClubClient.o: src/StompBookClubClient.cpp
	g++ $(CPPFLAGS) -o bin/StompBookClubClient.o src/StompBookClubClient.cpp

.PHONY: clean
clean:
	rm -f bin/*
