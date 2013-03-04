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

struct ServerMembers
{

};

struct ClientMembers
{
    //int sock
};


class NetComm
{
    protected:
        int master_socket;       

        sockaddr_in socket_address;
        socklen_t socket_length;

        void SetupSock();

    public:    
        explicit NetComm();
        explicit NetComm(int sockFD);
        explicit NetComm(bool isListener, std::string addr,  unsigned int port);
        ~NetComm();
};


//needed?
struct NetOptions
{
    

};

