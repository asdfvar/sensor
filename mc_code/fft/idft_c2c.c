#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void idft_c2c(float *x,
                     float *y,
                     float *w,
                     int    start,
                     int    stride,
                     int    N_orig,
                     int    N)
{
   int    i, k;
   int    index;
   float  x_sub[2];
   float *w_ptr;

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

         x_sub[0] = get_element_conj_sym(
                             x,       /* The conjugate symmetric array    */
                             start,   /* starting location on the array   */
                             stride,  /* elements to stride by from start */
                             N_orig,  /* number of elements in this array */
                             i,       /* the select element from start    */
                             1);      /* real part = 1, imag part = 2     */

         x_sub[1] = get_element_conj_sym(
                             x,       /* The conjugate symmetric array    */
                             start,   /* starting location on the array   */
                             stride,  /* elements to stride by from start */
                             N_orig,  /* number of elements in this array */
                             i,       /* the select element from start    */
                             2);      /* real part = 1, imag part = 2     */

         w_ptr = ref_element(
                        w,
                        0,
                        stride,
                        index,
                        2);

         y[2*k  ] += x_sub[0]*w_ptr[0] - x_sub[1]*w_ptr[1];
         y[2*k+1] += x_sub[1]*w_ptr[0] + x_sub[0]*w_ptr[1];
      }

   }

}
