#!/usr/bin/python

import numpy as np
import pylab as pl

class read_reference:

   def __init__(self, path):

      with open(path, 'r') as fid:
         innards = fid.readlines();

         self.N         = int  (innards[0].split('=')[1])
         self.frequency = float(innards[1].split('=')[1])
         self.time      = float(innards[2].split('=')[1])
         self.ID        = int  (innards[3].split('=')[1])

         self.primary = innards[4]
         self.primary = self.primary.split(',')
         for k,x in enumerate(self.primary):
            self.primary[k] = float(x)
         self.primary = np.array(self.primary)

         self.secondary = innards[5]
         self.secondary = self.secondary.split(',')
         for k,x in enumerate(self.secondary):
            self.secondary[k] = float(x)
         self.secondary = np.array(self.secondary)

   def plot(self):
      t = np.linspace(0, self.time, self.N)
      fig = pl.figure()

      ax1 = fig.add_subplot(211)
      pl.xlim([0.0, self.time])
      pl.title("Primary Reference")
      pl.xlabel("Time (seconds)")
      pl.ylabel("Acceleration (g)")
      ax1.plot(t, self.primary, color='blue')

      ax2 = fig.add_subplot(212)
      pl.xlim([0.0, self.time])
      pl.title("Secondary Reference")
      pl.xlabel("Time (seconds)")
      pl.ylabel("Acceleration (g)")
      ax2.plot(t, self.secondary, color='red')
      pl.show()
