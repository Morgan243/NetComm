#include <vector>
#include "NetComm.h"



struct ClientDesc
{
    int socket_fd;
    char *temp_buffer;
    std::string name;
};

class NC_Server : public NetComm
{
    private:
        int backlog_length;                                             //number of allowed pending connections

        ClientDesc temp_client;                                         //used for new clients until pushed back to connected clients
        std::vector<ClientDesc> connected_clients;                      //clients connected and being handled by threads

        bool SetClientName(int client_id, std::string client_name);
        int FindClient(std::string client_name);

    public:
        explicit NC_Server();
        explicit NC_Server(int socket);
        explicit NC_Server(std::string address, unsigned int port);
        ~NC_Server();

        //returns number of bytes read as ending (should a buffer reference be added?)
        int EndClientConnection(int client_id);
        int EndClientConnection(std::string client_name);
        void EndAllConnections();

        //seupt master socket to listen
        void Listen();
        void Listen(int connBacklog);

        //block to accept a single connection
        int Accept();

        //send a char array to a client
        int Send(unsigned char *data, int bytes);                      //defaults to last client (.back())
        int Send(unsigned char *data, int bytes, int client_id);
        int Send(unsigned char *data, int bytes, std::string client_name);

        //receive into a buffer
        int Receive(unsigned char *buffer, int bytes);
        int Receive(unsigned char *buffer, int bytes, int client_id);
        int Receive(unsigned char *buffer, int bytes, std::string client_name);
        int Receive(std::string *buffer, int bytes, int client_id);     //uses temp_buffer for actual read call
};
