#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void dft_r2c(float *x,
                    float *y,
                    float *w,
                    int    w_start,
                    int    w_stride,
                    int    N)
{
   int i,k;
   int index;

   float *w_ptr;

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

         w_ptr = ref_element(
                        w,
                        w_start,
                        w_stride,
                        index,
                        2);

         y[2*k  ] += x[i] * w_ptr[0];
         y[2*k+1] += x[i] * w_ptr[1];
      }
   }

}

