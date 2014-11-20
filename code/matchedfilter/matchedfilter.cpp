#include "matchedfilter.h"

/******************************************************************************/

matchedfilter::matchedfilter (float *ref_in, int N_in)
{

   N = N_in;
   ref = new float[N_in];

   for (int k = 0; k < N; k++)
      ref[k] = ref_in[k];

}

/******************************************************************************/

matchedfilter::~matchedfilter (void)
{

   delete[] ref;

}

/******************************************************************************/
