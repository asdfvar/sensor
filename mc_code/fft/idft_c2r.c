#include <math.h>
#include "fft.h"
#include <stdio.h>

inline void idft_c2r(float *x,
                     float *y,
                     float *w,
                     int    N)
{
   int i,k;
   int index;
   float xr, xi;

   /*
   ** Compute the DFT
   */

   for (k = 0; k < N; k++)
   {
      y[k] = 0.0f;
      for (i = 0; i < N; i++)
      {

         xr = get_element_conj_sym(
                          x,    /* The conjugate symmetric array    */
                          0,    /* starting location on the array   */
                          1,    /* elements to stride by from start */
                          N,    /* number of elements in this array */
                          i,    /* the select element from start    */
                          1);   /* real part = 1, imag part = 2     */

         xi = get_element_conj_sym(
                          x,    /* The conjugate symmetric array    */
                          0,    /* starting location on the array   */
                          1,    /* elements to stride by from start */
                          N,    /* number of elements in this array */
                          i,    /* the select element from start    */
                          2);   /* real part = 1, imag part = 2     */

         index = k*i; index %= N;
         y[k] += xr*w[2*index] - xi*w[2*index+1];
      }

   }

}
