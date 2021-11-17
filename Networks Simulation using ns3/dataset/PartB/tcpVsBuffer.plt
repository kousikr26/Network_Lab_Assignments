set terminal png
set output "tcpVsBuffer.png"
set xlabel "Buffer Size (packets)"
set ylabel "Throughput (mbps)"

set xrange [0:800]
plot "-"  title "TCP Flow" with linespoints
10 0.715401
20 1.27377
30 1.78362
40 2.26806
50 2.60094
60 2.85939
70 3.0947
80 3.28997
90 3.41873
100 3.41549
200 3.39877
300 3.39877
400 3.39877
500 3.39877
600 3.39877
700 3.39877
800 3.39877
e
