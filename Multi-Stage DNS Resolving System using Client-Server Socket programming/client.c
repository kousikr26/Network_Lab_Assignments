// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char in_buffer[BUFFER_SIZE] = {0};
char out_buffer[BUFFER_SIZE] = {0};

//the queryDNS function performs the sending and receiving actions to and from the server
void queryDNS(int sock, int queryType, char *query)
{

    memset(&out_buffer, '\0', BUFFER_SIZE);
    //For request Type 1, the client sends a Domain name and requests for corresponding IP address
    if (queryType == 1)
    {
        out_buffer[0] = '1';

        for (int i = 1; i <= strlen(query); i++)
        {
            out_buffer[i] = query[i - 1];
        }

        //print the buffer
        printf("Sending %s\n", out_buffer);
        //sending message to server
        send(sock, out_buffer, strlen(out_buffer), 0);
    }
    //For request Type 2, the client sends an IP address and requests for corresponding Domain name
    else if (queryType == 2)
    {
        out_buffer[0] = '2';
        for (int i = 1; i <= strlen(query); i++)
        {
            out_buffer[i] = query[i - 1];
        }
        //print the buffer
        printf("Sending %s\n", out_buffer);
        //sending message to server
        send(sock, out_buffer, strlen(out_buffer), 0);
    }

    //Reading the message received from the server into the buffer
    read(sock, in_buffer, BUFFER_SIZE);

    if (in_buffer[0] != '4')
    {
        //print the response from the in_buffer
        printf("Response %s \n", in_buffer + 1);
    }

    //If the response Type is 4, the server database does not contain the requested entry
    else if (in_buffer[0] == '4')
    {
        printf("Received type 4: Entry not found in database\n");
    }

    return;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage : ./proxy_server <CLIENT_PORT>");
        return 0;
    }
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

   

    serv_addr.sin_family = AF_INET;            // AF_INET is the IP address family used for the socket
    serv_addr.sin_port = htons(atoi(argv[2])); /* Port of the server provided by the user. 
                                                  htons() translates a short integer from host byte order to network byte order*/

    // Convert IPv4 and IPv6 addresses from text to binary form
    //If false server IP address(argv[1]) is stored in serv_addr.sin_addr
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    
    while (1)
    
    {
        /* Create a socket point */
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            //sock_stream is the socket type used by TCP
            printf("\n Socket creation error \n");
            return -1;
        }
        //the connect function is used by the client to establish a connection with the server
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }
        int type = 0;
        char message[BUFFER_SIZE] = {0};
        //empty current buffers for new messages to be received and sent
        memset(&in_buffer, '\0', BUFFER_SIZE);
        memset(&message, '\0', BUFFER_SIZE);
        printf("Enter type(1/2) or enter 0 to quit: ");
        scanf("%d", &type);
        if(type!=1 && type!=2){
            printf("Quitting \n");
            return 0;
        }
        printf("Enter domain/IP : ");
        scanf("%s", message);

        //the queryDNS function performs the sending and receiving actions to and from the server
        queryDNS(sock, type, message);
        
        close(sock);

    }

    return 0;
}
