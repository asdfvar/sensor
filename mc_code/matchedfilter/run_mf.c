/*
 *     ( (ref_1 \dot sig_1)[i] + (ref_2 \dot sig_2)[i] ) /
 * sqrt( (ref_1 \dot ref_1 + ref_2 \dot ref_2) *
 *       (sig_1[i] \dot sig_1[i] + sig_2[i] \dot sig_2[i] ) )
 *
 * Note that sig_1,2[i] is a vector which means sig_1,2 is an array of vectors
 */
#include "phase_correlation.h"
#include <math.h>

/*
 * Function NAME: run_mf
 */
float run_mf ( float *primary_acceleration,
               float *secondary_acceleration,
               float *reference_x,
               float *reference_y,
               float  dt,
               float  time_window,
               float  ref_time_window,
               float  samp_freq,
               float *work_buffer)
{

   int k;

   int N_window         = (int)(time_window * samp_freq);
   int N_window_ref     = (int)(ref_time_window * samp_freq);
   int N_data_reference = N_window - N_window_ref + 1;

   /*
   ** Resurve memory for local variables
   */
   float *norm_primary_squared        = work_buffer; work_buffer += N_window;
   float *cross_correlation_primary   = work_buffer; work_buffer += N_window + 2;
   float *norm_secondary_squared      = work_buffer; work_buffer += N_window;
   float *cross_correlation_secondary = work_buffer; work_buffer += N_window + 2;
   float *cross_correlation           = work_buffer; work_buffer += N_data_reference;
   float *norm_squared                = work_buffer; work_buffer += N_data_reference;

   /*
   ** Compute the norm squared of the reference
   */
   float ref_norm_primary_squared   = freq_norm_squared_f (reference_x, N_window);
   float ref_norm_secondary_squared = freq_norm_squared_f (reference_y, N_window);

   // norm_primary_squared[i] = primary_acc[i] \dot primary_acc[i]
   norm_squared_f (primary_acceleration,
                   norm_primary_squared,
                   N_window_ref,
                   N_window);

   norm_squared_f (secondary_acceleration,
                   norm_secondary_squared,
                   N_window_ref,
                   N_window);

   for (k = 0; k < N_data_reference; k++)
   {
      norm_squared[k] = norm_primary_squared[k] + norm_secondary_squared[k];
   }

   float ref_norm_squared = ref_norm_primary_squared + ref_norm_secondary_squared;

   for (k = 0; k < N_data_reference; k++)
   {
      norm_squared[k] *= ref_norm_squared;
   }

   phase_correlation (reference_x,
                      primary_acceleration,
                      cross_correlation_primary,
                      work_buffer,
                      N_window);

   phase_correlation (reference_y,
                      secondary_acceleration,
                      cross_correlation_secondary,
                      work_buffer,
                      N_window);

   for (k = 0; k < N_data_reference; k++)
   {
      cross_correlation[k] = cross_correlation_primary[k] +
                             cross_correlation_secondary[k];
   }

   for (k = 0; k < N_data_reference; k++)
   {
      cross_correlation[k] *= cross_correlation[k];
   }

   for (k = 0; k < N_data_reference; k++)
   {
      cross_correlation[k] /= norm_squared[k];
   }

   int index;
   float max = cross_correlation[0];
   for (index = 1; index < N_data_reference; index++)
   {
      if (cross_correlation[index] > max)
      {
         max = cross_correlation[index];
      }
   }

   float correlation = sqrt( max );

   return correlation;
}
