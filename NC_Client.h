#include "NetComm.h"

class NC_Client : NetComm
{
    private:

    public:
        NC_Client();
        NC_Client(std::string address, unsigned int port);
        ~NC_Client();

        void Connect();

        void Send(unsigned char *data, int bytes);

        int Receive(unsigned char *buffer, int bytes);
};

