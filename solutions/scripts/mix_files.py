#!/usr/bin/python

# for getting command line arguments
import sys

# read file names from command line
file1=sys.argv[1]
file2=sys.argv[2]

# read in file 1
file = open(file1, "r")
line1=[]
for line in file:
   if (line[0] != '#'):
      line1.append(line)
file.close()

# read in file 2
file = open(file2, "r")
line2=[]
for line in file:
   if (line[0] != '#'):
      line2.append(line)
file.close()

# print line by line: 1st and 2nd col. of file1, 2nd col. of file2 
counter=0
while counter<len(line2):
   print line1[counter].split()[0], line1[counter].split()[1], \
   line2[counter].split()[1]
   counter=counter+1


