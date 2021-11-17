/* Network topology

        (h1)  (n0)                                  (n5)         (h4)
                \ 100 Mbps, 10ms                   /
                 \          10Mbps, 100ms         /
        (h2)   (n1)---(n3)-----------------------(n4)----(n6)    (h5)
                 /                                \
                / 100 Mbps, 10ms                   \
        (h3)  (n2)                                  (n7)         (h6)


    Connections 
    
    h1-h2/n0-n1 TCP
    h3-h4/n2-n5 TCP
    h2-h6/n1-n7 TCP
    h1-h6/n0-n7 TCP
    h5-h6/n6-n7 UDP
    h4-h3/n5-n2 UDP
*/

/* A custom-made  application for binding the sockets when the application is initiated.
The application increases the data rate at run time.
This is taken from fifth.cc from ns3 examples
*/


class MyApp : public Application{
public:
    MyApp();
    virtual ~MyApp();

    void Setup(Ptr<Socket> socket, Address addr, int pktSize, int nPkts, DataRate dataRate);
    void ChangeRate(DataRate newrate);

private:
    virtual void StartApplication(void);
    virtual void StopApplication(void);

    void ScheduleTx(void);
    void SendPacket(void);

    Ptr<Socket> m_socket;
    Address m_peer;
    int m_pktSize, m_nPkts,m_packetsSent;
    bool m_running;
    DataRate m_dataRate;
    EventId m_sendEvent;
    
};

MyApp::MyApp()
    : m_socket(0), m_peer(), m_pktSize(0), m_nPkts(0), m_packetsSent(0), m_running(false), m_dataRate(0), m_sendEvent() {}

MyApp::~MyApp()
{
    m_socket = 0;
}



void MyApp::Setup(Ptr<Socket> socket, Address addr, int pktSize, int nPkts, DataRate dataRate){
    m_socket = socket;
    m_peer = addr;
    m_pktSize = pktSize;
    m_nPkts = nPkts;
    m_dataRate = dataRate;
}

void MyApp::StartApplication(){
    m_running = true;
    m_packetsSent = 0;
    m_socket->Bind();
    m_socket->Connect(m_peer);
    SendPacket();
}

void MyApp::StopApplication(){
    m_running = false;
    if (m_sendEvent.IsRunning())
        Simulator::Cancel(m_sendEvent);
    
    if (m_socket)
        m_socket->Close();
    
}

void MyApp::SendPacket(){
    Ptr<Packet> packet = Create<Packet>(m_pktSize);
    m_socket->Send(packet);
    m_packetsSent++;
    if (m_packetsSent < m_nPkts)
        ScheduleTx();
}

void MyApp::ScheduleTx()
{
    if (m_running)
    {
        Time tNext(Seconds(m_pktSize * 8 / static_cast<double>(m_dataRate.GetBitRate())));
        m_sendEvent = Simulator::Schedule(tNext, &MyApp::SendPacket, this);
    }
}

//This function changes the data rate of an application
void MyApp::ChangeRate(DataRate newrate)
{
    m_dataRate = newrate;
    
}

//This function increases the data rate of an application
void IncRate(Ptr<MyApp> app, DataRate rate)
{
    app->ChangeRate(rate);

}

// This function calculates throughput every second
void throughputFlow(FlowMonitorHelper *fmhelper, Ptr<FlowMonitor> flowMon)
{
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(fmhelper->GetClassifier());
    map<FlowId, FlowMonitor::FlowStats> stats = flowMon->GetFlowStats();
    double sumFlow = 0, sumFlowSqr = 0, sumFlowTCP = 0,sumFlowUDP=0;
    for (auto& i : stats)
    {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i.first);
        // Throughput calculation
        double TPut = i.second.rxBytes * 8.0 / (i.second.timeLastRxPacket.GetSeconds() - i.second.timeFirstTxPacket.GetSeconds()) / 1000000;
        sumFlow += TPut;
        sumFlowSqr += TPut * TPut;
        if (t.destinationPort == 8005 || t.destinationPort == 8006){
            sumFlowUDP+=TPut;
        }
        else{
            sumFlowTCP+=TPut;
        }
    }
    // Fairness calculation
    double FairnessIndex = (sumFlow * sumFlow) / (6 * sumFlowSqr);
    datasets[0].Add(10*Simulator::Now().GetSeconds(), FairnessIndex);
    if (sumFlowTCP != 0)
        datasets[1].Add(10*Simulator::Now().GetSeconds(), sumFlowTCP);
    if (sumFlowUDP != 0)
        datasets[2].Add(10*Simulator::Now().GetSeconds(), sumFlowUDP);
    cout << " FairnessIndex: " << FairnessIndex << endl;
    Simulator::Schedule(Seconds(1), &throughputFlow, fmhelper, flowMon);
}

//This function establishes a TCP connection between trace source and trace sink
Ptr<MyApp> establishTCP(NodeContainer &nodes, Ipv4InterfaceContainer &intface, int source, int sink, int bsize)
{
    ++portNo;
    Address sinkAddress(InetSocketAddress(intface.GetAddress(1), portNo));
    PacketSinkHelper pckSink("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), portNo));
    //The application at the Sink uses Packet Sink helper to consume all the packets coming from Port 1
    ApplicationContainer sinkApps = pckSink.Install(nodes.Get(sink));
    sinkApps.Start(Seconds(startTime));
    sinkApps.Stop(Seconds(endTime));

    //Create a TCP socket for applcation on the sender's side
    Ptr<Socket> tcpSocket = Socket::CreateSocket(nodes.Get(source), TcpSocketFactory::GetTypeId());
    tcpSocket->SetAttribute("SndBufSize", ns3::UintegerValue(bsize));
    tcpSocket->SetAttribute("RcvBufSize", ns3::UintegerValue(bsize));

    //Create the application on the sender's side
    Ptr<MyApp> tcp_Agent = CreateObject<MyApp>();
    tcp_Agent->Setup(tcpSocket, sinkAddress, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(source)->AddApplication(tcp_Agent);
    tcp_Agent->SetStartTime(Seconds(startTime));
    tcp_Agent->SetStopTime(Seconds(endTime));
    return tcp_Agent;
}


//This function establishes a UDP connection between trace source and trace sink
Ptr<MyApp> establishUDP(NodeContainer &nodes, Ipv4InterfaceContainer &intface, int source, int sink, int bsize)
{

    //++portNo assigns a new port to every new connection
    portNo = portNo+1;

    //This creates a sink
    Address sinkAddress(InetSocketAddress(intface.GetAddress(0), portNo));
    PacketSinkHelper pckSink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), portNo));


    //This creates a sink side application that will consume all the packets coming in from the port created above
    ApplicationContainer sinkApps = pckSink.Install(nodes.Get(sink));
    sinkApps.Start(Seconds(startTime));
    sinkApps.Stop(Seconds(endTime));


    //This creates a socket
    Ptr<Socket> ns3UdpSocket = Socket::CreateSocket(nodes.Get(source), UdpSocketFactory::GetTypeId());
    ns3UdpSocket->SetAttribute("RcvBufSize", ns3::UintegerValue(bsize));


    //Create an application for the sender's side.
    Ptr<MyApp> udp_Agent = CreateObject<MyApp>();
    udp_Agent->Setup(ns3UdpSocket, sinkAddress, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(source)->AddApplication(udp_Agent);
    udp_Agent->SetStartTime(Seconds(startTime));
    udp_Agent->SetStopTime(Seconds(endTime));

    return udp_Agent;
}

void plotGraph(string fileName, string title, string legendx, string legendy, string extra, Gnuplot2dDataset &dataset)
{
    string fileNameWithNoExtension = fileName;
    string graphicsFileName = fileNameWithNoExtension + ".png";
    string plotFileName = fileNameWithNoExtension + ".plt";
    string plotTitle = title;
    Gnuplot plot(graphicsFileName);
    plot.SetLegend(legendx, legendy);
    plot.AppendExtra(extra);
    plot.AddDataset(dataset);
    ofstream plotFile(plotFileName.c_str());
    plot.GenerateOutput(plotFile);
    plotFile.close();
}