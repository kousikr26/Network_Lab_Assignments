set terminal png
set output "udpVsBuffer.png"
set xlabel "Buffer Size (packets)"
set ylabel "Throughput (mbps)"

set xrange [0:800]
plot "-"  title "UDP flow" with linespoints
10 28.3641
20 28.3701
30 28.3118
40 28.264
50 28.2716
60 28.2493
70 28.2399
80 28.2159
90 28.216
100 28.212
200 28.208
300 28.208
400 28.208
500 28.208
600 28.208
700 28.208
800 28.208
e
