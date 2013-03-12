#include <iostream>
#include "NC_Server.h"

using namespace std;

int main(){
    unsigned char message[10] = "Hello!";

    NC_Server server("127.0.0.1", 2337);

    server.Listen();
    server.Accept();
    server.Send(message, 6);
    usleep(1000);
    
    return 0;   
}
