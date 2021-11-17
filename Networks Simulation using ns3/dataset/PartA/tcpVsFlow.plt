set terminal png
set output "tcpVsFlow.png"
set xlabel "UDP flow rate(Mbps)"
set ylabel "Throughput (mbps)"

set xrange [0:100]
plot "-"  title "TCP Flow" with linespoints
10 0.375037
20 0.472808
30 0.546218
40 0.58831
50 0.813312
60 1.19225
70 1.35727
80 1.6225
90 1.98379
100 2.26122
e
