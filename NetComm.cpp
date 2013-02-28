//Network class for abstracting the low level BSD C sockets

#include "NetComm.h"

using namespace std;


#define SERVER_IP "192.168.1.66"
#define PORT 2337

NetComm::NetComm()
{

    if( SocketFD == -1)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(stSockAddr));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(PORT);
    res = inet_pton(AF_INET, SERVER_IP, &stSockAddr.sin_addr);

   if( res < 0)
   {
        perror("error: first parameter not valid");
        close(SocketFD);
        exit(EXIT_FAILURE);
   }
   else if (res == 0)
   {
        perror("char string error");
        close(SocketFD);
        exit(EXIT_FAILURE);
   }

   if(connect(SocketFD,(struct sockaddr *)&stSockAddr, sizeof(stSockAddr)) == -1)
   {
        perror("connect failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
   }
}

//overload a bunch of different sends, yo
void NetComm::Send(unsigned char *data, int size)
{
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
}
