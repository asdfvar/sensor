#include "sensor.h"
#include "preproc.h"
#include "run_mf.h"
#include <stdio.h>

/*
** Function NAME: training_main
*/
void training_main(
 /*[I ]*/ const float  sampling_freq,          /* Sampling frequency                          */
 /*[I ]*/ const float  data_time_length,       /* data time length in seconds                 */
 /*[I ]*/ const float  total_data_time_length, /* total time length of the incoming data      */
 /*[I ]*/ const float *ax,                     /* Acceleration data in x                      */
 /*[I ]*/ const float *ay,                     /* Acceleration data in x                      */
 /*[I ]*/ const float *az,                     /* Acceleration data in x                      */
 /*[I ]*/ const float  ref_time_length,        /* Time length for the reference               */
 /*[ O]*/ float       *reference_x,            /* Reference x                                 */
 /*[ O]*/ float       *reference_y,            /* Reference y                                 */
 /*[ O]*/ float       *reference_z,            /* Reference z                                 */
 /*[I ]*/ const int    num_samples,            /* Number of samples to test for reference     */
 /*[**]*/ void        *workspace)              /* pre-allocated buffer space. Size = TBD      */
{

   int k, p;

   float dt = 1.0f / sampling_freq;
   const int N_window       = (int)(sampling_freq * data_time_length);
   const int N_total_length = (int)(sampling_freq * total_data_time_length);
   const int N_window_ref   = (int)(sampling_freq * ref_time_length);
      
   float correlation = -1.0f;

   float *workspace_float = (float*)workspace;

   float *ref_buffer_x    = workspace_float; workspace_float += N_window + 2;
   float *ref_buffer_y    = workspace_float; workspace_float += N_window + 2;
   float *ax_buffer       = workspace_float; workspace_float += N_window + 2;
   float *ay_buffer       = workspace_float; workspace_float += N_window + 2;
   float *az_buffer       = workspace_float; workspace_float += N_window + 2;

   int    N_data = (int)(data_time_length * sampling_freq);

   int cand_ref, data_it;

   float best_ref_correlation = -1.0f;
   int   best_ref_index = 0;

   /*
   ** Loop through the candidate references
   */
   for (cand_ref = 0; cand_ref < num_samples; cand_ref++)
   {

      int start_ref_index = (int)((total_data_time_length - data_time_length) / num_samples) * cand_ref;

      for (k = 0; k < N_window; k++) ref_buffer_x[k] = ax[start_ref_index + k];
      for (k = 0; k < N_window; k++) ref_buffer_y[k] = ay[start_ref_index + k];
      for (k = 0; k < N_window; k++) az_buffer[k]    = az[start_ref_index + k];

      prep_ref(
            ref_buffer_x,
            ref_buffer_y,
            az_buffer,
            ref_time_length,
            data_time_length,
            sampling_freq,
            1,
            (void*)workspace_float);

      float sum_data_correlation = 0.0f;
      
      /*
      ** Test the given candidate reference against the rest of the data
      */
      for (data_it = 0; data_it < num_samples; data_it++)
      {

         int start_data_index = total_data_time_length / num_samples * data_it;

         for (k = 0; k < N_window; k++) ax_buffer[k] = ax[start_ref_index + k];
         for (k = 0; k < N_window; k++) ay_buffer[k] = ay[start_ref_index + k];
         for (k = 0; k < N_window; k++) az_buffer[k] = az[start_ref_index + k];

         /*
         ** PRE-PROCESSING
         */
         preproc (
              ax_buffer,         /* Acceleration data in x               */
              ay_buffer,         /* Acceleration data in y               */
              az_buffer,         /* Acceleration data in z               */
              NULL,              /* Resulting power of the signal        */
              dt,
              data_time_length,
              workspace_float,
              N_window);         /* Number of sample points              */
      
         /*
         ** MATCHED-FILTER
         */
         correlation = run_mf(
                           ax_buffer,
                           ay_buffer,
                           ref_buffer_x,
                           ref_buffer_y,
                           dt,
                           data_time_length,
                           ref_time_length,
                           sampling_freq,
                           workspace_float);

         sum_data_correlation += correlation;

      }

      if (sum_data_correlation > best_ref_correlation)
      {
         best_ref_correlation = sum_data_correlation;
         best_ref_index       = start_ref_index;
      }
   }

   /*
   ** Populate the reference data with the best solution
   */
   for (k = 0; k < N_window_ref; k++) reference_x[k] = ax[best_ref_index + k];
   for (k = 0; k < N_window_ref; k++) reference_y[k] = ay[best_ref_index + k];
   for (k = 0; k < N_window_ref; k++) reference_z[k] = az[best_ref_index + k];

   return;
}
