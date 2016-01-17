#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void idft_c2c(float *x,
                     float *y,
                     float *w,
                     int    N)
{
   int i,k;
   int index;

   /*
   ** Compute the DFT
   */
   for (k = 0; k < N; k++)
   {

      y[2*k  ] = 0.0f;
      y[2*k+1] = 0.0f;

      for (i = 0; i < N; i++)
      {
         index = k*i; index %= N;
         y[2*k  ] += x[2*i  ]*w[2*index] - x[2*i+1]*w[2*index+1];
         y[2*k+1] += x[2*i+1]*w[2*index] + x[2*i  ]*w[2*index+1];
      }

   }

printf("%s:%d:inputs: ",__FILE__,__LINE__);
for (k = 0; k < N; k++) printf("%f + %fj, ", x[2*k], x[2*k+1]);
printf("\n");
printf("w: ");
for (k = 0; k < N; k++) printf("%f + %fj, ", w[2*k],  w[2*k+1]);
printf("\n");
printf("outputs: ");
for (k = 0; k < N; k++) printf("%f + %fj, ", y[2*k], y[2*k+1]);
printf("\n");
printf("\n");

}
