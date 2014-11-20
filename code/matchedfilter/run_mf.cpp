#include "matchedfilter.h"
#include "mflt.h"

float matchedfilter::run (float *signal, int N_sig)
{

   float *corr;
   int *shift;

   mflt::crosscorr (ref, signal, N, corr, shift);

   return *corr;

}
