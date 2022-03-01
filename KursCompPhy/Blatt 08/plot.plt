reset
set xlabel "p"
set ylabel "S/N"
set key top left
set title "Fraction of biggest Cluster S to N sites over percentage p occupied sites"
L_num = "10 20 50 100 200 300 500"
plot    for [L in L_num] "perc".L.".dat" using 1:2 title "L = ".L, \
        for [L in L_num] "perc".L.".dat" using 1:2 with lines ls 0 title ""

# Same for png save
set term x11 0
set term png size 1000,700
set output 'perc_L.png'
plot    for [L in L_num] "perc".L.".dat" using 1:2 title "L = ".L, \
        for [L in L_num] "perc".L.".dat" using 1:2 with lines ls 0 title ""