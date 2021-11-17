set terminal png
set output "fairnessVsBuffer.png"
set xlabel "Buffer Size (packets)"
set ylabel "Fairness"

set xrange [0:800]
plot "-"  title "Fairness" with linespoints
10 0.294507
20 0.305771
30 0.315457
40 0.324784
50 0.33164
60 0.336676
70 0.341381
80 0.345121
90 0.347754
100 0.347642
200 0.347256
300 0.347256
400 0.347256
500 0.347256
600 0.347256
700 0.347256
800 0.347256
e
