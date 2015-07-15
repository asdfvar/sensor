#!/usr/bin/python

import csv
import numpy as np
import pylab as pl

class read_correlations:

   def __init__(self, path):

      fid = open(path, 'r')
      reader = csv.reader(fid)
      row_count = sum(1 for row in reader)
      fid.close()

      self.correlations   = np.zeros( row_count, dtype = float )

      with open(path,'r') as fid:
         reader = csv.reader(fid)

         for p, row in enumerate( reader ):
            for k, data in enumerate( row ):
               if k == 0:
                  self.correlations[p] = float( data )

   def plot(self):

      pl.ylim([0.0, 1.0])
      pl.title("Correlations")
      pl.yticks(np.arange(0.0, 1.001, 0.1))
      pl.plot( np.clip(self.correlations, 0.0, 1.2), 'green')

      pl.show()

   def print_stats(self):
      print "correlation stats:"
      print "\tmax  = %f" % max(self.correlations)
      print "\tmean = %f" % np.mean(self.correlations)
      print "\tstd  = %f" % np.std(self.correlations)
