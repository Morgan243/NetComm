#include "NC_Server.h"

using namespace std;

NC_Server::NC_Server()
{}

NC_Server::NC_Server(int socket) 
                : NetComm(socket)
{}

NC_Server::NC_Server(string address, unsigned int port) 
                : NetComm(true, address, port)
{}

NC_Server::~NC_Server()
{
//{{{
    #if DEBUG
        cout<<"Shuting down socket!!"<<endl;
    #endif

    //shutdown all the clients connections
    EndAllConnections();

    //begin shutdown
    shutdown(master_socket, SHUT_RDWR);

    //make sure to read everything
    while(Receive((unsigned char *)temp_buffer,1024) > 0);

    close(master_socket);
//}}}
}

int NC_Server::EndClientConnection(int client_id)
{
//{{{
    #if DEBUG
        cout<<"Shuting down socket!!"<<endl;
    #endif

    //begin shutdown
    shutdown(connected_clients[client_id].socket_fd, SHUT_RDWR);

    //make sure to read everything
    while(Receive((unsigned char *)temp_buffer,1024, client_id) > 0);

    close(connected_clients[client_id].socket_fd);
//}}}
}

int NC_Server::EndClientConnection(string client_name)
{
//{{{
    int client_id = FindClient(client_name);

    if(client_id < 0 || client_id >= connected_clients.size())
    {
        cout<<"Error ending client connection named "<<client_name<<endl;
        return -1;
    }

    #if DEBUG
        cout<<"Shuting down socket!!"<<endl;
    #endif

    //begin shutdown
    shutdown(connected_clients[client_id].socket_fd, SHUT_RDWR);

    //make sure to read everything
    while(Receive((unsigned char *)temp_buffer,1024, client_id) > 0);

    close(connected_clients[client_id].socket_fd);
//}}}
}

void NC_Server::EndAllConnections()
{
//{{{
    #if DEBUG
        cout<<"Shuting all socket!!"<<endl;
    #endif

    //shutdown all the cilents sockets
    for(int i = 0; i < connected_clients.size(); i++)
    {
        //begin shutdown
        shutdown(connected_clients[i].socket_fd, SHUT_RDWR);

        //make sure to read everything
        while(Receive((unsigned char *)temp_buffer,1024, i) > 0);

        close(connected_clients[i].socket_fd);
    }
//}}}
}

void NC_Server::Listen()
{
//{{{
    //listen on master socket
    listen(this->master_socket, this->backlog_length);

    #if DEBUG
        cout<<"Queue Length "<<this->backlog_length<<", Listening..."<<endl;
    #endif
//}}}
}

void NC_Server::Listen(int connBacklog)
{
//{{{
    //make sure queue length is up to date
    this->backlog_length = connBacklog;

    //listen on master socket
    listen(this->master_socket,this->backlog_length);

    #if DEBUG
        cout<<"Queue Length "<<this->backlog_length<<", Listening..."<<endl;
    #endif
//}}}
}

int NC_Server::Accept()
{
//{{{
    //need size of socket
    this->socket_length = sizeof(this->socket_address);

    #if DEBUG
        cout<<"Blocking on accept..."<<endl;
    #endif

    //accept a single connectiong ans store reutrned socket to temporary client struct
    temp_client.socket_fd = accept(master_socket, 
             (struct sockaddr *) &socket_address,
                                  &socket_length);


    //disable the nagle algorithm on the socket
    setsockopt(temp_client.socket_fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

    #if DEBUG
        cout<<"Accepted Connection..."<<endl;
    #endif

    //preset client name
    temp_client.name = "UNSET";

    //push updated temp client struct to vector of connected clients
    this->connected_clients.push_back(temp_client);

    this->connected_clients.back().temp_buffer = (char *)malloc(sizeof(char)*1024);

    //return the integer id of the now connected client
    return connected_clients.size() - 1;
//}}}
}

int NC_Server::Send(unsigned char *data, int bytes)
{
    return send(this->connected_clients.back().socket_fd, data, bytes, 0);
}

int NC_Server::Send(unsigned char *data, int bytes, int client_id)
{
    return send(this->connected_clients[client_id].socket_fd, data, bytes, 0);
}

int NC_Server::Send(unsigned char *data, int bytes, string client_name)
{
//{{{
    int client_id = FindClient(client_name);
    if(client_id >= 0)
    {
        return send(this->connected_clients[client_id].socket_fd, data, bytes, 0);
    }
    else
        cout<<"Unable to send, not such client..."<<endl;
//}}}
}

int NC_Server::Receive(unsigned char *buffer, int bytes)
{
    return read(this->master_socket, buffer, bytes);
}

int NC_Server::Receive(unsigned char *buffer, int bytes, int client_id)
{
    return read(this->connected_clients[client_id].socket_fd, buffer, bytes);
}

int NC_Server::Receive(unsigned char *buffer, int bytes, string client_name)
{
//{{{
    int client_id = FindClient(client_name);

    if(client_id >= 0)
        read(this->connected_clients[client_id].socket_fd, buffer, bytes);
    else
        cout<<"Cannot receive from a non-existent client..."<<endl;
//}}}
}

int NC_Server::Receive(string *buffer, int bytes, int client_id)
{
//{{{

    buffer->erase();

    //use private temp buffer, zero it out first
    bzero(connected_clients[client_id].temp_buffer, sizeof(connected_clients[client_id].temp_buffer));

    #if DEBUG
        cout<<"PRe-receive buffer: "<<connected_clients[client_id].temp_buffer<<", string is: "<< *buffer<<endl;
    #endif

    //receive into private temp buffer
    int bytes_recv =
        read(this->connected_clients[client_id].socket_fd, connected_clients[client_id].temp_buffer, bytes);

    #if DEBUG
        cout<<"RECEIVED "<<bytes_recv<<" BYTES IN NC SERVER: "<<connected_clients[client_id].temp_buffer<<endl;
    #endif

    //assign received characters to string
    *buffer = connected_clients[client_id].temp_buffer;

    //how much received
    return bytes_recv;
//}}}
}

bool NC_Server::SetClientName(int client_id, string client_name)
{
//{{{
    if(client_id < 0 || client_id > this->connected_clients.size() - 1)
    {
        cout<<"No client with that id exists..."<<endl;
        return false;
    }

    this->connected_clients[client_id].name = client_name;
    return true;
//}}}
}

int NC_Server::FindClient(std::string client_name)
{
//{{{
    for(int i = 0; i < this->connected_clients.size(); i++)
    {
        if(connected_clients[i].name == client_name)
            return i;
    }

    printf("Client not found in connected clients listing...\n");
    return -1;
//}}}
}
