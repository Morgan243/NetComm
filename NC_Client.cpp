#include "NC_Client.h"

using namespace std;


NC_Client::NC_Client()
{

}

NC_Client::NC_Client(string address, unsigned int port)
                : NetComm(false, address, port)
{

}

NC_Client::~NC_Client()
{

}

void NC_Client::Connect()
{
//{{{
if(connect(this->master_socket, (struct sockaddr *)& this->socket_address,sizeof(this->socket_address)) == -1)
   {
        #if DEBUG
            printf("CONNECTION ERROR!\n");
        #endif

        perror("connect failed");
        close(this->master_socket);
   }
   #if DEBUG
   else
        printf("Connection successful\n");
   #endif
//}}}
}

void NC_Client::Send(unsigned char *data, int bytes)
{
    send(this->master_socket, data, bytes, 0);
}

int NC_Client::Receive(unsigned char *buffer, int bytes)
{
    return read(this->master_socket, buffer, bytes);
}

