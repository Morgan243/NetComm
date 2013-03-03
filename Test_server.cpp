#include <iostream>
#include "NetComm.h"

using namespace std;

int main(){
    unsigned char message[10] = "Hello!";

    NetComm server(1, "127.0.0.1", 2337);
    server.Listen();
    server.Accept();
    //while(1)
    //{
        server.Send(message, 6);
        usleep(1000);
    //}
    
    return 0;   
}
