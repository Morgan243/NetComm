#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


class NetComm
{
    private:
        int scok_fd,
                  n,
                res,
           SocketFD;

        //struct CLI_Options options;

        struct sockaddr_in stSockAddr;

    public:    
        NetComm();
        ~NetComm();

        void Send(unsigned char *data, int size);

};
