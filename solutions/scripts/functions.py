#!/usr/bin/python

def factorial(n):
    if n <= 1:
        return(1)
    else:
        return(n*factorial(n-1))

def change1(x):
    x=5
    print x

def change2(l):
    ll=len(l)
    l.append(ll)

print factorial(5)

z=10
print z
change1(z)
print z

list=[]
change2(list)
change2(list)
change2(list)
print list

