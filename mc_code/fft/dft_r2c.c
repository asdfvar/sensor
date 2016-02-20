#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void dft_r2c(float *x,
                    float *y,
                    float *w,
                    int    start,
                    int    stride,
                    int    N)
{
   int i,k;
   int index;

   float *w_ptr;
   float *x_ptr;

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
                        0,
                        stride,
                        index,
                        2);

         x_ptr = ref_element(
                        x,
                        start,
                        stride,
                        i,
                        1);

         y[2*k  ] += x_ptr[0] * w_ptr[0];
         y[2*k+1] += x_ptr[0] * w_ptr[1];
      }
   }

}

