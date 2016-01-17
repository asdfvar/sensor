#include "fft.h"
#include <stdio.h>

inline void local_ifft_c2r(float *x,
                           float *y,
                           float *w,
                           int    N,
                           float *workspace)
{

   int k, index;

   if (N <= 2 || N % 2 != 0)
   {
      idft_c2r(x,
               y,
               w,
               N);

printf("%s:%d:inputs: ",__FILE__,__LINE__);
for (k = 0; k <= N/2; k++) printf("%f+%fj, ", x[2*k], x[2*k+1]);
printf("\n");
printf("outputs: ");
for (k = 0; k < N; k++) printf("%f, ", y[k]);
printf("\n");
printf("\n");

      return;
   }

   float *x_even = workspace;
   workspace    += N;
   float *x_odd  = workspace;
   workspace    += 2*N;
   float *w_N_2  = workspace;
   workspace    += N;
   float *S1     = workspace;
   workspace    += 2*N;
   float *S2     = workspace;
   workspace    += 2*N;

   for (k = 0; k <= N/2; k++)
   {
      x_even[2*k  ] = x[2*(2*k)  ];
      x_even[2*k+1] = x[2*(2*k)+1];
   }

   for (k = 0, index = 1; k < N/2/2; k++, index+=2)
   {
      x_odd[2*k  ] = x[2*index  ];
      x_odd[2*k+1] = x[2*index+1];
   }
   for (k = N/2/2, index = N/2-1; k < N/2; k++, index-=2)
   {
      x_odd[2*k  ] =  x[2*index  ];
      x_odd[2*k+1] = -x[2*index+1];
   }

   for (k = 0; k < N; k++)
   {
      w_N_2[(2*k) % (2*N)  ] = w[(2*(2*k))   % (2*N)];
      w_N_2[(2*k+1) % (2*N)] = w[(2*(2*k)+1) % (2*N)];
   }

   local_ifft_c2r(x_even,
                  S1,
                  w_N_2,
                  N/2,
                  workspace);

   local_ifft_c2c(x_odd,
                  S2,
                  w_N_2,
                  N/2,
                  workspace);

#if 0
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
#endif

   for (k = 0, index = 0; index < N/2; k++, index++)
   {
      y[index] = S1[k] + (w[2*k]*S2[2*k] - w[2*k+1]*S2[2*k+1]);
   }

   for (k = 0, index = N/2; index < N; k++, index++)
   {
      y[index] = S1[k] - (w[2*k]*S2[2*k] - w[2*k+1]*S2[2*k+1]);
   }

printf("%s:%d:inputs: ",__FILE__,__LINE__);
for (k = 0; k <= N/2; k++) printf("%f+%fj, ", x[2*k], x[2*k+1]);
printf("\n");
printf("outputs: ");
for (k = 0; k < N; k++) printf("%f, ", y[k]);
printf("\n");
printf("\n");

}
