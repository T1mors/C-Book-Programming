#!/usr/bin/python

import sys
from random import random,seed,randint
from math import sqrt


def basicStatistics(myList):
	"""compute mean value, standard deviation,
	and standard error of the mean for the 
	supplied list of numerical values

	NOTE: so as to reduce roundoff errors, 
	variance is computed via the corrected
	two-pass algorithm, see
        "Numerical Recipes in C", 
        section 14.  Statistical Description of Data
        section 14.1 Moments of a Distribution

	Input:
	myList	-- sequence of numerical values

	Returns: (av,sDev,sErr)
	av	-- mean value
	sDev	-- standard deviation
	sErr	-- standard error of the mean
	"""
	av=var=tiny=0.

        # first pass to get mean 
	N  = len(myList) 
        av = float(sum(myList))/N
        # second pass to get variance
	for el in myList:
		dum   = el - av
		tiny += dum
		var  += dum*dum
        # correction step
	var = (var - tiny*tiny/N)/(N-1)
	sDev = sqrt(var)
	sErr = sDev/sqrt(N)
	return av, sDev, sErr


def bootstrap(array,estimFunc,nBootSamp=128):
	"""Empirical bootstrap resampling of data.
	
	estimates value of function 'estimFunc' from original data 
	stored in list 'array'. Calculates corresponding error as 
	standard deviation of the 'nBootSamp' resampled bootstrap 
	data sets

	Input:
	array     	-- list of values for resampling procedure
	estimFunc  	-- estimator function for resampling procedure
	nBootSamp  	-- number of bootstrap samples (default 128)

	Returns: (origEstim,resError)
	origEstim	-- value of estimFunc for original data
	resError	-- corresponding error estimated via resampling
	"""
	# estimate mean value from original array
	origEstim=estimFunc(array)
	## resample data from original array
	nMax=len(array)		
	h   = [0.0]*nBootSamp
	bootSamp = [0.0]*nMax 
	for sample in range(nBootSamp):
		for val in range(nMax):
			bootSamp[val]=array[randint(0,nMax-1)]
		h[sample]=estimFunc(bootSamp)
	## estimate error as std deviation of resampled values
	resError = basicStatistics(h)[1]
	return origEstim,resError

def Var(x):
        """abbreviate squared 2nd output parameter of basicStatics fcn
        yielding the standard deviation of the input data"""
        return basicStatistics(x)[1]*basicStatistics(x)[1]

def main():
        # generate array of N random numbers
        # fcn random() returns float r, 0.0 <= r < 1.0
        # expected variance: var_true = 1./12
        N=10000
        print "# Test data set: N=%d iid random numbers 0.0 <= r < 1.0"%(N)
        seed(11) 
        myData = [random() for i in range(N)]

        # basic summary measures 
        print "# Basic summary measures"
        av,sDev,sErr    = basicStatistics(myData)
        var=sDev*sDev
        print "av   = %lf \nsDev = %lf \nsErr = %lf \nvar  = %lf \n|var-var_true| = %lf"%(av,sDev,sErr,var,abs(var-1./12))
        print

        # bootstrap resampled variance, the term "lambda x: fcn(x)" provided
        # as second argument specifies a lambda function, i.e. an anonymous function 
        # defined on the fly
        print "# Bootstrap resampled variance (number of bootstrap samples = 20)"
        var_b,varErr_b  = bootstrap(myData, Var, 20) 
        print "var=%lf, varErr=%lf"%(var_b,varErr_b)
        print

if __name__=="__main__":
        main()        
