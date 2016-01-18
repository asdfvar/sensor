#include "fft.h"
#include <stdio.h>

inline void local_ifft_c2c(float *x,
                           float *y,
                           float *w,
                           int    start,
                           int    stride,
                           int    N,
                           int    N_orig,
                           float *workspace)
{

   int k, index;

   float *x_sub = workspace;
   workspace    += 2*N;
   float *w_N_2  = workspace;
   workspace    += N;
   float *S1     = workspace;
   workspace    += 2*N;
   float *S2     = workspace;
   workspace    += 2*N;

   if (N <= 2 || N % 2 != 0)
   {

      for (k = 0; k < N; k++)
      {
         x_sub[2*k] = get_element_conj_sym(
                             x,       /* The conjugate symmetric array    */
                             start,   /* starting location on the array   */
                             stride,  /* elements to stride by from start */
                             N_orig,  /* number of elements in this array */
                             k,       /* the select element from start    */
                             1);      /* real part = 1, imag part = 2     */

         x_sub[2*k+1] = get_element_conj_sym(
                             x,       /* The conjugate symmetric array    */
                             start,   /* starting location on the array   */
                             stride,  /* elements to stride by from start */
                             N_orig,  /* number of elements in this array */
                             k,       /* the select element from start    */
                             2);      /* real part = 1, imag part = 2     */
      }

      idft_c2c(x_sub,
               y,
               w,
               N);

printf("start = %d, stride = %d\n", start, stride);
printf("%s:%d:inputs: ",__FILE__,__LINE__);
for (k = 0; k <= N/2; k++) printf("%f+%fj, ", x_sub[2*k], x_sub[2*k+1]);
printf("\n");
printf("outputs: ");
for (k = 0; k < N; k++) printf("%f+%fj, ", y[2*k], y[2*k+1]);
printf("\n");
printf("\n");

      return;
   }

#if 0
   for (k = 0, index = 0; k <= N/2/2; k++, index+=2)
   {
      x_even[2*k  ] = x[2*index  ];
      x_even[2*k+1] = x[2*index+1];
   }
   for (k = N/2/2+1, index = N/2-1; k < N/2; k++, index-=2)
   {
      x_even[2*k  ] =  x[2*index  ];
      x_even[2*k+1] = -x[2*index+1];
   }

   for (k = 0, index = 1; k < N/2/2; k++, index+=2)
   {
      x_odd[2*k  ] = x[2*index  ];
      x_odd[2*k+1] = x[2*index+1];
   }
   for (k = N/2/2, index = N/2-2; k < N/2; k++, index-=2)
   {
      x_odd[2*k  ] =  x[2*index  ];
      x_odd[2*k+1] = -x[2*index+1];
   }
#endif

   for (k = 0; k < N/2; k++)
   {
      w_N_2[2*k  ] = w[2*(2*k)  ];
      w_N_2[2*k+1] = w[2*(2*k)+1];
   }

   local_ifft_c2c(x,
                  S1,
                  w_N_2,
                  start,
                  2*stride,
                  N/2,
                  N_orig,
                  workspace);

   local_ifft_c2c(x,
                  S2,
                  w_N_2,
                  start + stride,
                  2*stride,
                  N/2,
                  N_orig,
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

printf("S1: ");
for (k = 0; k < N/2; k++) printf("%f+%fj, ", S1[2*k], S1[2*k+1]);
printf("\n");
printf("S2: ");
for (k = 0; k < N/2; k++) printf("%f+%fj, ", S2[2*k], S2[2*k+1]);
printf("\n");
printf("w: ");
for (k = 0; k < N; k++) printf("%f+%fj, ", w[2*k], w[2*k+1]);
printf("\n");

   for (k = 0, index = 0; index < N/2; k++, index++)
   {
      y[2*index  ] = S1[2*k  ] + (w[2*k]*S2[2*k  ] - w[2*k+1]*S2[2*k+1]);
      y[2*index+1] = S1[2*k+1] + (w[2*k]*S2[2*k+1] + w[2*k+1]*S2[2*k  ]);
   }

   for (k = 0, index = N/2; index < N; k++, index++)
   {
      y[2*index  ] = S1[2*k   ] - (w[2*k]*S2[2*k  ] - w[2*k+1]*S2[2*k+1]);
      y[2*index+1] = S1[2*k +1] - (w[2*k]*S2[2*k+1] + w[2*k+1]*S2[2*k  ]);
   }

printf("start = %d, stride = %d\n", start, stride);
printf("%s:%d:inputs: ",__FILE__,__LINE__);
for (k = 0; k < N; k++) printf("%f+%fj, ",
                              get_element_conj_sym( x, start, stride,
                                                    N_orig, k, 1),
                              get_element_conj_sym( x, start, stride,
                                                    N_orig, k, 2));
printf("\n");
printf("outputs: ");
for (k = 0; k < N; k++) printf("%f+%fj, ", y[2*k], y[2*k+1]);
printf("\n");
printf("\n");

}
