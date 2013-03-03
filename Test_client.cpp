#include <iostream>
#include "NetComm.h"

using namespace std;

int main(){
    unsigned char message[10] = "";

    NetComm client(0, "127.0.0.1", 2337);
    client.Connect();
  //  while(1)
  //  {
        printf("%d bytes received\n",client.Receive(message, 6));
        printf("%s\n", message);
        usleep(1000);
  //  }
    
    return 0;   
}
