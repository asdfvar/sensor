#include "local_trig.h"
#include "fft.h"
#include <stdio.h>

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
      w[2*k  ] = local_cos( two_pi_N_inv * (float)k );
      w[2*k+1] = local_sin( two_pi_N_inv * (float)k );
   }

   local_ifft_c2r(x,
                  y,
                  w,
                  0,
                  1,
                  N,
                  N,
                  workspace);

   const float scale = 1.0f / (float)N;
   for (k = 0; k < N; k++) y[k] *= scale;
}
