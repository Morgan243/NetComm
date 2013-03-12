#need to add support for cross compile
COMP=g++

#we'll want to try and use C11 threads if the cross compiler can do it
FLAGS=-lpthread --std=c++11
OUT=test

all : Client Server

Client : Test_client.o NetComm.o NC_Client.o
	$(COMP) Test_client.o NetComm.o NC_Client.o $(FLAGS) -o client

Server : Test_server.o NetComm.o NC_Server.o
	$(COMP) Test_server.o NetComm.o NC_Server.o $(FLAGS) -o server

Test_client.o : Test_client.cpp
	$(COMP) -c Test_client.cpp $(FLAGS)

Test_server.o : Test_server.cpp
	$(COMP) -c Test_server.cpp $(FLAGS)

NC_Client.o : NC_Client.cpp NC_Client.h
	$(COMP) -c NC_Client.cpp NC_Client.h $(FLAGS)

NC_Server.o : NC_Server.cpp NC_Server.h
	$(COMP) -c NC_Server.cpp NC_Server.h $(FLAGS)

NetComm.o: NetComm.cpp NetComm.h
	$(COMP) -c NetComm.cpp NetComm.h $(FLAGS)

clean :
	rm client server *.o *.gch
