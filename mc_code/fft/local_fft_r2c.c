#include "fft.h"

inline void local_fft_r2c(float *x,
                          float *y,
                          float *w,
                          int    N,
                          int    stride,
                          int    start)
{

   int k;

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

   float *S1     = y;
   float *S2     = y + N;

   local_fft_r2c(x,
                 S1,
                 w,
                 N/2,
                 stride*2,
                 start);

   local_fft_r2c(x,
                 S2,
                 w,
                 N/2,
                 stride*2,
                 start + stride);

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
      float *w_ptr = ref_element(
                        w,
                        0,
                        stride,
                        k,
                        2);

      float tmp[2];

      tmp[0] = S1[2*k  ] + (w_ptr[0]*S2[2*k  ] - w_ptr[1]*S2[2*k+1]);
      tmp[1] = S1[2*k+1] + (w_ptr[0]*S2[2*k+1] + w_ptr[1]*S2[2*k  ]);
      y[2*k  ] = tmp[0];
      y[2*k+1] = tmp[1];
   }

   // Nyquist
   y[N] = y[N+1] = 0.0f;
   for (k = 0; k < N; k++)
   {
      float *x_ptr = ref_element(
                     x,
                     start,
                     stride,
                     k,
                     1);

      y[N] = x_ptr[0] - y[N];
   }
   y[N] = -y[N];

}
