#include <iostream>
#include "NetComm.h"

using namespace std;

int main(){
    NetComm server(1, "127.0.0.1", 2337);
    server.Listen();
    while(1){}
    









    return 0;   
}
