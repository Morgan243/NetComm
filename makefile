#need to add support for cross compile
COMP=g++

#we'll want to try and use C11 threads if the cross compiler can do it
FLAGS=-lpthread --std=c++11
OUT=test

all : Client Server

Client : Test_client.o NetComm.o
	$(COMP) Test_client.o NetComm.o $(FLAGS) -o client

Server : Test_server.o NetComm.o
	$(COMP) Test_server.o NetComm.o $(FLAGS) -o server

Test_client.o : Test_client.cpp
	$(COMP) -c Test_client.cpp $(FLAGS)

Test_server.o : Test_server.cpp
	$(COMP) -c Test_server.cpp $(FLAGS)

NetComm.o: NetComm.cpp NetComm.h
	$(COMP) -c NetComm.cpp NetComm.h $(FLAGS)

clean :
	rm client server *.o
