set terminal png
set output "fairnessVsFlow.png"
set xlabel "UDP flow rate(Mbps)"
set ylabel "Fairness"

set xrange [0:100]
plot "-"  title "Fairness" with linespoints
0 -nan
10 0.292369
20 0.300591
30 0.303319
40 0.304335
50 0.306412
60 0.313155
70 0.315362
80 0.319008
90 0.324702
100 0.329322
e
