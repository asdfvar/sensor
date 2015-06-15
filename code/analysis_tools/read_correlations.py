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

      self.correlations_primary   = np.zeros( row_count, dtype = float )
      self.correlations_secondary = np.zeros( row_count, dtype = float )

      with open(path,'r') as fid:
         reader = csv.reader(fid)

         for p, row in enumerate( reader ):
            for k, data in enumerate( row ):
               if k == 0:
                  self.correlations_primary[p] = float( data )
               elif k == 1:
                  self.correlations_secondary[p] = float( data )

   def plot(self):
      fig = pl.figure()

      ax1 = fig.add_subplot(211)
      pl.ylim([0.0, 1.0])
      pl.title("Primary Signature Correlations")
      ax1.plot( np.clip(self.correlations_primary, 0.0, 1.0), 'blue')

      ax2 = fig.add_subplot(212)
      pl.ylim([0.0, 1.0])
      pl.title("Secondary Signature Correlations")
      ax2.plot( np.clip(self.correlations_secondary, 0.0, 1.0), 'red')

      pl.show()

   def print_stats(self):
      print "Primary correlation stats:"
      print "\tmax = %f" % max(self.correlations_primary)
      print "\tmean = %f" % np.mean(self.correlations_primary)
      print "\tstd = %f" % np.std(self.correlations_primary)

      print "Secondary correlation stats:"
      print "\tmax = %f" % max(self.correlations_secondary)
      print "\tmean = %f" % np.mean(self.correlations_secondary)
      print "\tstd = %f" % np.std(self.correlations_secondary)
