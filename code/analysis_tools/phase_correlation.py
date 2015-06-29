#!/usr/bin/python
import numpy as np
import math
import pylab as pl
from numpy import linalg as la

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
   norm_array[0:norm_size] = 1.0 / norm_1 * norm_2

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
   ref will pass over data (remain stationary) to produce
   the normalized correlation

   positive lags (zero based index) mean to circular shift ref 
   in the positive direction by that much followed by a dot product
   with data to produce the corresponding value in the
   correlation array at that index

   len(ref) <= len(data), numpy arrays
'''

class phase_correlation:

   def __init__(self, ref, data, n_point=1 ):

      ref   = smooth( ref, n_point )
      data  = smooth( data, n_point )

      norm                       = normalizing_array( ref, data )
      self.norm                  = norm
      ref                        = zero_pad( ref, data )
      cross_corr                 = cross_correlation( ref, data)
      cross_corr                 = abs( cross_corr )
      self.cross_corr            = cross_corr
      cross_corr_normalized      = cross_corr * norm
      self.cross_corr_normalized = cross_corr_normalized
      pl.plot(norm)
      pl.show()

      matched_corr = cross_corr_normalized.max()

      lag          = cross_corr_normalized.argmax()

      ref_1_rolled = np.roll( ref, lag )

      self.ref_1_rolled = ref_1_rolled
      self.matched_corr   = matched_corr

      self.ref_norm  = la.norm( ref  )
      self.data_norm = la.norm( data )

      self.ref = ref 
      self.data = data 

   def plot_match( self, samp_freq=128.0):
      dt = 1.0 / samp_freq
      end = len(self.data) * dt
      time = np.linspace( 0, end, len(self.data))
      pl.plot(time, self.data, 'r', linewidth=3.0)
      pl.plot(time, self.ref_1_rolled, 'g', linewidth=2.0)
      pl.xlabel("Time (seconds)")
      pl.ylabel("Acceleration (g)")
      pl.show()
