reset
set xlabel "x"
set ylabel "y"
set xrange[0:0.3]
set yrange[0:0.3]

set term x11 0
set term png size 800,700
set output 'Data_a_both.png'
plot    "Data_a_12351.dat" using 1:2 title "a = 12351" pt 7 lc 1, \
        "Data_a_12349.dat" using 1:2 title "a = 12349" pt 7 lc 2

set xrange[0:0.5]
set yrange[0:0.5]

set term x11 1
set term png size 800,700
set output 'Data_a_12351.png'
plot    "Data_a_12351.dat" using 1:2 title "a = 12351" pt 7 ps 0.7 lc 1

set term x11 2
set term png size 800,700
set output 'Data_a_12349.png'
plot    "Data_a_12349.dat" using 1:2 title "a = 12349" pt 7 ps 0.7 lc 2
