/*
 *     ( (ref_1 \dot sig_1)[i] + (ref_2 \dot sig_2)[i] ) /
 * sqrt( (ref_1 \dot ref_1 + ref_2 \dot ref_2) *
 *       (sig_1[i] \dot sig_1[i] + sig_2[i] \dot sig_2[i] ) )
 *
 * Note that sig_1,2[i] is a vector which means sig_1,2 is an array of vectors
 */
#include "phase_correlation.h"
#include <math.h>
#include <stdio.h>

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

   int   N_time_window              = (int)(time_window * samp_freq);
   int   N_time_window_ref          = (int)(ref_time_window * samp_freq);

   /*
   ** Resurve memory for local variables
   */
   float *norm_primary_squared        = work_buffer;
   float *cross_correlation_primary   = norm_primary_squared        + N_time_window;
   float *norm_secondary_squared      = cross_correlation_primary   + N_time_window + 2;
   float *cross_correlation_secondary = norm_secondary_squared      + N_time_window;
   float *cross_correlation           = cross_correlation_secondary + N_time_window + 2;
   float *norm_squared                = cross_correlation           + N_time_window;

   /*
   ** Compute the norm squared of the reference
   */
   float ref_norm_primary_squared   = 0.0f;
   float ref_norm_secondary_squared = 0.0f;
   for (k = 0; k < N_time_window_ref; k++)
   {
      ref_norm_primary_squared += reference_x[k] * reference_x[k];
      ref_norm_secondary_squared += reference_y[k] * reference_y[k];
   }

   // norm_primary_squared[i] = primary_acc[i] \dot primary_acc[i]
   norm_squared_f (primary_acceleration,
                   norm_primary_squared,
                   N_time_window_ref,
                   N_time_window);

   norm_squared_f (secondary_acceleration,
                   norm_secondary_squared,
                   N_time_window_ref,
                   N_time_window);

   for (k = 0; k < N_time_window_ref; k++)
   {
      norm_squared[k] = norm_primary_squared[k] + norm_secondary_squared[k];
   }

   float ref_norm_squared = ref_norm_primary_squared + ref_norm_secondary_squared;

   for (k = 0; k < N_time_window_ref; k++)
   {
      norm_squared[k] *= ref_norm_squared;
   }

   phase_correlation (reference_x,
                      primary_acceleration,
                      cross_correlation_primary,
                      N_time_window);

   phase_correlation (reference_y,
                      secondary_acceleration,
                      cross_correlation_secondary,
                      N_time_window);

   for (k = 0; k < N_time_window_ref; k++)
   {
      cross_correlation[k] = cross_correlation_primary[k] +
                             cross_correlation_secondary[k];
   }

   for (k = 0; k < N_time_window_ref; k++)
   {
      cross_correlation[k] *= cross_correlation[k];
   }

   for (k = 0; k < N_time_window_ref; k++)
   {
      cross_correlation[k] /= norm_squared[k];
   }

   int index;
   float max = cross_correlation[0];
   for (index = 1; index < N_time_window_ref; index++)
   {
      if (cross_correlation[index] > max)
      {
         max = cross_correlation[index];
      }
   }

   float correlation = sqrtf( max );

   return correlation;
}
