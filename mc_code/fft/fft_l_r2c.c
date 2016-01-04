#include "fft.h"
#include <stdio.h>

void fft_l_r2c(float *x,
               float *y,
               float *w,
               int    N,
               float *workspace)
{

   int k;

   if (N <= 2)
   {
      y[0] = x[0] + x[1];
      y[1] = 0;
      y[2] = x[0] + x[1]*w[2];
      y[3] = x[1]*w[3];

      return;
   }

   float *x_even = workspace;
   workspace    += N;
   float *x_odd  = workspace;
   workspace    += N;
   float *w_N_2  = workspace;
   workspace    += N;
   float *S1     = workspace;
   workspace    += N;
   float *S2     = workspace;
   workspace    += N;

   for (k = 0; k < N/2; k++) x_even[k] = x[2*k  ];
   for (k = 0; k < N/2; k++) x_odd[k]  = x[2*k+1];
   for (k = 0; k < N/2; k++) {
      w_N_2[2*k  ] = w[2*2*k  ];
      w_N_2[2*k+1] = w[2*2*k+1];
   }

   fft_l_r2c(x_even,
             S1,
             w_N_2,
             N/2,
             workspace);

   fft_l_r2c(x_odd,
             S2,
             w_N_2,
             N/2,
             workspace);

   for (k = 0; k <= N/2; k++)
   {
      y[2*k  ] = S1[2*k  ] + (w[2*k]*S2[2*k  ] - w[2*k+1]*S2[2*k+1]);
      y[2*k+1] = S1[2*k+1] + (w[2*k]*S2[2*k+1] + w[2*k+1]*S2[2*k  ]);
   }

}
