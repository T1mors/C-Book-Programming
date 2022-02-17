#/*******************************************************************/
#/*** Gnuplot script, which fits a Fisher-Tippett function to     ***/
#/*** data in the file "ft.dat" and shows result                  ***/
#/***                                                             ***/
#/*** Solution of a problem from the book:                        ***/
#/*** A.K. Hartmann                                               ***/
#/*** A practical guide to computer simulation                    ***/
#/*** World Scientific, Singapore 2008                            ***/
#/***                                                             ***/
#/*** Chapter: Randomness and statistics                          ***/
#/*** Section: exercises                                          ***/
#/*******************************************************************/
set logscale y
plot "ft.dat"
f(x)=l*exp(-l*(x-x0))*exp(-exp(-l*(x-x0)))
l=1.0
x0=1.0
fit [1:6] f(x) "ft.dat" via l, x0
plot [1:10] "ft.dat", f(x)
pause -1 "Hit enter to finish"
