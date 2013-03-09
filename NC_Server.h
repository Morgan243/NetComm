#include <vector>
#include "NetComm.h"

struct ClientDesc
{
    int socket_fd;
    std::string name;
};

class NC_Server : public NetComm
{
    private:
        int backlog_length;

        ClientDesc temp_client;
        std::vector<ClientDesc> connected_clients;

        bool SetClientName(int client_id, std::string client_name);
        int FindClient(std::string client_name);

    public:
        explicit NC_Server();
        explicit NC_Server(int socket);
        explicit NC_Server(std::string address, unsigned int port);
        ~NC_Server();

        void Listen();
        void Listen(int connBacklog);

        int Accept();

        void Send(unsigned char *data, int bytes);
        void Send(unsigned char *data, int bytes, int client_id);
        void Send(unsigned char *data, int bytes, std::string client_name);

        int Receive(unsigned char *buffer, int bytes);
        int Receive(unsigned char *buffer, int bytes, int client_id);
        int Receive(unsigned char *buffer, int bytes, std::string client_name);
        int Receive(std::string *buffer, int bytes, int client_id);

};
