#!/usr/bin/python
import numpy as np
import math

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
   array_1 will pass over array_2 (remain stationary) to produce
   the normalized correlation

   positive lags (zero based index) mean to circular shift array_1
   in the positive direction by that much followed by a dot product
   with array_2 to produce the corresponding value in the
   correlation array at that index

   len(array_1) <= len(array_2), numpy arrays
'''

def phase_correlation( array_1, array_2 ):
   norm         = normalizing_array( array_1, array_2 )
   array_1      = zero_pad( array_1, array_2 )
   correlation  = cross_correlation( array_1, array_2)
   correlation *= norm
   return correlation
