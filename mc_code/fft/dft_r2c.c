#include <math.h>
#include "fft.h"
#include <stdio.h>

void dft_r2c(float *x,
             float *y,
             int    N,
             float *workspace)
{
   float *w = workspace;

   int i,k;
   int index;

   const float neg_two_pi_N_inv = - TWO_PI / (float)N;

   /*
   ** Compute the twiddle factors
   */
   for (k = 0; k <= N; k++)
   {
      w[2*k  ] = cosf( neg_two_pi_N_inv * k );
      w[2*k+1] = sinf( neg_two_pi_N_inv * k );
   }

   /*
   **
   */
   for (k = 0; k <= N/2; k++)
   {
      y[2*k  ] = 0.0f;
      y[2*k+1] = 0.0f;

      for (i = 0; i < N; i++)
      {
         index = 2*k*i; index %= 2*N;
         y[2*k  ] += x[i] * w[ index     ];
         y[2*k+1] += x[i] * w[ index + 1 ];
      }
   }
}
