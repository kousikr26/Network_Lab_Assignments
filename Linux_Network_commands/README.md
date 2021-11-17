**CS342 Assignment 1 Kousik Rajesh**

**180101094**

**Q.1**

1. **-c &lt;count> :**_ping -c &lt;count> &lt;IP>_
2. **-i** &lt;**interval> :**_ping -i &lt;interval> &lt;IP>_
3. **ping -l &lt;preload> &lt;host>**

Normal user is limited to**max 3**ECHO_REQUEST(_preload_) packets

4. **ping -s &lt;size> &lt;host>**

_ICMP header is of 8 bytes_. Total packet size = payload size + header size

Hence total size**32+8 = 40 bytes**



* * *



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

  
![](https://lh5.googleusercontent.com/iL-8xVl7CPUqFBWZU6g3qb3CBy3P11AaZfP5zb_BxQ5XB_D2y1Efkll3CKqYBKwwWzholItASaBry3pvYJylV-1Bv2FsKxDrVbBI2V6Soo-li2CKILgaSK04J4QtrowAiZt1dA6Q)

There is**no strong correlation of RTT with geographical distance** as shown in the plot. This is due to the use of CDN’s as proxy servers

**b) None of the hosts suffered packet loss** indicating that the network was in perfect working condition.

If there were any packet loss it could be due to a congestion in the network, server down, faulty hardware or software bugs.

**c) Using host**[udp.jp/](http://udp.jp/)

**d) Time of day:**There is some correlation between time

of day and Avg RTT. At 23:00 Hours(11:00 PM) almost all the hosts![](https://lh4.googleusercontent.com/BzONRJDCCmBgGMitlWSAxLIElkmkrwEZQGP05iCFEZK2T8Fov1yRAIpbj9jtIEPEF7A58fkC_-oFPjV_6szJ1et0tDlkyTF4oYSAtatxbGtVhGt8rDqG9Z3-aIVop0xJ0YK9xy2I)

had 10-20% higher RTT than other times which could be indication of

high network congestion

**Packet Size:**There is no direct correlation observed between packet size and RTT possibly because the propagation time dominates the data transfer time. However when size exceeds MTU the packet is broken down into 2 frames.



* * *



Q.3**Chosen IP address : 172.16.114.188**

**a) b)**

|                                 | **Packet loss(%)** | **Minimum (ms)** | **Maximum (ms)** | **Mean (ms)** | **Median (ms)** | **Standard Deviation(ms)** |
| ------------------------------- | ------------------ | ---------------- | ---------------- | ------------- | --------------- | -------------------------- |
| **ping -n 172.16.114.188**      | **0.8%**           | **114**          | **196**          | **122.85**    | **122.0**       | **8.06**                   |
| **ping -p ff00 172.16.114.188** | **1.9%**           | **92.3**         | **400**          | **101.7**     | **99.85**       | **14.43**                  |

  


![](https://lh3.googleusercontent.com/BnK9Pxrjz2mLRfM_As7soVqnypJb7vS-iIlJ_mhIYgUr9j-zdVdhq7sYejzk90B4TDZIR9YQu3fO_IVnr9XBdPaKku-56nBeQMppUBcvx_bCLC4G-YFfvbsTrJBY_2MNR1WQO5Lv) ![](https://lh4.googleusercontent.com/yPakc7IvjWitkPDs5IFNSzHobYlEhLVlKHA759hGd488pr62DtAMSUt5T7OSrfaD3FG61lsBDdrTMf_B3iOQv_hzz3BGlhdewk7x90N9l6seU720Vajh-xj-nszGUhog5xBHGsCC)

**************************Fitting them to a normal curve**

  
![](https://lh3.googleusercontent.com/ERl4ThJBTmGtD40Pe93hZPz9TQM-Q6GZw-tHCfzLD7ZQolQOiOEwEUcbfShmltsGJ5yw6vHQu8czv6B7YNKcO36uh3Cv25_8d_6t55ESlhcV3rrj_2lgtgjGvxZ-OPoWU1lCJOy0)

- Both commands have a normal distribution of latency
- **Ping -n has a higher mean and lower variance** than the other


- The -p ff00 packet contains 1111111100000000 since only one transition is present in the padding (from high to low) clocks are more likely to go out of synchronization and we observe a higher packet loss.

  
  
  
  
  


**Q.4**

1. The**ifconfig** config outputs all the network devices present and some statistics on them

**Eno1 :**The physical interface representing Ethernet network card

**Lo :**The loopback interface which acts as a virtual network device used to run network services such as web servers locally for debugging and testing.

  
  
  


**Statistics****  
**

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

  
**  
**

**Destination** : Destination network/host

**Gateway :**Gateway address

**Genmask :**The netmask of the destination network

**Flags :**

******U :**Route is up

**G** : Route is to a gateway

**H** : Target is a host  


d)

- **Add :**route add &lt;destination> gw &lt;gateway> (Adds a route)
- **Del :**route del &lt;destination> (Deletes a route)
- **host**: used to denote the target is a host.
- **mss :**Set the Maximum Transmission Unit(MTU)

![](https://lh5.googleusercontent.com/HMnz2jx-XZO10pHEmiwV4MurMp9kepOpdS-E94vKG4ubBSY266jUclcdR9PBceoLz0h0K36gFHOCffNFlx2322pJS8mSJW9G_G0EF63BcLrVYDBkn__86JJM_OuQlZtW6xHTlffE)

Q.5

a) The**netstat** command displays various statistics on network connections(TCP/UDP/UNIX) and their status. It can also be used to display routing tables, interface statistics, protocol statistics, internal connections(UNIX type), masquerade connections, and multicast memberships

b)** netstat -at | grep ESTABLISHED****  
****![](https://lh5.googleusercontent.com/7VN-nUzq6bc0IIQcpLak8Vp-upaEXIYcg8w3N9P-TqsCXawGERIn3scftoewwcZwkd17p61de7J7Rdvnz30rtQNP2WPukbSV0v2Pq3X84z7-71f1WvhAcuhA_q8oD3v7U-fnBKXl)**

c)** netstat -r **shows the IP routing table which acts as a map and is used in computing the next hop for a packet.

  
**  
**

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

1. **Command : sudo nmap -sn172.16.114._128_/25**

The IP and subnet mask can be found using**_ip add_**command

**_Subnet mask :_**_ 255.255.255._**_128_**

2. **sudo nmap -sA -T4 &lt;ip address>![](https://lh4.googleusercontent.com/4WoxA-6IIEALiU9v-bVZLuBQaFCxAg6nng8NEqsnP1nwWYwcMEI8-pZiFQdJzEtcj3xW1DyKCkFnfHaGhAOQ2KmOGKlzhS0FGIMp4PxdT7pZgnl7rd0blOQpCpiXuQIXUBWXCA5n)**
3. **  
   **

| **Time** | **Number of PC’s up** |
| -------- | --------------------- |
| 01:50    | 85                    |
| 03:20    | 85                    |
| 15:50    | 85                    |
| 17:50    | 78                    |
| 18:20    | 83                    |
| 22:40    | 86                    |

  
