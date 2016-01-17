#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void idft_c2r(float *x,
                     float *y,
                     float *w,
                     int    N)
{
   int i,k;
   int index, x_ind;

   /*
   ** Compute the DFT
   */
   for (k = 0; k < N; k++)
   {
      y[k] = 0.0f;
      for (i = 0; i <= N/2; i++)
      {
         index = k*i; index %= N;
         y[k] += x[2*i]*w[2*index] - x[2*i+1]*w[2*index+1];
      }

      for (i = N/2+1; i < N; i++)
      {
         index = k*i; index %= N;
         x_ind = 2*(N/2) - i;
         y[k] += x[2*x_ind]*w[2*index] + x[2*x_ind+1]*w[2*index+1];
      }
   }

}
