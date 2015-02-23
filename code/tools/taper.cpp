/*
 * Produce the complex taper used as a lowpass filter prior to
 * doing the cross correlation.
 */

#include <cmath>
#include <iostream>

#define PIO2 1.5707963267948966

void taper_f(
       float *taper,      // taper data of size N+2
       float time_window,
       float cutoff_freq,
       float freq_range,  // Hz. In each direction from cut-off frequency
       float samp_freq,
       float dt,
       int   N)
{

   float df = 1.0f / (dt * (float)N);

   int freq_range_N_hlf = (int)(freq_range / df);
   int cutoff_index = (int)(cutoff_freq / df);

   float arg, tmp;
   int k,k2;

   for (int k=0; k<N+2; k++) taper[k] = 1.0f;

   if (2*(cutoff_index + freq_range_N_hlf) < N+2  && 2*(cutoff_index - freq_range_N_hlf) >= 0)
   {
      for (k=0, k2=2*(cutoff_index - freq_range_N_hlf);
           k<2*freq_range_N_hlf;
           k++, k2+=2)
      {
         arg = (float)k / (float)(2*freq_range_N_hlf-1) * PIO2;
         tmp = cosf(arg);
         tmp *= tmp;
         taper[k2]   = tmp;
         taper[k2+1] = tmp;
      }

      for (k=2*(cutoff_index + freq_range_N_hlf); k<N+2; k++) taper[k] = 0.0f;
   }

}
