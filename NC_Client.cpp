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
//{{{
    #if DEBUG
    cout<<"Shuting down socket!!"<<endl;
    #endif

    //begin shutdown
    shutdown(master_socket, SHUT_RDWR);

    //make sure to read everything
    while(Receive((unsigned char *)temp_buffer,1024) > 0);

    close(master_socket);
//}}}
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
    cout<<"unsigned CHAR send: "<<data<<"doNE"<<endl;
    send(this->master_socket, data, bytes, 0);
}

void NC_Client::Send(char *data, int bytes)
{
    cout<<"CHAR send: "<<data<<"dOnE"<<endl;
    send(this->master_socket, data, bytes, 0);
}

void NC_Client::Send(const char *data, int bytes)
{
    cout<<"CONST send: "<<data<<"(DoNe)"<<endl;
    cout<<"Sent "<<send(this->master_socket, data, bytes, 0)<<" bytes"<<endl;
}

int NC_Client::Receive(unsigned char *buffer, int bytes)
{
    return read(this->master_socket, buffer, bytes);
}

int NC_Client::Receive(string *buffer, int bytes)
{
//{{{
    //zero out temp buffer
    bzero(this->temp_buffer, sizeof(temp_buffer));

    //receive into temp buffer
    int bytes_recv =
        read(this->master_socket, this->temp_buffer, bytes);

    //string is set to character array
    *buffer = this->temp_buffer;

    return bytes_recv;
//}}}
}
