//Network class for abstracting the low level BSD C sockets

#include "NetComm.h"

using namespace std;

NetComm::NetComm()
{
//{{{
    flag = 1;
    initialized = false;
    SetupSock();
//}}}
}

NetComm::NetComm(bool isListener, string addr, unsigned int port)
{
//{{{
    flag = 1;
    initialized = false;

    SetupSock();

    Init(isListener, addr, port);
//}}}
}

NetComm::NetComm(int sockFD)
{
//{{{
    initialized = false;

    flag = 1;

    #if DEBUG
        cout<<"Constructing network with socket..."<<endl;
    #endif

    //set socket to constructor arg
    this->master_socket = sockFD;

    //zero out the address struct
    memset(&this->socket_address, 0, sizeof(this->socket_address));

    //ipv4
    this->socket_address.sin_family = AF_INET;

    initialized = true;
//}}}
}

NetComm::~NetComm()
{
//{{{
    #if DEBUG
        cout<<"Shuting down socket!!"<<endl;
    #endif
    char buf[256];

    //begin shutdown
    shutdown(master_socket, SHUT_RDWR);

    //be sure to read everything
    while(read(this->master_socket, buf, 256) > 0);

    close(master_socket);
//}}}
}

void NetComm::SetupSock()
{
//{{{
    //create the master socket
    this->master_socket = socket(PF_INET, SOCK_STREAM, 0);

    setsockopt(this->master_socket, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

    //check error
    if(this->master_socket == -1)
    {
        perror("cannot create socket");
    }

    //zero out the address struct
    memset(&this->socket_address, 0, sizeof(this->socket_address));

    //ipv4
    this->socket_address.sin_family = AF_INET;

    initialized = true;
//}}}
}

void NetComm::SetupAddress(string address, unsigned int port)
{
//{{{
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
//}}}
}

void NetComm::Init(bool isListener, std::string address, unsigned int port)
{
//{{{

    #if DEBUG
        cout<<"Initializing network..."<<endl;
    #endif

    //setup socket if not alreadu
    if(!initialized)
        SetupSock();

    //set the address numbers
    SetupAddress(address, port);

   //else, IS a SERVER
   if(isListener)
   {
        //pair socket fd with a port and check error
        if(bind(this->master_socket, (struct sockaddr *) & this->socket_address,
                                                                   sizeof(this->socket_address)) < 0)
            perror("Error on bind!");
   }
//}}}
}
