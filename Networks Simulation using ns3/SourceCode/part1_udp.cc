#include <bits/stdc++.h>

// Include required ns3 modules
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/gnuplot.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/point-to-point-module.h"



using namespace ns3;
using namespace std;

//Packet Size is 1.5KB 
int pktSize = 1500;
int bufferSize = 50 * pktSize;

Gnuplot2dDataset datasets[3];
vector<string> dataset_titles={"Fairness","TCP Flow","UDP flow"};
NS_LOG_COMPONENT_DEFINE("CS342_Assignment_4");

int portNo=8000;
int startTime = 0;
int endTime = 10;
int packetsToSend = 1000000;
//Include the header file that contains all the functions
#include "app.h"

int main(int argc, char *argv[])
{
    //Smallest measurable time interval = 1ns
    Time::SetResolution(Time::NS);

    //The default configuration is set as TCP new Reno
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpNewReno::GetTypeId()));


    /*Instantiating the dataset, setting the title, 
    and making the points be plotted by connecting lines*/
    for(int i=0;i<3;i++){
        datasets[i].SetTitle(dataset_titles[i]);
        datasets[i].SetStyle(Gnuplot2dDataset::LINES_POINTS);
    }

    //Create 8 nodes, 2 for the routers R1 and R2, and 6 for the hosts H1-H6.
    NodeContainer nodes;
    nodes.Create(8);

    //NodeContainer function creates node containers for each link
    NodeContainer e03 = NodeContainer(nodes.Get(0), nodes.Get(3)); // Link between h1 -- r1
    NodeContainer e13 = NodeContainer(nodes.Get(1), nodes.Get(3)); // Link between h2 -- r1
    NodeContainer e23 = NodeContainer(nodes.Get(2), nodes.Get(3)); // Link between h3 -- r1
    NodeContainer e34 = NodeContainer(nodes.Get(3), nodes.Get(4)); // Link between r1 -- r2
    NodeContainer e45 = NodeContainer(nodes.Get(4), nodes.Get(5)); // Link between r2 -- h4
    NodeContainer e46 = NodeContainer(nodes.Get(4), nodes.Get(6)); // Link between r2 -- h5
    NodeContainer e47 = NodeContainer(nodes.Get(4), nodes.Get(7)); // Link between r2 -- h6

    //Install the internet stack(protocols) on the nodes
    InternetStackHelper internet;
    internet.Install(nodes);

    //Create point to point channels between the nodes
    PointToPointHelper p2p;

    //Host router links
    p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("10ms"));
    NetDeviceContainer d03 = p2p.Install(e03);
    NetDeviceContainer d13 = p2p.Install(e13);
    NetDeviceContainer d23 = p2p.Install(e23);
    NetDeviceContainer d45 = p2p.Install(e45);
    NetDeviceContainer d46 = p2p.Install(e46);
    NetDeviceContainer d47 = p2p.Install(e47);

    //Router to Router Links 
    //Setting the queueing configuration in the Router Router Link to Drop Tail Queue
    p2p.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue(to_string(100000 * 10 / pktSize) + 'p'));
    p2p.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("100ms"));
    NetDeviceContainer d34 = p2p.Install(e34);

    // The code below assigns IP addresses to each interface
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i03 = ipv4.Assign(d03);

    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer i13 = ipv4.Assign(d13);

    ipv4.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer i23 = ipv4.Assign(d23);

    ipv4.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i34 = ipv4.Assign(d34);

    ipv4.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i45 = ipv4.Assign(d45);

    ipv4.SetBase("10.1.6.0", "255.255.255.0");
    Ipv4InterfaceContainer i46 = ipv4.Assign(d46);

    ipv4.SetBase("10.1.7.0", "255.255.255.0");
    Ipv4InterfaceContainer i47 = ipv4.Assign(d47);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    /* TCP Reno connections*/
    
    //tcp : h1-h2
    establishTCP(nodes, i13, 0, 1, bufferSize);

    //tcp : h3-h4
    establishTCP(nodes, i45, 2, 5, bufferSize);

    //tcp : h2-h6
    establishTCP(nodes, i47, 1, 7, bufferSize);

    //tcp : h1-h6
    establishTCP(nodes, i47, 0, 7, bufferSize);
    
    //udp : h5-h6
    establishUDP(nodes, i47, 6, 7, bufferSize);

    //increasing the UDP data rate upto 100Mbps in discrete time steps for UDP between h3 and h4
    Ptr<MyApp> udp_to_change = establishUDP(nodes, i23, 5, 2, bufferSize);


    /* CBR traffic on UDP */
    FlowMonitorHelper flowmn;


    Ptr<FlowMonitor> fmonitor_ptr = flowmn.InstallAll();

    
    throughputFlow(&flowmn, fmonitor_ptr);
    for(int i=1;i<=10;i++){
        Simulator::Schedule(Seconds((float)i), &IncRate, udp_to_change, DataRate(to_string(i)+"0Mbps"));
    }
    
    
    NS_LOG_INFO("Running simulation");
    Simulator::Stop(Seconds(11.0));
    Simulator::Run();
    Simulator::Destroy();
    // Initialize Plots
    plotGraph("fairnessVsFlow", "Fairness vs Time", "UDP flow rate(Mbps)", "Fairness", "set xrange [0:100]",datasets[0]);
    plotGraph("tcpVsFlow", "Throughput(TCP) vs Time", "UDP flow rate(Mbps)", "Throughput (mbps)", "set xrange [0:100]", datasets[1]);
    plotGraph("udpVsFlow", "Throughput(UDP) vs Time", "UDP flow rate(Mbps)", "Throughput (mbps)", "set xrange [0:100]", datasets[2]);
    NS_LOG_INFO("simulation complete");
}

