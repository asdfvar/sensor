import numpy as np
from numpy import linalg as la

def preproc(ax, ay, az):

   ax = ax - ax.mean()
   ay = ay - ay.mean()
   az = az - az.mean()

   x = np.c_[ax, ay, az].T
   covariance = np.dot(x, x.T)

   eig_values, eig_vectors = la.eigh( covariance )

   print eig_values
   xp = np.dot( x.T, eig_vectors )

   max_eig_ind = 0
   mid_eig_ind = 1
   min_eig_ind = 2

   if eig_values[max_eig_ind] < eig_values[min_eig_ind]:
      max_eig_ind, min_eig_ind = min_eig_ind, max_eig_ind
   if eig_values[max_eig_ind] < eig_values[mid_eig_ind]:
      max_eig_ind, mid_eig_ind = mid_eig_ind, max_eig_ind
   if eig_values[mid_eig_ind] < eig_values[min_eig_ind]:
      mid_eig_ind, min_eig_ind = min_eig_ind, mid_eig_ind

   # the '-' sign because the signal gets inverted for
   # whatever reason ???
   axp = -xp[:, max_eig_ind]
   ayp = -xp[:, mid_eig_ind]
   azp = -xp[:, min_eig_ind]

   return [axp, ayp, azp]
