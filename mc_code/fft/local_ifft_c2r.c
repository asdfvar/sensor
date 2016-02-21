#include "fft.h"
#include <stdio.h>

inline void local_ifft_c2r(float *x,
                           float *y,
                           float *w,
                           int    start,
                           int    stride,
                           int    N,
                           int    N_orig,
                           float *workspace)
{

   int k, index;

   float *S1     = y;
   float *S2     = workspace;
   workspace    += 2*N;

   if (N <= 2 || N % 2 != 0)
   {

      idft_c2r(x,
               y,
               w,
               start,
               stride,
               N,
               N_orig);

      return;
   }

   // evens
   local_ifft_c2r(x,
                  S1,
                  w,
                  start,
                  2 * stride,
                  N/2,
                  N_orig,
                  workspace);

   // odds
   local_ifft_c2c(x,
                  S2,
                  w,
                  start + stride,
                  2 * stride,
                  N/2,
                  N_orig,
                  workspace);

   float *y_half = y + N/2;

   for (k = 0, index = 0; index < N/2; k++, index++)
   {

      float *w_ptr = ref_element(
                        w,
                        0,
                        stride,
                        k,
                        2);

      float tmp1     = S1[k] + (w_ptr[0]*S2[2*k] - w_ptr[1]*S2[2*k+1]);
      float tmp2     = S1[k] - (w_ptr[0]*S2[2*k] - w_ptr[1]*S2[2*k+1]);

      y[index]      = tmp1;
      y_half[index] = tmp2;
   }

}
