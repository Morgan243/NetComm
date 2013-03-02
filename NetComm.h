#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>

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
    private:
        bool isListener = false, isClient = false;

        int queueLength = 10;
        int scok_fd,
                  n,
           SocketFD,
        workingSock;

        struct sockaddr_in sockAddrIn;
        socklen_t sockLength;

        int SetupSock();

    public:    
        NetComm();
        NetComm(int sockFD);
        NetComm(bool isListener, std::string addr,  unsigned int port);
        ~NetComm();

        void Connect();

        void Listen();
        void Listen(int connBacklog);
        int Accept();

        void Send(unsigned char *data, int size);
        int Receive(unsigned char *buffer, int size);

        //TODO
        //Receive
        //Listen
        // -
};



//needed?
struct NetOptions
{
    

};

