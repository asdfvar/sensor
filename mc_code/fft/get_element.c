#include "fft.h"
#include <stdio.h>

#define WORDS 2

/* Function NAME: ref_element
**
*/
inline float *ref_element(
                      float *x,       /* The  array                       */
                      int    start,   /* starting location on the array   */
                      int    stride,  /* elements to stride by from start */
                      int    element, /* the select element from start    */
                      int    words)   /* number of words per element      */
{
   float *el_ptr;

   el_ptr = x + (start + element * stride) * words;
   return el_ptr;
}

/* Function NAME: get_element_conj_sym
**
*/
inline float get_element_conj_sym(
                      float *x,       /* The conjugate symmetric array    */
                      int    start,   /* starting location on the array   */
                      int    stride,  /* elements to stride by from start */
                      int    N,       /* number of elements in this array */
                      int    element, /* the select element from start    */
                      int    part)    /* real part = 1, imag part = 2     */
{

   int sel_el = (start + element * stride) * WORDS;

   if (sel_el <= WORDS * N / 2)
   {

      if (part == 1)
         return x[sel_el];
      else if (part == 2)
         return x[sel_el + 1];
      else
         return 0.0f;
   }
   else
   {
      sel_el = (N - (start + element * stride)) * WORDS;

      if (part == 1)
         return x[sel_el];
      else if (part == 2)
         return -x[sel_el + 1];
      else
         return 0.0f;
   }

}
