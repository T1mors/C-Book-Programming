#!/usr/bin/python

a=[12, 45, 98, 112, 114, 135, 167, 298, 312];
counter=0
for value in a:
  counter=counter+value;print value
print "sum of", len(a), "elements:", counter
print range(7,12)
print a[1], a[2:6]
a.insert(3,77)
print a
a.extend([22, 8])
print a
a.sort()
print a

##
counter=3.5
while counter < 4.2:
  print counter*counter
  counter = counter + 0.1

