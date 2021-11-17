// Proxy server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define RECORD_SIZE 100
#define CACHE_SIZE 3

#define DNS_IP "127.0.0.1"
int DNS_PORT;
//struct record stores domain name and IP address of each entry
struct record
{
    char ip[RECORD_SIZE];
    char domain[RECORD_SIZE];
    struct record *next;
};

char error_message[] = "Did not find record";

//Declaring the proxy cache
struct record *cache = NULL;

char in_buffer[1024] = {0}, out_buffer[1024] = {};
char buffer[1024] = {0};

int connect_send()
{

    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    //Create a socket point for the proxy to connect to the DNS
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DNS_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, DNS_IP, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    //Connecting to DNS
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, in_buffer, strlen(in_buffer), 0);
    valread = read(sock, buffer, 1024);
    
    close(sock);
    return 1;
}
void add_entry()
{
    
    //Allocate space for a new entry
    struct record *new_record = malloc(sizeof(struct record));

    memset(&(new_record->domain), '\0', RECORD_SIZE); //setting up the buffer for the new record
    memset(&(new_record->ip), '\0', RECORD_SIZE);
    new_record->next = NULL;

    //If the Request type is 1, add the client requested domain name to the domain field
    if (in_buffer[0] == '1')
    {
        for (int i = 1; i < strlen(in_buffer); i++)
        {
            new_record->domain[i - 1] = in_buffer[i];
        }
    }
    //If the Request type is 2, add the client requested IP address to the address field
    else if (in_buffer[0] = '2')
    {
        for (int i = 1; i < strlen(in_buffer); i++)
        {
            new_record->ip[i - 1] = in_buffer[i];
        }
    }
    else
    {
        printf("Invalid \n");
    }
    //DNS database contains requested entry and cache has to be updated
    if (buffer[0] == '3')
    {
        //Add the IP address as returned by the DNS
        if (in_buffer[0] == '1')
        {
            for (int i = 1; i < strlen(buffer); i++)
            {
                new_record->ip[i - 1] = buffer[i];
            }
        }
        //Else add the domain name as returned by the DNS
        else
        {
            for (int i = 1; i < strlen(buffer); i++)
            {
                new_record->domain[i - 1] = buffer[i];
            }
        }
        int cache_occupied = 0;
        new_record->next = cache;
        cache = new_record;
       
        struct record *iterator = cache;
        
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
            cache_occupied++;
        }
        /*The cache has to be updated according to the FIFO scheme. 
        So if the cache is full, the oldest entry entry is replaced by the new record*/
        if (cache_occupied >= CACHE_SIZE)
        {

            iterator = cache;
            cache_occupied = 1;
            while (cache_occupied != CACHE_SIZE)
            {
                iterator = iterator->next;
                cache_occupied++;
            }
            free(iterator->next);
            iterator->next = NULL;
        }
        
    }
}

//Searches the proxy cache for the requested IP/domain
int search(int sock, char *request)
{
    int type = request[0] - '0';

    
    struct record *iterator = cache;
    while (iterator != NULL)
    {
        //searches cache for the domain name sent by the client
        if (type == 1)
        {
            if (strcmp(iterator->domain, request + 1) == 0)
            {
                //domain name present in proxy cache
                printf("Cache hit for %s \n", iterator->domain);
                memset(out_buffer, '\0', 1024);
                out_buffer[0] = '3';
                for (int i = 0; i < strlen(iterator->ip); i++)
                {
                    out_buffer[i + 1] = iterator->ip[i];
                }
                
                send(sock, out_buffer, strlen(out_buffer), 0);
                return 1;
            }
        }
        //searches cache for the IP address sent by the client
        else if (type == 2)
        {

            if (strcmp(iterator->ip, request + 1) == 0)
            {
                //IP address present in proxy cache
                printf("Cache hit for %s \n", iterator->ip);
                memset(out_buffer, '\0', 1024);
                out_buffer[0] = '3';
                for (int i = 0; i < strlen(iterator->domain); i++)
                {
                    out_buffer[i + 1] = iterator->domain[i];
                }
                send(sock, out_buffer, strlen(out_buffer), 0);
                return 1;
            }
        }
        else
        {
            printf("Invalid type received \n");
        }
        iterator = iterator->next;
    }
    //The entry does not exist in the proxy cache and a request has to be sent to the DNS server
    printf("Request %s Not found in cache requesting DNS server\n", request);
    return 0;
}

//Handles queries received by the proxy server from the client
void handle_query(int sock)
{
    //request type query
    if (in_buffer[0] == '1' || in_buffer[0] == '2')
    {
        int cache_hit = search(sock, in_buffer); //returns true if the proxy cache contains requested IP address/domain name
        if (!cache_hit)
        {
            connect_send(); //else connect to the DNS

            if (buffer[0] == '4') //The DNS server database does not contain requested entry
            {
                memset(out_buffer, '\0', 1024);
                out_buffer[0] = '4';
                for (int i = 0; i < strlen(error_message); i++)
                {
                    out_buffer[i + 1] = error_message[i];
                }
                send(sock, out_buffer, strlen(out_buffer), 0);
            }
            else
            {
                add_entry(); /* The DNS server responds with a Type 3 response message 
                                                            if the entry exists in database.csv. 
                                                            The cache is updated with this records */
                cache_hit = search(sock, in_buffer);
                if (!cache_hit)
                {
                    printf("Somethings wrong\n");
                }
            }
        }
    }
    else
    {
        printf("Invalid query \n");
    }
}

int main(int argc, char const *argv[])
{
    
    if(argc<2){
        printf("Usage : ./proxy <CLIENT_PORT>");
        return 0;
    }
    DNS_PORT=atoi(argv[2]);
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    pid_t childPid;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Setting socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1]));

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("Bind to given address and port failed");
        exit(1);
    }
    //Listening on the socket
    if (listen(server_fd, 3) < 0)
    {
        perror("Listening error");
        exit(1);
    }
   
    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(1);
        }
        printf("Waiting for query \n");
        valread = read(new_socket, in_buffer, 1024);
        printf("Received type %c \nquery %s\n\n", in_buffer[0], in_buffer + 1);
        handle_query(new_socket);
        memset(&in_buffer, '\0', 1024);
        close(new_socket);
    }

    return 0;
}
