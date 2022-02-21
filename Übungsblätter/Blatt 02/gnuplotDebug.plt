set title "Coulomb potential with m=1, Ze^2=1, hbar=1"
set xlabel "basis size D"
set ylabel "relative error of lowest energy"
set xrange [10:40]
set xtics 10,2,40
set grid
exact = -0.5 # exact answer
f(x) = m*x+b # for a linear fit
fit f(x) "TestData.dat" u 1:2 via m, b
plot "TestData.dat" u 1:2 title "Datapoints", \
f(x) title "Fit"