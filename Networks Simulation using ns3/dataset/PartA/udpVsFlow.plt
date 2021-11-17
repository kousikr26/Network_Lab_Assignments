set terminal png
set output "udpVsFlow.png"
set xlabel "UDP flow rate(Mbps)"
set ylabel "Throughput (mbps)"

set xrange [0:100]
plot "-"  title "UDP flow" with linespoints
10 28.5722
20 29.3751
30 29.5644
40 29.6104
50 29.3565
60 29.2738
70 29.1614
80 28.9868
90 28.8244
100 28.7254
e
