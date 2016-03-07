#include "sensor.h"
#include "preproc.h"
#include "run_mf.h"
#include <stdio.h>

void training_main(
 /*[I ]*/ const float sampling_freq,     /* Sampling frequency                         */
 /*[I ]*/ const float data_time_length,  /* data time length in seconds                */
 /*[I ]*/ const float time_inc,          /* Time increment for next energy calculation */
 /*[I ]*/ float      *ax,                /* Acceleration data in x                     */
 /*[I ]*/ float      *ay,                /* Acceleration data in x                     */
 /*[I ]*/ float      *az,                /* Acceleration data in x                     */
 /*[I ]*/ float      *ref_time_length,   /* Time lengths for the reference             */
 /*[I ]*/ float      *reference_x,       /* References                                 */
 /*[I ]*/ float      *reference_y,       /* References                                 */
 /*[**]*/ void       *workspace)         /* pre-allocated buffer space. Size = TBD     */
{

   int k, p;

   float dt = 1.0f / sampling_freq;
   const int   N_window = (int)(sampling_freq * data_time_length);

   float *workspace_float = (float*)workspace;

   float *ref_buffer_x    = workspace_float; workspace_float += N_window + 2;
   float *ref_buffer_y    = workspace_float; workspace_float += N_window + 2;
   int    N_data = (int)(data_time_length * sampling_freq);

   float *power;

   /*
   ** PRE-PROCESSING
   */
   preproc (
        ax,            /* Acceleration data in x               */
        ay,            /* Acceleration data in y               */
        az,            /* Acceleration data in z               */
        power,         /* Resulting power of the signal        */
        dt,
        data_time_length,
        workspace_float,
        N_window);     /* Number of sample points              */

   float best_correlation = -1.0f;

   for (k = 0; k < num_references; k++)
   {

      int   N_window_ref = (int)(sampling_freq * ref_time_length[k]);

      for (p = 0; p < N_window; p++) ref_buffer_x[p] = 0.0f;
      for (p = 0; p < N_window; p++) ref_buffer_y[p] = 0.0f;

      for (p = 0; p < N_window_ref; p++) ref_buffer_x[p] = reference_x[p];
      for (p = 0; p < N_window_ref; p++) ref_buffer_y[p] = reference_y[p];

      /*
      ** MATCHED-FILTER
      */
      float correlation =
                     run_mf(
                        ax,
                        ay,
                        ref_buffer_x,
                        ref_buffer_y,
                        dt,
                        data_time_length,
                        ref_time_length[k],
                        sampling_freq,
                        workspace_float);

   }

   return;
}
