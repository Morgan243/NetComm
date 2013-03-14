#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class NetComm
{
    protected:
        bool initialized;
        int master_socket;       
        char temp_buffer[1024];

        sockaddr_in socket_address;
        socklen_t socket_length;

        void SetupSock();

    public:    
        explicit NetComm();
        explicit NetComm(int sockFD);
        explicit NetComm(bool isListener, std::string addr,  unsigned int port);

        //setup adress DOES NOT bind
        void SetupAddress(std::string address, unsigned port);

        //setup address and bind to socket
        void Init(bool isListener, std::string address, unsigned int port);
        ~NetComm();
};


