/*
 *     ( (ref_1 \dot sig_1)[i] + (ref_2 \dot sig_2)[i] ) /
 * sqrt( (ref_1 \dot ref_1 + ref_2 \dot ref_2) *
 *       (sig_1[i] \dot sig_1[i] + sig_2[i] \dot sig_2[i] ) )
 *
 * Note that sig_1,2[i] is a vector which means sig_1,2 is an array of vectors
 */
#include "matchedfilter.h"
#include "memory_management.h"
#include "phase_correlation.h"
#include <iostream>
#include <cmath>

/*
 * Function NAME: run_mf
 */
void run_mf (matchedfilter *MF,
             float         *primary_acceleration,
             float         *secondary_acceleration,
             float          dt,
             float          samp_freq,
             int            N_data,
             bool           debug,
             MEMORY         mem_buffer)
{

   int   N_window                   = MF->get_N_window();
   int   N_data_reference           = N_data - N_window + 1;
   float ref_norm_primary_squared   = MF->get_norm_ax() * MF->get_norm_ax();
   float ref_norm_secondary_squared = MF->get_norm_ay() * MF->get_norm_ay();

   float *norm_primary_squared        = mem_buffer.allocate_float( N_data           );
   float *cross_correlation_primary   = mem_buffer.allocate_float( N_data + 2       );
   float *norm_secondary_squared      = mem_buffer.allocate_float( N_data           );
   float *cross_correlation_secondary = mem_buffer.allocate_float( N_data + 2       );
   float *cross_correlation           = mem_buffer.allocate_float( N_data_reference );
   float *norm_squared                = mem_buffer.allocate_float( N_data_reference );

   // norm_primary_squared[i] = primary_acc[i] \dot primary_acc[i]
   phase::norm_squared (primary_acceleration,
                        norm_primary_squared,
                        N_window,
                        N_data);

   phase::norm_squared (secondary_acceleration,
                        norm_secondary_squared,
                        N_window,
                        N_data);

   for (int k = 0; k < N_data_reference; k++)
   {
      norm_squared[k] = norm_primary_squared[k] + norm_secondary_squared[k];
   }

   float ref_norm_squared = ref_norm_primary_squared + ref_norm_secondary_squared;

   for (int k = 0; k < N_data_reference; k++)
   {
      norm_squared[k] *= ref_norm_squared;
   }

   phase::phase_correlation (MF->access_ax(),
                             primary_acceleration,
                             cross_correlation_primary,
                             N_data);

   phase::phase_correlation (MF->access_ay(),
                             secondary_acceleration,
                             cross_correlation_secondary,
                             N_data);

   for (int k = 0; k < N_data_reference; k++)
   {
      cross_correlation[k] = cross_correlation_primary[k] +
                             cross_correlation_secondary[k];
   }

   for (int k = 0; k < N_data_reference; k++)
   {
      cross_correlation[k] *= cross_correlation[k];
   }

   bool unstable = false;
   for (int k = 0; k < N_data_reference; k++)
   {
      if (norm_squared[k] > 0.0001f) cross_correlation[k] /= norm_squared[k];
      else
      {
         cross_correlation[k] = 0.0f;
         unstable = true;
      }
   }
   if (unstable) std::cout << __FILE__ << ":Possible instability in normalization averted" << std::endl;

   float max       = cross_correlation[0];

   for (int index = 1; index < N_data_reference; index++)
   {
      if (cross_correlation[index] > max)
      {

         max = cross_correlation[index];

      }
   }

   float correlation = sqrtf( max );

   MF->set_correlation ( correlation );

   return;
}
