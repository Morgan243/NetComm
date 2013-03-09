//Network class for abstracting the low level BSD C sockets

#include "NetComm.h"

using namespace std;

#define DEBUG 1

NetComm::NetComm()
{
    SetupSock();
}

NetComm::NetComm(bool isListener, string addr, unsigned int port)
{
//{{{
    SetupSock();

    Init(isListener, addr, port);
//}}}
}

NetComm::NetComm(int sockFD)
{
    this->master_socket = sockFD;

    memset(&this->socket_address, 0, sizeof(this->socket_address));

    this->socket_address.sin_family = AF_INET;

    initialized = true;
}

NetComm::~NetComm()
{
    close(master_socket);
}

void NetComm::SetupSock()
{
//{{{
    this->master_socket = socket(PF_INET, SOCK_STREAM, 0);

    if( this->master_socket == -1)
    {
        perror("cannot create socket");
    }

    memset(&this->socket_address, 0, sizeof(this->socket_address));

    this->socket_address.sin_family = AF_INET;

    initialized = true;
//}}}
}

void NetComm::SetupAddress(string address, unsigned int port)
{
    //host to network byte order
    this->socket_address.sin_port = htons(port);

    //convert the address to binary form
    int res = inet_pton(AF_INET, address.c_str(), &this->socket_address.sin_addr);

        //check for errors in conversion
       if( res < 0)
       {
            perror("error: first parameter not valid");
            close(this->master_socket);
       }
       else if (res == 0)
       {
            perror("char string error");
            close(this->master_socket);
       }
}

void NetComm::Init(bool isListener, std::string address, unsigned int port)
{
//{{{
    if(!initialized)
        SetupSock();

    SetupAddress(address, port);

   //else, IS a SERVER
   if(isListener)
   {
        //pair socket fd with a port 
        if(bind(this->master_socket, (struct sockaddr *) & this->socket_address,
                                                                   sizeof(this->socket_address)) < 0)
            perror("Error on bind!");
   }
//}}}
}

