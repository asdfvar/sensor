#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void dft_r2c(float *x,
                    float *y,
                    float *w,
                    int    N)
{
   int i,k;
   int index;

   /*
   ** Compute the DFT
   */
   for (k = 0; k <= N/2; k++)
   {
      y[2*k  ] = 0.0f;
      y[2*k+1] = 0.0f;

      for (i = 0; i < N; i++)
      {
         index = k*i; index %= N;
         y[2*k  ] += x[i] * w[ 2*index     ];
         y[2*k+1] += x[i] * w[ 2*index + 1 ];
      }
   }

}
