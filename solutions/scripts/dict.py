#!/usr/bin/python

Z={'H':1, 'He':2, "Li":3}
print Z
print Z['He']

Z[55]=98
print Z[55]

Z[78]='structure'
print Z[78]

Z[55]=[27,57]
del Z['He']
print Z

print Z.keys()
print Z.values()

for key in Z.keys():
  print "Z[", key, "]=", Z[key]

for key,value in Z.iteritems():
  print "Z[", key, "]=", value
 
