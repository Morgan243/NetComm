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
           SocketFD;

        struct sockaddr_in sockAddrIn;

        int SetupSock();

    public:    
        NetComm();
        NetComm(bool isListener, std::string addr,  unsigned int port);
        ~NetComm();

        void Connect();
        void Listen();
        void Listen(int connBacklog);

        void Send(unsigned char *data, int size);

        //TODO
        //Receive
        //Listen
        // -
};



//needed?
struct NetOptions
{
    

};

