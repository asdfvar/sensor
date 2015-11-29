#include <math.h>
#include <stdio.h>

void sinwave(
       float *data,
       float omega,
       float phase,
       float amplitude,
       float time_length,
       float samp_freq)
{
   int k;
   int N = (int)(time_length * samp_freq);
   float dt = 1.0f / samp_freq;

   for (k = 0; k < N; k++)
   {
      data[k] = amplitude * sinf( omega * (k * dt) + phase);
   }
}
