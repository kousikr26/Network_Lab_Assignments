# Networks_lab_implementations
Assignments done as part of labwork in CS342: Computer Networks Laboratory

**This markdown has been generated from a doc file, please ignore the bad formatting**

## Linux Network commands
**Q.1**

1. **-c &lt;count> :**_ping -c &lt;count> &lt;IP>_
2. **-i** &lt;**interval> :**_ping -i &lt;interval> &lt;IP>_
3. **ping -l &lt;preload> &lt;host>**

Normal user is limited to**max 3**ECHO_REQUEST(_preload_) packets

4. **ping -s &lt;size> &lt;host>**

_ICMP header is of 8 bytes_. Total packet size = payload size + header size

Hence total size**32+8 = 40 bytes**







Q.2**a)**

| **Host Name**                                               | **Average RTT** | **Location** | **Distance(km)** |                         |       |
| ----------------------------------------------------------- | --------------- | ------------ | ---------------- | ----------------------- | ----- |
| **01:30**                                                   | **12:15**       | **23:00**    |                  |                         |       |
| [flipkart.com/](https://www.flipkart.com/)                  | 47.920          | 48.760       | 46.295           | Bengaluru, India        | 1741  |
| [udp.jp/](http://udp.jp/)                                   | 147.253         | 146.446      | 174.317          | Kita-ku, Japan          | 5840  |
| [gunjap.net/](https://www.gunjap.net/)                      | 188.608         | 170.653      | 222.931          | Arezzo, Italy           | 5916  |
| [programmingwithmosh.com/](http://programmingwithmosh.com/) | 119.866         | 120.300      | 147.991          | North Perth, Australia  | 7877  |
| [yuppiechef.com/](http://yuppiechef.com/)                   | 452.023         | 440.507      | 473.727          | Cape Town, South Africa | 7998  |
| [amazon.com/](https://www.amazon.com/)                      | 264.400         | 255.504      | 294.830          | Ashburn, USA            | 12045 |

 
![](https://lh5.googleusercontent.com/iL-8xVl7CPUqFBWZU6g3qb3CBy3P11AaZfP5zb_BxQ5XB_D2y1Efkll3CKqYBKwwWzholItASaBry3pvYJylV-1Bv2FsKxDrVbBI2V6Soo-li2CKILgaSK04J4QtrowAiZt1dA6Q)**

There is**no strong correlation of RTT with geographical distance** as shown in the plot. This is due to the use of CDN’s as proxy servers


**b) None of the hosts suffered packet loss** indicating that the network was in perfect working condition.

If there were any packet loss it could be due to a congestion in the network, server down, faulty hardware or software bugs.



**c) Using host**[udp.jp/](http://udp.jp/)


**d) Time of day:**There is some correlation between time

of day and Avg RTT. At 23:00 Hours(11:00 PM) almost all the hosts![](https://lh4.googleusercontent.com/BzONRJDCCmBgGMitlWSAxLIElkmkrwEZQGP05iCFEZK2T8Fov1yRAIpbj9jtIEPEF7A58fkC_-oFPjV_6szJ1et0tDlkyTF4oYSAtatxbGtVhGt8rDqG9Z3-aIVop0xJ0YK9xy2I)

had 10-20% higher RTT than other times which could be indication of

high network congestion



**Packet Size:**There is no direct correlation observed between packet size and RTT possibly because the propagation time dominates the data transfer time. However when size exceeds MTU the packet is broken down into 2 frames.





Q.3**Chosen IP address : 172.16.114.188**

**a) b)**

|                                 | **Packet loss(%)** | **Minimum (ms)** | **Maximum (ms)** | **Mean (ms)** | **Median (ms)** | **Standard Deviation(ms)** |
| ------------------------------- | ------------------ | ---------------- | ---------------- | ------------- | --------------- | -------------------------- |
| **ping -n 172.16.114.188**      | **0.8%**           | **114**          | **196**          | **122.85**    | **122.0**       | **8.06**                   |
| **ping -p ff00 172.16.114.188** | **1.9%**           | **92.3**         | **400**          | **101.7**     | **99.85**       | **14.43**                  |



![](https://lh3.googleusercontent.com/BnK9Pxrjz2mLRfM_As7soVqnypJb7vS-iIlJ_mhIYgUr9j-zdVdhq7sYejzk90B4TDZIR9YQu3fO_IVnr9XBdPaKku-56nBeQMppUBcvx_bCLC4G-YFfvbsTrJBY_2MNR1WQO5Lv) ![](https://lh4.googleusercontent.com/yPakc7IvjWitkPDs5IFNSzHobYlEhLVlKHA759hGd488pr62DtAMSUt5T7OSrfaD3FG61lsBDdrTMf_B3iOQv_hzz3BGlhdewk7x90N9l6seU720Vajh-xj-nszGUhog5xBHGsCC)

**Fitting them to a normal curve**

![](https://lh3.googleusercontent.com/ERl4ThJBTmGtD40Pe93hZPz9TQM-Q6GZw-tHCfzLD7ZQolQOiOEwEUcbfShmltsGJ5yw6vHQu8czv6B7YNKcO36uh3Cv25_8d_6t55ESlhcV3rrj_2lgtgjGvxZ-OPoWU1lCJOy0)**

- Both commands have a normal distribution of latency
- **Ping -n has a higher mean and lower variance** than the other


- The -p ff00 packet contains 1111111100000000 since only one transition is present in the padding (from high to low) clocks are more likely to go out of synchronization and we observe a higher packet loss.


**Q.4**

1. The**ifconfig** config outputs all the network devices present and some statistics on them

**Eno1 :**The physical interface representing Ethernet network card

**Lo :**The loopback interface which acts as a virtual network device used to run network services such as web servers locally for debugging and testing.


**Statistics****  


**inet :**IP address

**Netmask** : Subnet mask

**Ether** : Mac Address

**Txqueuelen**: Length of transmission queue.

**RX/TX packets**: # of packets

**RX/TX errors** : # of packets with error

**RX/TX dropped**: # of dropped packets

**RX/TX overruns**: # of packets that experienced fifo overruns

**RX/TX frame** : # of misaligned frames  



b)**Options**

**Up - ( ifconfig up &lt;interface> )**Activates an interface if not already up

**Down - ( ifconfig down &lt;interface> )** - Deactivates the specified interface if it is currently up

**Mtu N** - **( ifconfig &lt;interface> mtu &lt;new_mtu>) -**Sets the maximum transfer unit (mtu) of an interface

**Arp**-**( ifconfig &lt;interface> arp)**(Enable the use of arp protocol in this interface

c)**Route**

Route command**displays the IP routing table**. The routing table contains info on how packets should be transferred or how the hops would take place. It shows the**network path to all nodes** or devices within a network. It acts as a map for packets. Using the route command we can** view and manipulate** the routing table



**Destination** : Destination network/host

**Gateway :**Gateway address

**Genmask :**The netmask of the destination network


**Flags :**

**U :**Route is up

**G** : Route is to a gateway

**H** : Target is a host  


d)

- **Add :**route add &lt;destination> gw &lt;gateway> (Adds a route)
- **Del :**route del &lt;destination> (Deletes a route)
- **host**: used to denote the target is a host.
- **mss :**Set the Maximum Transmission Unit(MTU)

![](https://lh5.googleusercontent.com/HMnz2jx-XZO10pHEmiwV4MurMp9kepOpdS-E94vKG4ubBSY266jUclcdR9PBceoLz0h0K36gFHOCffNFlx2322pJS8mSJW9G_G0EF63BcLrVYDBkn__86JJM_OuQlZtW6xHTlffE)


Q.5

a) The **netstat** command displays various statistics on network connections(TCP/UDP/UNIX) and their status. It can also be used to display routing tables, interface statistics, protocol statistics, internal connections(UNIX type), masquerade connections, and multicast memberships



b)** netstat -at | grep ESTABLISHED****  
**![](https://lh5.googleusercontent.com/7VN-nUzq6bc0IIQcpLak8Vp-upaEXIYcg8w3N9P-TqsCXawGERIn3scftoewwcZwkd17p61de7J7Rdvnz30rtQNP2WPukbSV0v2Pq3X84z7-71f1WvhAcuhA_q8oD3v7U-fnBKXl)**


c)** netstat -r **shows the IP routing table which acts as a map and is used in computing the next hop for a packet.



**Destination**: Destination network/host

**Gateway:**Gateway address

**Genmask:**The netmask of the destination network



**Flags :**

******U:**Route is up

**G**: Route is to a gateway

**H**: Target is a host  


d)**Option : -i (displays network interfaces)**

**netstat -i | tail -n +3 |wc -l**

e)**netstat -asu**

![](https://lh3.googleusercontent.com/XHRmRwXES42fE4XZa3De2uqg0LUiwjwDicGw87C0jfVBUAMFJwZivGz_E-ZgXhltR26h3NEcvSYas3TvfCy8LlwnZCVwvbCqj7lucGztvQL9hQhuQrq6rPP885F7_ml7SIA3xDfa)![](https://lh4.googleusercontent.com/Fgq-pX8vi18D87fBY4qKl96Unr168ZYIEb5r4010RjYrgej1OV6PUBl1FMlWgKZygE-C3APmOVPB814oAGHDzkJMkZJ6Yiuzs0PXX_gBDwcIGhGdugjRcgKDTTc1m8t9Htym2pYy)

**_A django server running on the loopback device at 127.0.0.1_**



f)**lo**** is a loopback device**. It acts as a** virtual network device** that is on all systems, even if they aren't connected to any network. It has an IP address of 127.0.0.1 and can be used to** access network services locally**.**Running a web server** for debugging/testing locally will route it through this device to the address 127.0.0.1



Q.6 a)**traceroute**is used to identify the complete path a packet takes to reach a destination host. It is useful for debugging connection issues and localizing problems in network connectivity. It uses UDP by default to send packets to the host.

b)

| **Host Name**                                               | Hop count |       |     |
| ----------------------------------------------------------- | --------- | ----- | --- |
| 01:00                                                       | 18:00     | 22:00 |     |
| [flipkart.com/](https://www.flipkart.com/)                  | 9         | 9     | 9   |
| [programmingwithmosh.com/](http://programmingwithmosh.com/) | 11        | 11    | 11  |
| [udp.jp/](http://udp.jp/)                                   | 14        | 14    | 16  |
| [gunjap.net/](https://www.gunjap.net/)                      | 12        | 16    | 12  |
| [amazon.com/](https://www.amazon.com/)                      | \-        | 23    | \-  |
| [yuppiechef.com/](http://yuppiechef.com/)                   | 18        | 18    | 18  |

The highlighted lines are common in all traceroutes.

![](https://lh3.googleusercontent.com/vt_EElKzITKia_M84luTefpHXUjc3k4wuJXSj3hCpnLxFtp5MOmsrjwcsWzKRi5JpE0ydqRjE0JomT_is8CCLjLN34nh0Wf0VpwJWkICnWxKiX3-vc-ss8uNUhPqZKt1OPcGjDKT)

**1 192.168.1.1 :**Since the first hop of any packet will be to the router it’s IP will be common in all

**2 122.176.127.68 :**All packets will go through the ISP’s server(Airtel) hence it is also common

c) Yes. The route changed at different times this is because network load is different at each time and to balance load on the network routers and other devices route packets through different routes based on congestion

d) Traceroute did not find a path to amazon.com in my case this is because the**max number of hops are set at 30** after which the packet is dropped. It could be that to reach amazon’s server present in USA **more than 30 hops are required** (sometimes) which is why traceroute fails in such cases. It could also be the case that some firewall blocked the packets from reaching.

e)**YES,**some networks may block ICMP packets for security reasons using a firewall in such cases ping fails since it uses ICMP echo packets. However traceroute uses**UDP**packets by default which is a standard network protocol and it’s packets are not blocked by firewalls. In such cases traceroute is able to reach the host using its UDP packets while ICMP ping requests get blocked and fail to reach.



Q.7 a)**arp(** Address Resolution Protocol)** command** can dump/change the system ARP cache. It provides a mapping from **IP address to Mac address** and hence it works between level 2(Data link layer) and level 3(Network layer).



**arp -a :**Provides the complete ARP table on a machine

**IP Address** : This is what an incoming packet will contain

**Mac Address** : Arp provides the mapping of each IP to a mac addr

**Hardware type** : The type of network hardware

**Network Interface :**An ID uniquely identifying the network interface used

**![](https://lh3.googleusercontent.com/zP47NiZDMBkkEVId8KXoUMObJZdH8lm1O-R3sMx1nSnLChmUNLBNIPYbY2lp-bHurypmhnKuoohwSp6bNkEOsdpr_vzosjW3-mRf1scSxzg2mbscXu9ggpe6aB3IT5eH9cXVlRU_)**

b)**Add an entry : sudo arp -s &lt;ip_address> -i &lt;type of network interface> &lt;mac address>**

**Delete an entry : sudo arp -d &lt;ip_address>**

**![](https://lh3.googleusercontent.com/e7RV_BlbcfqQSttYa4E1COVQ-GvpmVYttZTHqCeDxbvEs3OVtg2NRQ7M5olfLfB-MBLqV9YyhIN68xI4FL0evd26hLliuH2IPMoUqAEQV6qqWexDI9rZpIMELiEM6hYBta63lfcm)**

c)**ARP only works between devices in the same IP subnet.**

When a machine wants to send a packet to a host it checks which subnet the host belongs to, If it is in the same subnet it finds the MAC address from the ARP table and sends the packet directly. If the host is on a different subnet the packet has to go through the subnet’s router. Hence the MAC address of the router is looked up in the ARP table and the packet is routed through it.



d)



| kousik@kousik:~$ ping 172.16.114.246 -c 1   PING 172.16.114.246 (172.16.114.246) 56(84) bytes of data.   64 bytes**from** 172.16.114.246: icmp_seq=1 ttl=64 time=0.843 ms   --- 172.16.114.246 ping statistics ---   1 packets transmitted, 1 received, 0% packet loss, time 0ms   rtt min/avg/max/mdev = 0.843/0.843/0.843/0.000 ms      kousik@kousik:~$ sudo arp -d 172.16.114.246      kousik@kousik:~$ sudo arp -s 172.16.114.246 -i eno1 a0:8c:fd:e6:92:7b   kousik@kousik:~$ ping 172.16.114.246 -c 1   PING 172.16.114.246 (172.16.114.246) 56(84) bytes of data.   --- 172.16.114.246 ping statistics ---   1 packets transmitted, 0 received, 100% packet loss, time 0ms |
| ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |



**Operation :**Force change MAC address of172.16.114.246 to that of another IP

There is** no error on forcefully changing the MAC address** however,

On pinging172.16.114.246 after forcefully changing MAC the ICMP request packet is sent to the incorrect ip address but when the IP of the new machine is compared with destination IP present in ICMP header and they don't match the packet is dropped and an ICMP echo packet is not sent. Hence we observe 100% packet loss on ping after switching the MAC address.


**Q.8**

1. ****Command : sudo nmap -sn**172.16.114.**_128_**/25******

The IP and subnet mask can be found using**_ip add_**command

**_Subnet mask :_**_ 255.255.255._**_128_**



2. ****sudo nmap -sA -T4 &lt;ip address>**![](https://lh4.googleusercontent.com/4WoxA-6IIEALiU9v-bVZLuBQaFCxAg6nng8NEqsnP1nwWYwcMEI8-pZiFQdJzEtcj3xW1DyKCkFnfHaGhAOQ2KmOGKlzhS0FGIMp4PxdT7pZgnl7rd0blOQpCpiXuQIXUBWXCA5n)**
3. 

| **Time** | **Number of PC’s up** |
| -------- | --------------------- |
| 01:50    | 85                    |
| 03:20    | 85                    |
| 15:50    | 85                    |
| 17:50    | 78                    |
| 18:20    | 83                    |
| 22:40    | 86                    |



## Wireshark Analysis of Skype

**Q.1 Protocols used**

**TCP**: Used to communicate to skype servers, call initiation, termination, messaging

**UDP**: Used for audio/video call from one node to another

**STUN**: Used for a binding request

**TLSv1.2**: Used for secure encrypted communication with the server

**DNS**: Used for a DNS lookup of skype servers![](https://lh3.googleusercontent.com/XdKRngZKOVRZue48kRjIdKIlHC4wqyGAe68QioVrGOdkpWi7EQ1LjXsSfp4O3IRD_-ePTROcoLZHRMvAqwOjPBewJqC68SOnh0iZsv-Fk1nW59ceMVw796cSPeTcpbKk7sZl7YV5)


**Link Layer**

**_Ethernet II:_**

1. **Source IP**
2. **Destination IP**
3. **Source MAC**
4. **Destination MAC**

**Network Layer**

**IPV4:**

1. **Differentiated Services Code Point (DSCP):**specifies differentiated services per RFC 2474.**
2. **Explicit Congestion Notification (ECN):**End to end congestion notification**
3. **Time To Live (TTL):**Time packet persists in the network**
4. **Protocol:**The protocol used in the data portion**
5. **Header Checksum:**Checksum to verify packet integrity**
6. **Source address**

**Transport Layer**

**_TCP/UDP_**

1. **Source port**
2. **Destination port**
3. **Checksum:**Checksum to verify packet integrity**
4. **Checksum status:**Verified/unverified**
5. **ACK and Sequence number( TCP )**


**Application Layer**

**_TLSv1.2 (Transport Layer Security)_**

Used to exchange application data or handshakes securely

1. ****Content-type**:**Application data**/ handshake data**
2. ****Version:**The TLS version**
3. ****Length:**Length of the packet![](https://lh3.googleusercontent.com/g9LPFnsg8lw2wIzXuFVb57sjVObSbgB8nccCRiYVGs445iNDv1ddyzze4lBVJsFoLGimKNjsL8qKbE2xGWkXCZnbAVvxt7GwMC8ceujlgxdwSYZaLctzgV868dOMtOG2S35ZvNkU)**
4. ****Encrypted Application Data****



**_DNS ( Domain Name System)_**

DNS lookup used to get domain of skype server

**Query/Response**

1. ****Transaction ID :** A unique id identifying the request**
2. ****Flags:**Flags for dns request**
3. ****Questions:**the number of questions asked in the message**
4. ****Queries:**All the queries for DNS lookup**
5. ****RRs:** resource records**



**STUN (Session Traversal Utilities for NAT)**![](https://lh6.googleusercontent.com/CDIYGT88ivxZRSkvCqZPsEcDM6aJEE45_aHCCpIcyoh1--5ZgbTYOO9TtyjHne5o0xpPBnFid2cJF4QT9ZQtARPWT-nNIyWnJ3BIbdBF5-uNnAaclJQIIij2CotRJ0v0EhPwHVpk)

STUN is used to resolve the public IP of a device running behind a NAT used in VoIP calls and to make binding requests

1. ****Message Type:**Allocate/Binding/Refresh request**
2. ****Length****
3. ****Cookie****
4. ****Transaction ID****



Q.2**Functionalities**

**Skype has a persistent TCP connection to the server which it maintains at all times. Hence most information can be conveyed through this TCP stream itself.**



1. ****Login authentication:****

Uses**DNS** on a UDP packet to lookup domain name for server, A **TCP** handshake follows and **TLS** is used to create a secure encrypted channel for authentication

2. ****Add contact:****

******TCP -**The persistent connection can be used, using**UDP** we would need to worry about packet loss and retransmission

3. ****Schedule call : TCP****
4. ****Initiate/terminate call : TCP, UDP, P2P****

******TCP**is used to initiate the call and**UDP** is used to transfer call data as it is a loss tolerant application and maintaining a connection is expensive



5. ****Send message****

**TCP** is used since we cannot afford loses

6. ****Create a poll : TCP****
7. **View profile : TCP**
8. ****Notifications : TCP****
9. ****Private chat (E2E encrypted) : TCP****

(**UDP** in case of private video/audio call)

10. ****VoIP call : P2P, UDP, TCP****
11. ****VoIP SMS : P2P, UDP, TCP****



Skype also pickles randomly from a wide range of ports so it is harder to be blocked by a firewall. This also makes it difficult to do port filtering on wireshark to remove noise from other running background processes.


Q.3

**_Application 1: Voice/Video call_**

Skype uses a proprietary video conferencing protocol based on**P2P(Peer to Peer) networking.**Assume a client**X** calls **Y**



Each logged-in user maintains a**persistent TCP connection** established with skype servers. When **X** makes a call to **Y,**the IP address of user**Y**is looked up from data stored on the server.

For**Y**this persistent connection is used to sound a ring when a call comes.



When a new call is initiated by**X**it**creates a new TCP connection**in addition to the persistent connection to the server, which will be**closed when the call is terminated**. This connection could be used as a**heartbeat mechanism to check if the call is still alive**. This is necessary as, during the call due to the** P2P** policy none of the packets go through the server, and hence it has no way of knowing if the call is still alive.


**_Handshake_**

![](https://lh4.googleusercontent.com/91x0WZlCtM3lvTn4DOMogUOqsxuohoDlWPbn0BAQoZCxIoLr-xpBN59S1l68sc7uSwzettmmlI0-V7RLRridkiVprd_GvKznix-WR9fzKKRqEiJEDOygipsgYXjk6g6KM7r5qclr)

Shown above is the trace for connection initiation which starts with a**SYN packet ( used for initiating a TCP connection)(Packet 57)**sent by client to the server. This is followed by the**Client Hello (Packet 64)**message to initiate the key exchange and the server responds with a**Server Hello(Packet 73)**which contains a**Certificate** to verify the authenticity of the server and completes the key exchange process. The encrypted channel is now established and a **new encrypted handshake is done through the encrypted channel** which exchanges important server information **(Packet 79)**.



Skype uses encryption on its calls hence** X** establishes a secure encrypted channel with **Y**with the help of the new encrypted TCP connection we just created using TLS.



Next,**X**makes a**STUN** binding request to **Y,**and**Y**returns a response with an**XOR mapped address.**

Now the connection is established.

Now the call has started. Using a**P2P protocol**the**UDP**packets of the call carrying video/audio are routed from**X** to **Y** without any server intervention.

**(Numeric IP’s have been renamed for clarity)**

**  
![](https://lh5.googleusercontent.com/PLTgZbMFFlE5H-ZP7kleGUxvd1QJvffnrn1U1tfCZ4WWFD1Lze3z9yySnwg3_r9jFAl8ifFTORLtH0X2MIJpJrFaDitbX-Z4X1evK7KT9kGZX-s4aOV-xyc_WZRY_SxBKiXJaLDB)**

**Client X initiates TCP connection with the server and communicates with** **the** **server to initiate a call to Y**


**Binding Request by X to Y**



**Binding Response by Y to X**

**  
![](https://lh5.googleusercontent.com/KJTHgWGvvC3QbBguwVuRglXfncxD8DahGG1v9sz7lVzNSHI6NV_nCO6YEK7E8NXvAi0WP3cKewATy0mbaYyCWvKhnYRtZJ33xJLdQshJIxNNlpt-SDfGD6J2ZrkuYQclvU67ZMxP)**

**Now since the connection is established the call continue using purely UDP packets**


**Termination**

The trace showing the connection termination is given below

**![](https://lh4.googleusercontent.com/AWSSH6qyGQeCbTKXJybk-ztzWNKL1jASXyJ6SLzvFGWDxUyXOfPi73ddnDVpVYx07GEQs7mbIGxU9J5AMCzcOO3jYtKjmY_5qtGB1YeIQhGDFaVB4lLPvvL1wFZp0X6lwe_X5Klz)**



The connection is terminated when the call ends by sending a**TCP \[FIN] packet.**

The**TCP RST packet**is indicating that a packet was attempted to be sent to a host connection which was previously closed/terminated.



**_Application 2: Messaging_**

For messaging skype** does not** use a **P2P policy. All communication happens solely with the server.**

The client** uses the already established encrypted persistent TCP connection** with the server to send messages which further sends it to the receiver using its secure TCP connection. No handshakes are observed as no new TCP connections are created

![](https://lh4.googleusercontent.com/uT1x8MayX5Kx1KUHFTAgKtu0Q5yHduSNy9-2mJdZFURlP0W9dz2HhhCRNEUJUO_8iKuZ4E7Cp-jvW6qIlHHSQR2SoqRpxTHzMIpDE2FBf4eyMMX_jUXTxQI-cyiXRqkgVqjAVdAb)

As shown above, the client sends the encrypted message using the secure TLS channel and receives ACK and some packets back from the server(Could possibly contain information such as sent/read receipts)


Skype also offers an**End-to-End encrypted** private channel for messaging/calls. The encryption and messaging mechanism is **based on the Signal Protocol**. The difference in the E2E channel is that initially when setup, it does a key exchange using DHKE to setup a shared secret channel that is closed to the server. From my analysis, I found that once such a channel is established the packet sequences are similar for both calls and messaging as the one given above. ( The only difference is that the messages are encrypted with the new E2E key which is not known to the server)



Q.4



| **Statistics**             | **Time**  |           |          |
| -------------------------- | --------- | --------- | -------- |
| **14:00**                  | **16:30** | **19:20** |          |
| **Throughput(bytes/s)**    | **160k**  | **27k**   | **134k** |
| **RTT(ms)**                | **184**   | **230**   | **107**  |
| **Packet size(Bytes)**     | **676**   | **247**   | **611**  |
| **Number of packets lost** | **3**     | **7**     | **3**    |
| **UDP Packets**            | **10076** | **4267**  | **9088** |
| **TCP Packets**            | **264**   | **249**   | **259**  |
| **Response ratio**         | **0.77**  | **0.89**  | **0.84** |



**Q.5**

**Yes, multiple sources**exist. Some of them are  



| **Servers facilitating persistent connections** | **Servers facilitating video/audio calls** |
| ----------------------------------------------- | ------------------------------------------ |
| 20.185.212.106                                  | 52.114.6.1                                 |
| 40.77.18.167                                    | 52.114.15.57                               |
| 40.83.97.152                                    | 52.114.15.65                               |
| 40.114.211.99                                   | 52.114.77.164                              |
|                                                 | 52.114.128.71                              |
|                                                 | 52.149.21.60                               |
|                                                 | 52.114.159.22                              |
|                                                 | 52.247.2.90                                |


By observing I noticed that the sources on**the left** were used for the **persistent TCP connections**and the**right** ones(starting with 52) were initiated when a call was made.

**Reasons for multiple sources:**

- Skype has**multiple parallel TCP connections** for facilitating activities such as messaging, call alerts, video calls
- By**differentiating servers based on the type of requests**(messaging/calls) they receive, it gives more opportunity for them to**optimize the server** to handle those requests better
- Multiple servers also provide** load balancing**, prevent congestion on one server, and improves the quality of service
- A singles server is a**Single Point of Failure** and should be avoided



**Some Interesting Observations**

Since Skype uses a P2P protocol during a call between two devices on the same local network, connection to the Internet is not required. I tested this by creating a call between two devices connected to my WIFI router(locally connected). Wireshark showed the Local IP Address of both devices. Once the call was initiated (This part requires the internet as a new TCP connection is created with skype server) I turned off the internet access of my WIFI router and the call continued to work with no issues.

This kind of protocol removes unnecessary load from skype servers.



**_Files_**

**Dump_1400.pcapng**

**Dump_1630.pcapng**



**Dump_1920.pcapng**




## Multi-Stage DNS Resolving System using Client-Server Socket programming



1)The client passes the request, which can be of two types:

a)Type 1 : Message Field contains Domain name and client requests for the corresponding IP address

b)Type 2: Message Field contains IP address and client requests for the corresponding domain name


2) The response received is also of two types:

a)Type 3: Message field contains Domain name/ IP address

b)Type 4: Message field contains error message, “entry not found in the database”



3)The cache in the proxy server stores the response of the DNS server, with the cache size being 3.

The proxy server cache uses FIFO scheme to update its cache.


\#User Runflow:

Setting up :

1. Open three terminal windows
2. Compile proxy.c, dns_server.c and client.c in three terminal windows, using the commands:

- gcc client.c -o client
- gcc dns_server.c -o dns_server
- gcc proxy_server.c -o proxy

3. The system running dns_server.c must contain database.csv, because the dns_server performs domain name and IP address lookups in this file.
4. Run “./dns_server 9000” on the first terminal.

Format : ./dns_server &lt;port between proxy server and DNS server>


5. Run “./proxy 8000 9000” in the second terminal.

Format: ./proxy &lt; Port between client and proxy server> &lt;Port between proxy and DNS>



6. Run “./client” &lt;IP address of proxy server> 8000” in the third terminal. If the proxy is being hosted on the same system, enter “./client” 127.0.0.1 8000

Format: ./client &lt;IP address of proxy server> &lt;Port between client and proxy server>


7. Now enter the request in to the terminal running “./client”:

Type 1 example:

Enter type(1/2) or enter 0 to quit: 1

Enter Domain/IP : google.com

Type 2 example:

Enter type(1/2) or enter 0 to quit: 2

Enter Domain/IP : 172.217.12.238

After each query of client and proxy server the socket connection is gracefully closed from both sides releasing the socket resource.







## Networks Simulation using ns3


**Network Configuration:**
![image](https://user-images.githubusercontent.com/45571579/144579026-5764690c-2a77-46e2-9812-0e5ab29a662d.png)

- The Network consists of two routers R1 and R2 connected with a link (10Mbps,100ms)
- The hosts of the network are connected to the routers with (100Mbps,10ms) links. Router 1 is connected to H1, H2, H3, and Router 2 is connected to H4, H5, and H6.
- The routers use drop-tail queues with equal queue size set according to bandwidth-delay product i.e
- The size of the packet is 1.5KB
- 6 connections, 4 TCP and 2 UDP are created, which are randomly distributed between the 6 hosts of the network.

**TCP New Reno Flows**

1)Host 1 to Host 2

2)Host 3 to Host 4

3)Host 2 to Host 6

4)Host 1 to Host 6

**CBR over UP flows:**

1)Host 5 to Host 6

2)Host 4 to Host 3

**PART 1**

In the beginning, all connections operate on a data rate of 20Mbps each. We increase the data rate of Flow number 6, which is a UDP connection, from 20Mbps to 100Mbps. The data rate is increased in a linear fashion with 10Mbps jumps.

The buffer size is kept 15KB(10 \* Packet size) for the whole experiment.

![](https://lh5.googleusercontent.com/4twMYTV3xlsaIPkhoWB7b3nllZOduSXy8KJmroLp7ZUBGtW0pMvBemr0dxwJyB3n7h0ckoRHNx0zVh3ssw0wgjyouwSOlaZxygIbrirbfRZv2HpqWz-kaR87oU6_IkeW920ZIWH2)

  
  
  


**Throughput(UDP) vs increasing UDP flow rate**

Observation:

The graph above illustrates the effect of increasing the UDP rate of Flow Number 6 on the throughput of other UDP connections. When the UDP flow-rate of Flow number 6 is increased linearly with time, the rate of increase of UDP throughput of the other two connections decreases as the shared link gets increasingly congested with the 6th UDP connection as its UDP rate is increasing linearly with time.

  
  
  
  
  
  
  
  


![](https://lh4.googleusercontent.com/04pMbpLfhDfQclOT5Y80aNYujDtj2ix7sggvu5HqfNSVD7lo30JePNOTytY7Osy9VOli2-0aouSi5zKVmmG13DKgwyCWj_sWaNxy-tNL4um4Q3XpyZtaqzeEi95bEU7GWPjujaDs)

**Throughput(TCP) vs increasing UDP flow rate**

**Observation:**

As the UDP flow rate of Flow number 6 on the throughput of the TCP connections.. As the UDP flow rate increases linearly with time,**the rate of increase of the TCP throughput will decrease**, until it starts to approximately approach a constant value(Not reached in this case till 100Mbps). The reason for this happening is that the shared link gets more and more populated with the packets being sent by the UDP connection with the increasing flow rate.

  
  
  


![](https://lh4.googleusercontent.com/Kq1EejDhe3PPlX037z0M7LCUhtle66ridl3vHKimwv3G-izjClid4bVV-UjKzN8UUKry2gsvxk-a3-ByRy_O8dKYrVNfKCa2EPx41A-5U_hhAsEjOsSKGmLQHnHjLvzRneyHV8HP)

**Fairness Vs****increasing UDP flow rate**

Observation:

The above graph illustrates the effect of increasing the flow rate of the UDP connection(Flow Number ) on the fair share of bandwidth. Fairness increase with the increase in UDP flow rate

  
  
  
  
  
  
  
  
  
  
  
  
  
  


**PART 2**

![](https://lh3.googleusercontent.com/pAgYFU6owMgj93HSd9OAOFuSLlX1D2easUqkvn3y-LLvSRQK6yLUFrCUskXmPIWx_8PPre3bKSM_KcUy42vnH0UaLky7AKz4hWVlc0TjcEESPGyVcCdvEQtj1WVgHW9Mm7Pp1aK8)

**TCP throughput vs increasing Buffer Size**

Observation:

The above graph illustrates the effect of increasing buffer size on the throughput of TCP connections. The graph makes it clear that the TCP throughput would increase with the increasing buffer size until it saturates and reaches a constant value(~3.5Mbps).

We can observe that the throughput is less when the buffer size is less, because too many packets would be competing for the queue in the buffer of the router present at the bottleneck link. When this packet congestion happens, several packets undergo delay and may even be dropped out of the queue due to overflow. This leads to throughput degradation and packet loss. This happens when the buffer size is too small. As it increases, TCP efficiency also increases

![](https://lh3.googleusercontent.com/i20hXdVEZv4thUXSq3QrIazxK7n8Zop4Zwc5EWbGPPjsgffn3jAJq1CQYl8kwrD9r5of7by1AJwDZPQLVQKhWIvB5mJoHfEX94t_IYlMyF77jPPKqut5Wlpx6eDaABL_GNTvW2E2)

**UDP throughput vs increasing Buffer Size**

**Observation:**

The above graph illustrates the effect of increasing buffer size on the throughput of the UDP connections. As can be observed from the graph, UDP throughput erratically decreases as the buffer size is increased, and then it reaches a constant value when the buffer size reaches 100 packets. Beyond this point, increasing the buffer size has no effect on the UDP throughput.

![](https://lh5.googleusercontent.com/rGMtw9anSUbbc6LsKgd5p-yMOpOA7v9RMO6_RWGMrqoWRjfitofRWWm3XXo5NwGUSm6PRExY-qtWR-pU3c1LlTP5vsX1xNLgeaYt9GAKf3rjy47ku4_WYUIOQVHr9rQkEJMd-P6E)

**Fairness vs increasing Buffer Size**

Observation:

The above graph illustrates the effect of increasing buffer size on the Fairness index, it increases with increasing buffer size, which indicates that bandwidth is fairly shared amongst all 6 connections. When the fairness index is 1, it indicates that all connections share the bandwidth equally. The value of the index increases up to a certain value, and then it saturates. After this saturation value, increasing buffer size doesn’t have any effect on the fairness index because all the links cannot exceed the link bandwidth and therefore fairness reaches a constant value(~0.35)

  
  
  
  
  
  


.

  
