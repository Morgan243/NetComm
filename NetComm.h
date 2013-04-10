#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>

#include <linux/tcp.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define DEBUG 0
class NetComm
{
    protected:
        bool initialized;                   //has the master_socket socket been setup?
        int master_socket;                  //clients only socket and servers listening socket
        int flag;                           //used with TCP_NODELAY
        char temp_buffer[1024];             //used for all your buffering needs (1kB)

        sockaddr_in socket_address;         //master_socket address descriptor
        socklen_t socket_length;            //used in server's accept call

        void SetupSock();

    public:    
        explicit NetComm();
        explicit NetComm(int sockFD);
        explicit NetComm(bool isListener, std::string addr,  unsigned int port);
        ~NetComm();

        //setup adress DOES NOT bind
        void SetupAddress(std::string address, unsigned port);

        //setup address and bind to socket
        void Init(bool isListener, std::string address, unsigned int port);
};


