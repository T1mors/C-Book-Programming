set terminal postscript enhanced "Times-roman" 22 portrait
set output "PW_integrand.eps"

set multiplot

set size square 1
set nokey
set label  "{/Times-Italic N}=128^2,{/Times-Italic B}_{max}=3"\
           at -47500, 9060
set xtics 1000
set xlabel "{/Times-Italic W}"
set format y "10^{%4.0f}"
set ylabel "{/Times-Italic P(W)}e^{/Times-Italic -W/T}"\
    offset 1,0
plot [-48600:-46000] [8700:9100] "integrand.dat" u 1:($2/log(10.0))

set size square 0.53
set origin 0.22, 0.175
set xlabel "{/Times-Italic  B_{/Times-Roman max}}" offset -0.3,0.6
set xtics 1
set ylabel "{/Symbol D}{/Times-Italic F/N-B}_{max}" offset 1.5,0
set ytics 0.1
set format y "%g"
f(x)=a*x
a=-128*128
plot [0:3.5][0:0.2] "B.dat" u 1:(($2-f($1))/(128*128)) ps 2 lw 2

