#include <iostream>
#include "NC_Client.h"

using namespace std;

int main(){
    unsigned char message[10] = "";

    NC_Client client("127.0.0.1", 2337);

    client.Connect();
    printf("%d bytes received\n",client.Receive(message, 6));
    printf("%s\n", message);
    usleep(1000);
    
    return 0;   
}
