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
      pl.plot( np.clip(self.correlations_primary, 0.0, 1.0), 'r')
      pl.plot( np.clip(self.correlations_secondary, 0.0, 1.0), 'g')
      pl.show()
