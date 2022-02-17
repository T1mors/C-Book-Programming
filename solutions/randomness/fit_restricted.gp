# fitting without/with restricting the range of parameters
m(x)=m0+b*x+c*x*x
m0=1
b=1
c=1
fit m(x) "parabola.dat" u 1:2:3 via m0,b,c
pause -1 "Hit enter to perform restricted fit"
m2(x)=m2+exp(b2)*x+c2*x*x
m2=1
b2=-10
c2=1
fit m2(x) "parabola.dat" u 1:2:3 via m2,b2,c2
print "susceptibility:", exp(b2)
plot [0:1] 1.2+0.1*x+3*x*x, "parabola.dat" w e, m(x), m2(x)
pause -1 "Hit enter to finish"
