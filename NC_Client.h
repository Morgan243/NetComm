#include "NetComm.h"

class NC_Client : public NetComm
{
    private:

    public:
        explicit NC_Client();
        explicit NC_Client(std::string address, unsigned int port);
        ~NC_Client();

        void Connect();

        void Send(unsigned char *data, int bytes);

        int Receive(unsigned char *buffer, int bytes);
};

