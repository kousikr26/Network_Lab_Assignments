// DNS server 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


char input_buffer[1024] = {0};
char output_buffer[1024] = {0};

void reply_dns(int new_socket){
    char IP_address[1023];
    char domain[1023];
    int flag;
    FILE *data_fp;
    if (input_buffer[0] == '1' || input_buffer[0] == '2')
    {
        //Database scanned and response message sent if found
        flag = 0;
        data_fp = fopen("database.csv", "r");
        while (fscanf(data_fp, "%[^,],%[^\n]\n", domain, IP_address) != -1)
        {
            //Response message contains Domain name, requesting IP address
            if (input_buffer[0] == '1')
            {
                if (strcmp(domain, input_buffer + 1) == 0)
                {
                    flag = 1;
                    output_buffer[0] = '3';
                    for(int i=0;i<strlen(IP_address);i++){ // Add IP to output buffer
                        output_buffer[i+1]=IP_address[i]; 
                    }
                   
                    send(new_socket, output_buffer, strlen(output_buffer), 0);
                    break;
                }
            }
            //Response Message contains IP address, Requesting domain name
            else
            {
                if (strcmp(IP_address, input_buffer + 1) == 0)
                {
                    flag = 1;
                    output_buffer[0] = '3';
                    strcat(output_buffer, domain); //Concatenate the response type with the response message(domain name)
                    send(new_socket, output_buffer, strlen(output_buffer), 0);
                    break;
                }
            }
        }
        fclose(data_fp);

        //If the entry does not exist in the database, then send a not found message
        if (flag == 0)
        {
            strcpy(output_buffer, "4entry not found in the database");
            send(new_socket, output_buffer, strlen(output_buffer), 0);
        }
    }
    else
    {
        strcpy(output_buffer, "4please correct the packet format");
        send(new_socket, output_buffer, strlen(output_buffer), 0);
        printf("The packet format received is wrong");
    }
    printf("Type:%c Response Message: %s\n", output_buffer[0], output_buffer + 1);
    printf("\n");
    close(new_socket);
    
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage : ./dns_server ");
        return 0;
    }
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    
    int opt = 1;
    int addrlen = sizeof(address);

    int port=atoi(argv[1]);
    
    
    pid_t childPid;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Setting socket options to allow reuse of Port and DNS address
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Socket options failure");
        exit(1);
    }

    //Setup of IP address and Port of the DNS server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind to given address and port failed");
        exit(1);
    }
    //Listening on the socket created
    if (listen(server_fd, 3) < 0)
    {
        perror("Listening error");
        exit(1);
    }
    
    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(1);
        }
        printf("Connection accepted\n");

        memset(&input_buffer, '\0', 1024);
        memset(&output_buffer, '\0', 1024);
        read(new_socket, input_buffer, 1024);
        printf("Query Type: %c, Query Message: %s\n", input_buffer[0], input_buffer + 1);
        reply_dns(new_socket);
      
    }

    return 0;
}
