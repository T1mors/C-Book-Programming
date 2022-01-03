#########################################################
# symbols (for "terminal postscript")
#########################################################
#                3              star
#                4              empty square
#                5              filled square
#                6              empty circle
#                7              filled circle
#                8              empty triangle up
#                9              filled triangle up
#               10              empty triangle down
#               11              filled triangle down
#               12              empty diamond
#               13              filled diamond
#               14              empty pentagon
#               15              filled pentagon
#########################################################
# line styles
#########################################################
#	       -1		same as border lines
#		0		separated dashed
#		1		solid
#               2               dashed 
#		3		dotted 
#		6		dashed-dotted 
#########################################################
set size 1.0, 0.6
set terminal postscript portrait enhanced font 'Helvetica,16'
set output 'test_mult-branch.eps'

#########################################################
# set details about key
#########################################################
set key at graph 0.63, graph 0.95 width 0  box
set key spacing 1.25
set key Left reverse 	
set key samplen 1.5		# set length of error bars in key
#set key bottom left box

#########################################################
#set format x "10^{%L}"
#set format y "%3.2f"		# set scientific notation for y axis
#set format x "%3.2f"		# set one digit after period for x axis
#set log y
#set log
set yrange [-2:35]	# set range of y axis
#set xrange [0.55:1.1]		# set range of x axis
#########################################################
# set axes labels
#########################################################
set xlabel 'x' # set label x axis
set ylabel 'y' offset 2.0 # set label y axis
set label 'y = a + b x' at graph 0.7, 0.15
#########################################################
# fits
#########################################################
set fit errorvariables
#f(x,t) = exp(-(x/value(sprintf("xi%d",t)))**b)
f(x,t) = a + value(sprintf("b%d", t)) * x
fit f(x,y) "test_data" u 1:-2:2:3 via a, b0, b1, b2
#########################################################
# now compute some parameters of the fit and print the results
#########################################################
ndf = FIT_NDF
chisq = FIT_STDFIT**2 * ndf
Q = 1 - igamma(0.5 * ndf, 0.5 * chisq)  # quality of fit
f0(x) = a + b0*x
f1(x) = a + b1*x
f2(x) = a + b2*x
set label sprintf("a = %5.2f +/- %5.2f",a, a_err/FIT_STDFIT) at graph 0.03, 0.9
set label sprintf("b0 = %5.2f +/- %5.2f",b0, b0_err/FIT_STDFIT) at graph 0.03, 0.83
set label sprintf("b1 = %5.2f +/- %5.2f",b1, b1_err/FIT_STDFIT) at graph 0.03, 0.76
set label sprintf("b2 = %5.2f +/- %5.2f",b2, b2_err/FIT_STDFIT) at graph 0.03, 0.69
set label sprintf("{/Symbol c}^2 = %5.2f", chisq) at graph 0.03, 0.62
set label sprintf("{/Symbol c}^2/NDF = %5.2f", FIT_STDFIT**2) at graph 0.03, 0.55
set label sprintf("Q = %5.2f", Q) at graph 0.03, 0.48

#########################################################
# how to plot of a function but only over a certain range of x
#plot x >= 50 ? f(x)  : 0/0 notitle ls 1, \
# to plot a line specified from the "standard input", i.e. the "-".
# plot "-" with lines lt 2 lw 3 lc rgb "black" notitle
#0.77 -0.01
#0.77 0.02
#end
#########################################################

######################################################
# Now do the plot
#########################################################
plot \
"test_data" index 0 using 1:2:3 w errorbars pt 4 lw 3 lt 1 lc rgb "red" t "data 0", \
"test_data" index 1 using 1:2:3 w errorbars pt 6 lw 3 lt 1 lc rgb "#00DD00" t "data 1", \
"test_data" index 2 using 1:2:3 w errorbars pt 8 lw 3 lt 1 lc rgb "blue" t "data 2", \
f0(x) lt 1 lw 3 lc rgb "red", \
f1(x) lt 1 lw 3 lc rgb "#00DD00", \
f2(x) lt 1 lw 3 lc rgb "blue"
