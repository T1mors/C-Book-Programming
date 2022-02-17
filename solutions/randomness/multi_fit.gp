#/*******************************************************************/
#/*** Gnuplot script, which performs a multi branch fitting to    ***/
#/*** file "expo1.dat" and shows result                           ***/
#/***                                                             ***/
#/*** Solution of a problem from the book:                        ***/
#/*** A.K. Hartmann                                               ***/
#/*** A practical guide to computer simulation                    ***/
#/*** World Scientific, Singapore 2008                            ***/
#/***                                                             ***/
#/*** Chapter: Randomness and statistics                          ***/
#/*** Section: General estimators                                 ***/
#/*******************************************************************/
f0(x)=a0*exp(-x/mu)
f1(x)=a1*exp(-x/mu)
f2(x)=a2*exp(-x/mu)
# uncomment and use this if you want to compare single fits
#fit  f0(x) "expo1.dat" index 0  using 1:2:3 via a0,mu
#fit  f1(x) "expo1.dat" index 1  using 1:2:3 via a1,mu
#fit  f2(x) "expo1.dat" index 2  using 1:2:3 via a2,mu
delta(a,b) = (a==b) ? 1 : 0
f(x,s) = delta(s,0)*f0(x)+delta(s,1)*f1(x)+delta(s,2)*f2(x)
fit f(x,y) "expo1.dat" using 1:-2:2:3 via a0,a1,a2,mu
set xlabel "x"
set ylabel "P(x)"
set logscale y
set label sprintf("mu=%f (%f)", mu) at 8,0.5
plot "expo1.dat" u 1:2:3 w e, f(x,0) title sprintf("a0=%f", a0),\
     f(x,1) title sprintf("a1=%f", a1), f(x,2) title sprintf("a2=%f", a2)
pause -1 "Hit enter to finish"