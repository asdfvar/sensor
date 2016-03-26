#include "preproc.h"
#include "fft.h"
#include "sensor.h"
#include <stdlib.h>

void prep_ref(
 /* [IO] */ float       *ref_ax,
 /* [IO] */ float       *ref_ay,
 /* [IO] */ float       *ref_az,
 /* [I ] */ const float  ref_time_length,
 /* [I ] */ const float  data_time_length,
 /* [I ] */ const float  sampling_freq,
 /* [**] */ void        *workspace)
{

   int k;
   float dt = 1.0f / sampling_freq;
   int   N_window         = sampling_freq * data_time_length;
   int   N_window_ref     = sampling_freq * ref_time_length;
   float *workspace_float = (float*)workspace;

   preproc (
        ref_ax,            /* Acceleration in x               */
        ref_ay,            /* Acceleration in y               */
        ref_az,            /* Acceleration in z               */
        NULL,              /* Resulting power of the signal   */
        dt,
        data_time_length,
        workspace_float,
        N_window_ref);         /* Number of sample points         */


   float *buffer = workspace; workspace        += N_window;

   for (k = 0; k < N_window; k++) buffer[k]     = 0.0f;
   for (k = 0; k < N_window_ref; k++) buffer[k] = ref_ax[k];
   
   local_fft_wrapper_r2c(buffer,
                         ref_ax,
                         N_window,
                         workspace);

   for (k = 0; k < N_window; k++) buffer[k]     = 0.0f;
   for (k = 0; k < N_window_ref; k++) buffer[k] = ref_ay[k];
   
   local_fft_wrapper_r2c(buffer,
                         ref_ay,
                         N_window,
                         workspace);

   return;
}
