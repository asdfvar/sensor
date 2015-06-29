import numpy as np
import math

class cross_corr:

   def __init__(self):
      self.phase_corrs = list()

   def combined_matched_corr(self):
      # assuming all are the same length
      sum_ref_norm   = np.zeros(len(self.phase_corrs[0].data))
      sum_data_norm  = np.zeros(len(self.phase_corrs[0].data))
      sum_cross_corr = np.zeros(len(self.phase_corrs[0].data))

      for phase_corr in self.phase_corrs:
         sum_ref_norm   += 1.0 / phase_corr.ref_norm ** 2
         sum_data_norm  += 1.0 / phase_corr.data_norm ** 2
         sum_cross_corr += phase_corr.cross_corr

      combined_norm = (np.sqrt( sum_ref_norm * sum_data_norm ))
      combined_corr = sum_cross_corr / combined_norm

      print "Combined correlation = %f" % combined_corr.max()
