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

  
