                                                             CS 342 Network’s Lab 
                                                                  Assignment 3 
					                                           Application ID : 3 
	                                  Multi-Stage DNS Resolving System using Client-Server Socket programming

Group : 32
Members: 
Kousik Rajesh (180101094)
Drishti Chouhan (180101021)

     1)The client passes the request, which can be of two types:
a)Type 1 : Message Field contains Domain name and client requests for the corresponding IP address
b)Type 2: Message Field contains IP address and client requests for the corresponding domain name 

     2) The response received is also of two types: 
	a)Type 3: Message field contains Domain name/ IP address
	b)Type 4: Message field contains error message, “entry not found in the database”

     3)The cache in the proxy server stores the response of the DNS server, with the cache size being 3.
        The proxy server cache uses FIFO scheme to update its cache.


  Running the program:

Setting up :

Open three terminal windows
Compile proxy.c, dns_server.c and client.c in three terminal windows, using the commands:
gcc client.c -o client
gcc dns_server.c -o dns_server
gcc proxy_server.c -o proxy
The system running dns_server.c must contain database.csv, because the dns_server performs domain name and IP address lookups in this file.

Run “./dns_server 9000” on the first terminal.
(Format : ./dns_server <port between proxy server and DNS server>)

Run “./proxy 8000 9000” in the second terminal. 
Format: ./proxy < Port between client and proxy server> <Port between proxy and DNS>

Run “./client” <IP address of proxy server> 8000” in the third terminal. If the proxy is being hosted on the same system, enter “./client 127.0.0.1 8000 "
Format: ./client  <IP address of proxy server> <Port between client and proxy server>

Now enter the request in to the terminal running “./client”:
Type 1 example: 
Enter type(1/2) or enter 0 to quit: 1
Enter Domain/IP : google.com
	
	Type 2 example: 
Enter type(1/2) or enter 0 to quit: 2
Enter Domain/IP : 172.217.12.238

After each query of client and proxy server the socket connection is gracefully closed from both sides releasing the socket resource.
