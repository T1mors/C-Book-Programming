# load "gnuplotTestData.plt" , "" sehr wichtig!

set title "Coulomb potential with m=1, Ze^2=1, hbar=1"
set xlabel "basis size D"
set ylabel "relative error of lowest energy"
set xrange [10:40]
set xtics 10,2,40
exact = -0.5 # exact answer
f(x) = m*x+b # for a linear fit
# $1 refers to column 1 in test1.dat, $2 to column 2, and so on
fit f(x) "TestData.dat" using (log10($1)):(log10(abs(($2-exact)/exact))) via m,b
slope_title = sprintf("slope = %-+4.1f",m) # check "man sprintf" for details
set logscale
plot "TestData.dat" using (($1)):((abs(($2-exact)/exact))) title ’b=0.6’, \(10**b)*x**a title slope_title