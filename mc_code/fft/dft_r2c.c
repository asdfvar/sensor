#include <math.h>
#include "fft.h"

void dft_r2c(float *x,
             float *y,
             int    N,
             float *workspace)
{
   float *w = workspace;

   int i,k;

   const float neg_two_pi_N_inv = - TWO_PI / (float)N;

   /*
   ** Compute the twiddle factors
   */
   for (k = 0; k <= N; k+=2)
   {
      w[k  ] = cosf( neg_two_pi_N_inv * k );
      w[k+1] = sinf( neg_two_pi_N_inv * k );
   }

   /*
   **
   */
   for (k = 0; k <= N/2; k+=2)
   {
      y[k  ] = 0.0f;
      y[k+1] = 0.0f;

      for (i = 0; i <= N; i+=2)
      {
         y[k  ] += x[i] * w[ (k * i) % N    ];
         y[k+1] += x[i] * w[ (k * i) % N + 1];
      }
   }
}
