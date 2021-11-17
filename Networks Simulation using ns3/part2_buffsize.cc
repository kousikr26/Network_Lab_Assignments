//Include all the required ns3 libraries
#include <bits/stdc++.h>
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

Gnuplot2dDataset datasets[3];
vector<string> dataset_titles = {"Fairness", "TCP Flow", "UDP flow"};
NS_LOG_COMPONENT_DEFINE("CS342_Assignment_4");
int portNo;
int startTime = 1;
int endTime = 10;
//Packet Size is 1.5KB
int pktSize = 1500;
int bufferSize;
int packetsToSend = 1000000;
//Include the header file that contains all the functions
#include "app.h"

int main(int argc, char *argv[])
{
    //Smallest measurable time interval = 1ns
    Time::SetResolution(Time::NS);

    //The default configuration is set as TCP new Reno
    Config::SetDefault("ns3::TcpL4Protocol::SocketType",
                       TypeIdValue(TcpNewReno::GetTypeId()));

   
    /*Instantiating the dataset, setting the title, 
    and making the points be plotted by connecting lines*/
    for(int i=0;i<3;i++){
    for (int i = 0; i < 3; i++)
    {
        datasets[i].SetTitle(dataset_titles[i]);
        datasets[i].SetStyle(Gnuplot2dDataset::LINES_POINTS);
    }

    for (bufferSize = 10 * pktSize; bufferSize <= 800 * pktSize;)
    {
        portNo = 8000;
        NS_LOG_INFO("Create nodes");

        //Create 8 nodes, 2 for the routers R1 and R2, and 6 for the hosts H1-H6.
        NodeContainer nodes;
        nodes.Create(8);

        // NodeContainer function creates node containers for each link
        NodeContainer e03 = NodeContainer(nodes.Get(0), nodes.Get(3)); // Link between h1 -- r1
        NodeContainer e13 = NodeContainer(nodes.Get(1), nodes.Get(3)); // Link between h2 -- r1
        NodeContainer e23 = NodeContainer(nodes.Get(2), nodes.Get(3)); // Link between h3 -- r1
        NodeContainer e34 = NodeContainer(nodes.Get(3), nodes.Get(4)); // Link between r1 -- r2
        NodeContainer e45 = NodeContainer(nodes.Get(4), nodes.Get(5)); // Link between r2 -- h4
        NodeContainer e46 = NodeContainer(nodes.Get(4), nodes.Get(6)); // Link between r2 -- h5
        NodeContainer e47 = NodeContainer(nodes.Get(4), nodes.Get(7)); // Link between r2 -- h6

        // Install the internet stack(protocols) on the nodes
        InternetStackHelper internet;
        internet.Install(nodes);

        NS_LOG_INFO("Creating connections");

        // Create point to point channels between the nodes
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

        // Router to router links
         //Setting the queueing configuration in the Router Router Link to Drop Tail Queue
        p2p.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue(std::to_string(100000 * 10 / pktSize) + 'p'));
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

         
        Ptr<MyApp> udpChange = establishUDP(nodes, i23, 5, 2, bufferSize);

        FlowMonitorHelper flowmn;
        Ptr<FlowMonitor> fmonitor_ptr = flowmn.InstallAll();
        
        for (int i = 2; i <= 10; i++)
        {
            Simulator::Schedule(Seconds((float) i), &IncRate, udpChange, DataRate(to_string(i + 1) + "0Mbps"));
        }

        NS_LOG_INFO("Simulation running");
        Simulator::Stop(Seconds(endTime));
        Simulator::Run();

        fmonitor_ptr->CheckForLostPackets();
        //This is used to calculate the throughput at each second. 
        //Total throughput, throuput from TCP connections and throughput from UDP connections are calculated.

        Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmn.GetClassifier());
        std::map<FlowId, FlowMonitor::FlowStats> stats = fmonitor_ptr->GetFlowStats();
        
        double sumFlow = 0, sumFlowSqr = 0, sumFlowTCP = 0, sumFlowUDP = 0;
        for (auto &i : stats)
        {
            Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i.first);
            // Calculating the throughput of the flow 
            double TPut = i.second.rxBytes * 8.0 / (i.second.timeLastRxPacket.GetSeconds() - i.second.timeFirstTxPacket.GetSeconds()) / 1000000;
            sumFlow += TPut;
            sumFlowSqr += TPut * TPut;
            //UDP connection
            if (t.destinationPort == 8005 || t.destinationPort == 8006)
            {
                sumFlowUDP += TPut;
            }
            //TCP connection
            else
            {
                sumFlowTCP += TPut;
            }
        }
        // Calculating the fairness index from the throughput
        double FairnessIndex = (sumFlow * sumFlow) / (6 * sumFlowSqr);
        // Adding to the dataset
        datasets[0].Add(bufferSize / pktSize, FairnessIndex);
        datasets[1].Add(bufferSize / pktSize, sumFlowTCP);
        datasets[2].Add(bufferSize / pktSize, sumFlowUDP);
        cout << " FairnessIndex:	" << FairnessIndex << endl;
        Simulator::Destroy();
        if (bufferSize < 100 * pktSize)
            bufferSize += 10 * pktSize;
        else
            bufferSize += 100 * pktSize;
    }
    //Plotting the graph 
    plotGraph("fairnessVsBuffer", "Fairness vs buffer size", "Buffer Size (packets)", "Fairness", "set xrange [0:800]", datasets[0]);
    plotGraph("tcpVsBuffer", "Throughput(TCP) vs buffer size", "Buffer Size (packets)", "Throughput (mbps)", "set xrange [0:800]", datasets[1]);
    plotGraph("udpVsBuffer", "Throughput(UDP) vs buffer size", "Buffer Size (packets)", "Throughput (mbps)", "set xrange [0:800]", datasets[2]);


    NS_LOG_INFO("Simulation complete");
}