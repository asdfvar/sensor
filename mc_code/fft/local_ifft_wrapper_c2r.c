#include "local_trig.h"
#include "fft.h"
#include <stdio.h>
#include <math.h>

void local_ifft_wrapper_c2r(float *x,
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
      w[2*k  ] = cosf( two_pi_N_inv * (float)k );
      w[2*k+1] = sinf( two_pi_N_inv * (float)k );
   }

   float *ifft_output = workspace;
   workspace += 2*N;

   local_ifft_c2r(x,
                  ifft_output,
                  w,
                  0,
                  1,
                  N,
                  N);

   for (k = 0; k < N; k++) y[k] = ifft_output[k];

   const float scale = 1.0f / (float)N;
   for (k = 0; k < N; k++) y[k] *= scale;
}
