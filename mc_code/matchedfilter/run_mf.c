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
               float  dt,
               float  time_window,
               float  ref_time_window,
               float  samp_freq,
               float  norm_ref_ax,
               float  norm_ref_ay,
               float *work_buffer)
{

   int   N_time_window              = (int)(time_window * samp_freq);
   int   N_time_window_ref          = (int)(ref_time_window * samp_freq);
   float ref_norm_primary_squared   = norm_ref_ax * norm_ref_ax;
   float ref_norm_secondary_squared = norm_ref_ay * norm_ref_ay;

   /*
   ** Resurve memory for local variables
   */
   float *norm_primary_squared        = work_buffer;
   float *cross_correlation_primary   = norm_primary_squared        + N_time_window;
   float *norm_secondary_squared      = cross_correlation_primary   + N_time_window + 2;
   float *cross_correlation_secondary = norm_secondary_squared      + N_time_window;
   float *cross_correlation           = cross_correlation_secondary + N_time_window + 2;
   float *norm_squared                = cross_correlation           + N_time_window;

   // norm_primary_squared[i] = primary_acc[i] \dot primary_acc[i]
   norm_squared_f (primary_acceleration,
                 norm_primary_squared,
                 N_time_window,
                 N_time_window);

   norm_squared_f (secondary_acceleration,
                 norm_secondary_squared,
                 N_time_window,
                 N_time_window);

   for (int k = 0; k < N_time_window_ref; k++)
   {
      norm_squared[k] = norm_primary_squared[k] + norm_secondary_squared[k];
   }

   float ref_norm_squared = ref_norm_primary_squared + ref_norm_secondary_squared;

   for (int k = 0; k < N_time_window_ref; k++)
   {
      norm_squared[k] *= ref_norm_squared;
   }

   phase_correlation (MF->access_ax(),
                      primary_acceleration,
                      cross_correlation_primary,
                      N_time_window);



   phase_correlation (MF->access_ay(),
                      secondary_acceleration,
                      cross_correlation_secondary,
                      N_time_window);



   for (int k = 0; k < N_time_window_ref; k++)
   {
      cross_correlation[k] = cross_correlation_primary[k] +
                             cross_correlation_secondary[k];
   }

   for (int k = 0; k < N_time_window_ref; k++)
   {
      cross_correlation[k] *= cross_correlation[k];
   }

   for (int k = 0; k < N_time_window_ref; k++)
   {
      cross_correlation[k] /= norm_squared[k];
   }

   float max       = cross_correlation[0];


   for (int index = 1; index < N_time_window_ref; index++)
   {
      if (cross_correlation[index] > max)
      {

         max = cross_correlation[index];

      }
   }


   float correlation = sqrtf( max );

   return correlation;
}
