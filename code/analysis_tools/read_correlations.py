#!/usr/bin/python

import csv
import numpy as np
import pylab as pl

class read_correlations:
   pass

fid = open('../output/correlations_demo17190', 'r')
fid.close()

primary   = np.array([])
secondary = np.array([])

with open('../output/correlations_demo17190','r') as fid:
   contents = csv.reader(fid)
   for line in contents:
      primary   = np.append(primary,   float(line[0]))
      secondary = np.append(secondary, float(line[1]))

pl.plot(primary)
pl.show()
