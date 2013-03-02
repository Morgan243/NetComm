//Network class for abstracting the low level BSD C sockets

#include "NetComm.h"

using namespace std;

#define DEBUG 1

#define SERVER_IP "192.168.1.66"
#define PORT 2337

NetComm::NetComm()
{
    SetupSock();
}

NetComm::NetComm(bool isListener, string addr, unsigned int port)
{
//{{{
    if(isListener)
        this->isListener = true;
    else
        this->isClient = true;

    SetupSock();

    //host to network byte order
    sockAddrIn.sin_port = htons(port);

    //convert the address to binary form
    int res = inet_pton(AF_INET, addr.c_str(), &sockAddrIn.sin_addr);

        //check for errors in conversion
       if( res < 0)
       {
            perror("error: first parameter not valid");
            close(SocketFD);
       }
       else if (res == 0)
       {
            perror("char string error");
            close(SocketFD);
       }

   //is CLIENT 
   if(!isListener)
   {
       this->isClient = true;
   }
   //else, IS a SERVER
   else
   {
        //pair socket fd with a port 
        if(bind(SocketFD, (struct sockaddr *) & sockAddrIn, sizeof(sockAddrIn)) < 0)
            perror("Error on bind!");
        else
            this->isListener = true;
   }
//}}}
}

int NetComm::SetupSock()
{
//{{{
    SocketFD = socket(PF_INET, SOCK_STREAM, 0);

    if( SocketFD == -1)
    {
        perror("cannot create socket");
        //exit(EXIT_FAILURE);
    }

    memset(&sockAddrIn, 0, sizeof(sockAddrIn));

    sockAddrIn.sin_family = AF_INET;
//}}}
}

void NetComm::Connect()
{
   if(connect(SocketFD,(struct sockaddr *)&sockAddrIn, sizeof(sockAddrIn)) == -1)
   {
        #if DEBUG
            printf("CONNECTION ERROR!\n");
        #endif

        perror("connect failed");
        close(SocketFD);
   }
   #if DEBUG
   else
        printf("Connection successful\n");
    #endif
}

void NetComm::Listen()
{

    listen(SocketFD,this->queueLength);
}

void NetComm::Listen(int connBacklog)
{

}

//overload a bunch of different sends, yo
void NetComm::Send(unsigned char *data, int size)
{
//{{{
    send(SocketFD, data, sizeof(data),0);

       //while(1)
       //{
           //old stuff from lab 3, here for reference!!
            //bzero(freq, sizeof(char)*freq_i);
            //bzero(peak, sizeof(char)*peak_i);
           

            //printf("\nEnter Wave Selection (sine or square):");
            //scanf("%s",wave);

            //if(!strcmp(wave,"sine"))
            //{
            //    wave_id = '0';
            //    printf("You selected SINE wave\n");
            //}
            //else if(!strcmp(wave,"square"))
            //{
            //    wave_id = '1';
            //    printf("You selected SQUARE wave\n");
            //}
            //else
            //    printf("unknown wave: %s\n", wave);
         
            //printf("Enter the desired frequency (1 to 1000 Hz):");
            //scanf("%s", freq);
            //printf("You entered: %s\n", freq);

            //printf("Enter the desired amplitude (.1 to 5 V):");
            //scanf("%s", peak);
            //printf("You entered: %s\n", peak);

            //receive wave id
            //send (SocketFD, &wave_id, sizeof(wave_id), 0);
            //receive frequency
            //send (SocketFD, freq, sizeof(char)*freq_i, 0);
            //receive peak voltage
            //send (SocketFD, peak, sizeof(char)*peak_i, 0);
       //}
//}}}
}
