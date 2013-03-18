#include "NetComm.h"

class NC_Client : public NetComm
{
    private:

    public:
        explicit NC_Client();
        explicit NC_Client(std::string address, unsigned int port);
        virtual ~NC_Client();

        //connect to specified address:port
        void Connect();

        //send data overloads
        void Send(unsigned char *data, int bytes);
        void Send(char *data, int bytes);
        void Send(const char *data, int bytes);

        //receive data overloads
        int Receive(unsigned char *buffer, int bytes);
        int Receive(std::string *buffer, int bytes);
};
