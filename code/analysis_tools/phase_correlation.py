#!/usr/bin/python
import numpy as np
import math
import pylab as pl

'''
   array_1 will pass over array_2 (remain stationary) to produce
   the correlation array un-normalized

   positive lags (zero based index) mean to circular shift array_1
   in the positive direction by that much followed by a dot product
   with array_2 to produce the corresponding value in the
   correlation array at that index

   len(array_1) = len(array_2), numpy arrays
'''
def cross_correlation( array_1, array_2 ):
   array_1 = np.fft.fft( array_1 )
   array_2 = np.fft.fft( array_2 )

   correlation = array_1.conj() * array_2
   correlation = np.fft.ifft( correlation )

   correlation = correlation.real

   return correlation

'''
   Returns the normalizing factor array to use in normalizing
   the output of the phase_correlation.

   The size returned = len(array_2)

   len(array_1) <= len(array_2), numpy arrays
'''

def normalizing_array( array_1, array_2 ):
   norm_1 = math.sqrt( np.dot( array_1, array_1 ))

   norm_size = len(array_2) - len(array_1) + 1
   norm_2 = np.zeros(norm_size)

   for start in range(norm_size):
      end = start + len(array_1)
      norm_2[start] = math.sqrt( np.dot( array_2[start:end], array_2[start:end] ))

   norm_array = np.zeros( len(array_2) )
   norm_array[0:norm_size] = 1.0 / (norm_1 * norm_2)

   return norm_array

'''
   Zero pad array_1 so that len(array_1) = len(array_2)
'''

def zero_pad( array_1, array_2 ):
   new_array_1 = np.zeros( len(array_2) )
   new_array_1[0:len(array_1)] = array_1
   return new_array_1

'''
   Apply an n_point tent filter smoothing to the data
'''

def smooth( array , n_points):

   left_weights = np.arange( int(n_points / 2) + 1, dtype='float')
   right_weights = left_weights[::-1]

   weights = np.append( left_weights, right_weights[1::] ) + 1.0
   weights /= sum(weights)
   weights = np.roll( weights, -int(n_points / 2) )

   smoothed = np.convolve( weights, array )

   return smoothed

'''
   array_1 will pass over array_2 (remain stationary) to produce
   the normalized correlation

   positive lags (zero based index) mean to circular shift array_1
   in the positive direction by that much followed by a dot product
   with array_2 to produce the corresponding value in the
   correlation array at that index

   len(array_1) <= len(array_2), numpy arrays
'''

class phase_correlation:

   def __init__(self, array_1, array_2, n_point=1 ):

      array_1      = smooth( array_1, n_point )
      array_2      = smooth( array_2, n_point )

      norm         = normalizing_array( array_1, array_2 )
      array_1      = zero_pad( array_1, array_2 )
      correlation  = cross_correlation( array_1, array_2)
      correlation *= norm

      matched_corr = correlation.max()
      lag          = correlation.argmax()

      array_1_rolled = np.roll( array_1, lag )

      self.correlation    = correlation
      self.array_1_rolled = array_1_rolled
      self.matched_corr   = matched_corr

      self.array_1 = array_1
      self.array_2 = array_2

   def plot_match( self, samp_freq=128.0):
      dt = 1.0 / samp_freq
      end = len(self.array_2) * dt
      time = np.linspace( 0, end, len(self.array_2))
      pl.plot(time, self.array_2, 'r', linewidth=3.0)
      pl.plot(time, self.array_1_rolled, 'g', linewidth=2.0)
      pl.show()
