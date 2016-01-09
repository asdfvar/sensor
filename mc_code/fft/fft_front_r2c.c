#include <math.h>
#include <stdio.h>
#include "fft.h"

inline void fft_front_r2c(float *x,
                          float *y,
                          int    N,
                          float *workspace)
{

   int k;
   const float neg_two_pi_N_inv = - TWO_PI / (float)N;

   float *w = workspace;
   workspace += 2*N;

   /*
   ** Compute the twiddle factors
   */
   for (k = 0; k <= N; k++)
   {
      w[2*k  ] = cosf( neg_two_pi_N_inv * k );
      w[2*k+1] = sinf( neg_two_pi_N_inv * k );
   }

   /*
   ** Compute nyquist
   */
   float nyquist = 0.0f;
   for (k = 0; k < N; k++) nyquist = x[k] - nyquist;
   nyquist = -nyquist;

   fft_l_r2c(x,
             y,
             w,
             N,
             workspace);

   y[N] = nyquist;

}
