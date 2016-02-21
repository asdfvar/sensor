#include "local_trig.h"
#include "fft.h"
#include <math.h>
#include <stdio.h>

inline void local_fft_wrapper_r2c(float *x,
                                  float *y,
                                  int    N,
                                  float *workspace)
{

   int k;
   const float two_pi_N_inv = TWO_PI / (float)N;

   float *w = workspace;
   workspace += 2*N;

   /*
   ** Compute the twiddle factors
   */
   for (k = 0; k <= N; k++)
   {
      w[2*k  ] = cosf( -two_pi_N_inv * (float)k );
      w[2*k+1] = sinf( -two_pi_N_inv * (float)k );
   }

   /*
   ** Compute nyquist
   */
   float nyquist = 0.0f;
   for (k = 0; k < N; k++) nyquist = x[k] - nyquist;
   nyquist = -nyquist;

   float *fft_output = workspace;

   local_fft_r2c(x,
                 fft_output,
                 w,
                 N,
                 1,
                 0);

   for (k = 0; k <= N/2; k++)
   {
      y[2*k  ] = fft_output[2*k  ];
      y[2*k+1] = fft_output[2*k+1];
   }

   if ( N % 2 == 0) y[N] = nyquist;

}
