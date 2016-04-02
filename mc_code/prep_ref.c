#include "preproc.h"
#include "fft.h"
#include "sensor.h"
#include "down_sample.h"
#include <stdlib.h>

/*
** Function name: prep_ref
**
** Prepares the reference data for matched-filter processing. The
** motivation here is to prepare the reference data prior to writing
** it to storage memory so that it can be called and used when needed.
**
**   Steps:
**      1) Filter and downsample (filtering is combined with the downsample
**         to make use of neighboring data before it is deleted)
**      2) Pre-process the data. This step performs the dimensionality reduction
**         along with additional smoothing.
**      3) The FFT is applied to the now two dimensional reference data.
*/

void prep_ref(
 /* [IO] */ float       *ref_ax,
 /* [IO] */ float       *ref_ay,
 /* [IO] */ float       *ref_az,
 /* [I ] */ const float  ref_time_length,
 /* [I ] */ const float  data_time_length,
 /* [I ] */ float        sampling_freq,
 /* [I ] */ const int    downsamp_fact,
 /* [**] */ void        *workspace)
{

   float *workspace_float = (float*)workspace;

   int k;
   float output_samp_freq;

   output_samp_freq = down_sample (ref_ax,
                                   sampling_freq,
                                   ref_time_length,
                                   downsamp_fact,
                                   workspace_float);

   output_samp_freq = down_sample (ref_ay,
                                   sampling_freq,
                                   ref_time_length,
                                   downsamp_fact,
                                   workspace_float);

   output_samp_freq = down_sample (ref_az,
                                   sampling_freq,
                                   ref_time_length,
                                   downsamp_fact,
                                   workspace_float);

   sampling_freq = output_samp_freq;

   float dt               = 1.0f / sampling_freq;
   int   N_window         = sampling_freq * data_time_length;
   int   N_window_ref     = sampling_freq * ref_time_length;

   for (k = N_window_ref; k < N_window; k++) ref_ax[k] = 0.0f;
   for (k = N_window_ref; k < N_window; k++) ref_ay[k] = 0.0f;
   for (k = N_window_ref; k < N_window; k++) ref_az[k] = 0.0f;

   /*
   ** PRE-PROCESSING
   */
   preproc (
        ref_ax,            /* Acceleration in x               */
        ref_ay,            /* Acceleration in y               */
        ref_az,            /* Acceleration in z               */
        NULL,              /* Resulting power of the signal   */
        dt,
        data_time_length,
        workspace_float,
        N_window_ref);     /* Number of sample points         */

   float *buffer = workspace_float; workspace_float += N_window;

   for (k = 0; k < N_window; k++) buffer[k]     = 0.0f;
   for (k = 0; k < N_window_ref; k++) buffer[k] = ref_ax[k];

   local_fft_wrapper_r2c(buffer,
                         ref_ax,
                         N_window,
                         workspace_float);

   for (k = 0; k < N_window; k++) buffer[k]     = 0.0f;
   for (k = 0; k < N_window_ref; k++) buffer[k] = ref_ay[k];
   
   local_fft_wrapper_r2c(buffer,
                         ref_ay,
                         N_window,
                         workspace_float);

   return;
}
