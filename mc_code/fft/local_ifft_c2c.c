#include "fft.h"
#include <stdio.h>

inline void local_ifft_c2c(float *x,
                           float *y,
                           float *w,
                           int    start,
                           int    stride,
                           int    N,
                           int    N_orig)
{

   int k, index;

   float *S1 = y;
   float *S2 = y + N;

   if (N <= 2 || N % 2 != 0)
   {

      idft_c2c(x,
               y,
               w,
               start,
               stride,
               N_orig,
               N);

      return;
   }

   local_ifft_c2c(x,
                  S1,
                  w,
                  start,
                  2*stride,
                  N/2,
                  N_orig);

   local_ifft_c2c(x,
                  S2,
                  w,
                  start + stride,
                  2*stride,
                  N/2,
                  N_orig);

   float *y_half = y + N;

   for (k = 0, index = 0; index < N/2; k++, index++)
   {

      float *w_ptr = ref_element(
                     w,
                     0,
                     stride,
                     k,
                     2);

      float tmp1[2];
      float tmp2[2];

      tmp1[0] = S1[2*k  ] + (w_ptr[0]*S2[2*k  ] - w_ptr[1]*S2[2*k+1]);
      tmp1[1] = S1[2*k+1] + (w_ptr[0]*S2[2*k+1] + w_ptr[1]*S2[2*k  ]);

      tmp2[0] = S1[2*k  ] - (w_ptr[0]*S2[2*k  ] - w_ptr[1]*S2[2*k+1]);
      tmp2[1] = S1[2*k+1] - (w_ptr[0]*S2[2*k+1] + w_ptr[1]*S2[2*k  ]);

      y[2*index  ] = tmp1[0];
      y[2*index+1] = tmp1[1];

      y_half[2*index  ] = tmp2[0];
      y_half[2*index+1] = tmp2[1];
   }

}
