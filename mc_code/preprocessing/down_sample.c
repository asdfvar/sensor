#include "down_sample.h"
#include <stdio.h>

int down_sample (float *data,
                 float  sampling_freq,
                 float  time_length,
                 int    downsamp_fact,
                 float *workspace)
{

   if (downsamp_fact <= 1) return sampling_freq;

   sampling_freq /= (float)downsamp_fact;
   float *weights = workspace;
   int window = 2 * downsamp_fact - 1;
   int ind, new_ind, k;
   int N = (int)(sampling_freq * time_length);
   float norm = 1.0f / (float)(downsamp_fact * downsamp_fact);

   for (k = 0; k <= window / 2; k++) weights[k] = (float)(k + 1);
   for (k = 0, ind = window - 1; k < window / 2; k++, ind--) weights[ind] = (float)(k + 1);
   for (k = 0; k < window ; k++) weights[k] *= norm;

   float val;
   for (new_ind = 0, ind = 0; new_ind < N-1; ind += downsamp_fact, new_ind++)
   {
      val = 0.0f;
      for (k = 0; k < window; k++) val += data[ind + k] * weights[k];
      data[new_ind] = val;
   }

   norm = 1.0f / (0.5f * (float)(downsamp_fact * (downsamp_fact + 1)));
   val = 0.0f;
   for (k = 0; k < window/2; k++) val += data[ind + k] * weights[k];
   data[new_ind] = val;

   return sampling_freq;
}
