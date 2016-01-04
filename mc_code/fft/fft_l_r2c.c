#include "fft.h"
#include <stdio.h>

void fft_l_r2c(float *x,
               float *y,
               float *w,
               int    N,
               float *workspace)
{

   int k;

printf("input: ");
for (k = 0; k < N; k++) printf("%f, ", x[k]);
printf("\n");

   if (N <= 2)
   {
      y[0] = x[0] + x[1];
      y[1] = 0.0f;
      y[2] = x[0] + x[1]*w[2];
      y[3] = x[1]*w[3];
      y[4] = x[0] - x[1];
      y[5] = 0.0f;

printf("output: ");
for (k = 0; k <= N/2; k++) printf("(%f, %f) ", y[2*k], y[2*k+1]);
printf("\n");

      return;
   }
   else if (N == 5)
   {
#if 0
      y[0] = x[0] + x[1] + x[2] + x[3] + x[4];
      y[1] = 0.0f;
      y[2] = x[0] + x[1]*w[2] + x[2]*w[4] + x[3]*w[6] + x[4]*w[8];
      y[3] = x[1]*w[3] + x[2]*w[5] + x[3]*w[7] + x[4]*w[9];
      y[4] = x[0]
      y[5]
      y[6]
      y[7]
      y[8]
      y[9]
#endif
   }

   float *x_even = workspace;
   workspace    += N;
   float *x_odd  = workspace;
   workspace    += N;
   float *w_N_2  = workspace;
   workspace    += N;
   float *S1     = workspace;
   workspace    += 2*N;
   float *S2     = workspace;
   workspace    += 2*N;

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

   /*
   ** Expand based on conjugate symmetry
   */
   int p;
   for (k = N/2/2+1, p = N/2/2-1; k < N/2; k++, p--)
   {
      S1[2*k  ] =  S1[2*p  ];
      S1[2*k+1] = -S1[2*p+1];
      S2[2*k  ] =  S2[2*p  ];
      S2[2*k+1] = -S2[2*p+1];
   }

#if 1
printf("S1 = ");
for (k = 0; k < N/2; k++) printf("(%f, %f), ", S1[2*k], S1[2*k+1]);
printf("\n");
printf("S2 = ");
for (k = 0; k < N/2; k++) printf("(%f, %f), ", S2[2*k], S2[2*k+1]);
printf("\n");
#endif

   for (k = 0; k < N/2; k++)
   {
      y[2*k  ] = S1[2*k  ] + (w[2*k]*S2[2*k  ] - w[2*k+1]*S2[2*k+1]);
      y[2*k+1] = S1[2*k+1] + (w[2*k]*S2[2*k+1] + w[2*k+1]*S2[2*k  ]);
   }

   // Nyquist
   y[N] = y[N+1] = 0.0f;
   for (k = 0; k < N; k++) y[N] = x[k] - y[N];
   y[N] = -y[N];

printf("output: ");
for (k = 0; k <= N/2; k++) printf("(%f, %f) ", y[2*k], y[2*k+1]);
printf("\n");

}
