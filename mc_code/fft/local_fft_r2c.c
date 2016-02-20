#include "fft.h"

inline void local_fft_r2c(float *x,
                          float *y,
                          float *w,
                          int    N,
                          int    level,
                          int    start,
                          float *workspace)
{

   int k;

   int stride = 1 << level;

   if (N <= 2 || N % 2 != 0)
   {
      dft_r2c(x,
              y,
              w,
              start,
              stride,
              N);

      return;
   }

   float *S1     = workspace;
   workspace    += 2*N;
   float *S2     = workspace;
   workspace    += 2*N;

   local_fft_r2c(x,
                 S1,
                 w,
                 N/2,
                 level + 1,
                 start,
                 workspace);

   local_fft_r2c(x,
                 S2,
                 w,
                 N/2,
                 level + 1,
                 start + 1,
                 workspace);

   /*
   ** Expand based on conjugate symmetry
   */
   int p;
   for (k = N/2/2+1, p = (N/2+1)/2-1; k < N/2; k++, p--)
   {
      S1[2*k  ] =  S1[2*p  ];
      S1[2*k+1] = -S1[2*p+1];
      S2[2*k  ] =  S2[2*p  ];
      S2[2*k+1] = -S2[2*p+1];
   }

   for (k = 0; k < N/2; k++)
   {
      y[2*k  ] = S1[2*k  ] + (w[2*k]*S2[2*k  ] - w[2*k+1]*S2[2*k+1]);
      y[2*k+1] = S1[2*k+1] + (w[2*k]*S2[2*k+1] + w[2*k+1]*S2[2*k  ]);
   }

   // Nyquist
   y[N] = y[N+1] = 0.0f;
   for (k = 0; k < N; k++) y[N] = x[k] - y[N];
   y[N] = -y[N];

}
