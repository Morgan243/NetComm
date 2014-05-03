#need to add support for cross compile
COMP=g++
CROSS_ARM=arm-unknown-linux-gnueabi-g++
CROSS_PPC=powerpc-linux-g++

FLAGS=-lpthread -fPIC
OUT=test

x86 : Client Server

arm : Client_arm Server_arm

ppc: Client_ppc Server_ppc



Client_arm : Test_client_arm.o NetComm_arm.o NC_Client_arm.o
	$(CROSS_ARM) Test_client.o NetComm.o NC_Client.o $(FLAGS) -o client

Server_arm : Test_server_arm.o NetComm_arm.o NC_Server_arm.o
	$(CROSS_ARM) Test_server.o NetComm.o NC_Server.o $(FLAGS) -o server

Test_client_arm.o : Test_client.cpp
	$(CROSS_ARM) -c Test_client.cpp $(FLAGS)

Test_server_arm.o : Test_server.cpp
	$(CROSS_ARM) -c Test_server.cpp $(FLAGS)

NC_Client_arm.o : NC_Client.cpp NC_Client.h
	$(CROSS_ARM) -c NC_Client.cpp NC_Client.h $(FLAGS)

NC_Server_arm.o : NC_Server.cpp NC_Server.h
	$(CROSS_ARM) -c NC_Server.cpp NC_Server.h $(FLAGS)

NetComm_arm.o: NetComm.cpp NetComm.h
	$(CROSS_ARM) -c NetComm.cpp NetComm.h $(FLAGS)




Client_ppc : Test_client_ppc.o NetComm_ppc.o NC_Client_ppc.o
	$(CROSS_PPC) Test_client.o NetComm.o NC_Client.o $(FLAGS) -o client

Server_ppc : Test_server_ppc.o NetComm_ppc.o NC_Server_ppc.o
	$(CROSS_PPC) Test_server.o NetComm.o NC_Server.o $(FLAGS) -o server

Test_client_ppc.o : Test_client.cpp
	$(CROSS_PPC) -c Test_client.cpp $(FLAGS)

Test_server_ppc.o : Test_server.cpp
	$(CROSS_PPC) -c Test_server.cpp $(FLAGS)

NC_Client_ppc.o : NC_Client.cpp NC_Client.h
	$(CROSS_PPC) -c NC_Client.cpp NC_Client.h $(FLAGS)

NC_Server_ppc.o : NC_Server.cpp NC_Server.h
	$(CROSS_PPC) -c NC_Server.cpp NC_Server.h $(FLAGS)

NetComm_ppc.o: NetComm.cpp NetComm.h
	$(CROSS_PPC) -c NetComm.cpp NetComm.h $(FLAGS)





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
