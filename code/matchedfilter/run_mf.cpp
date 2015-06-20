#include "matchedfilter.h"
#include "phase_correlation.h"
#include <cmath>

void run_mf (matchedfilter *MF,
             float         *primary_acceleration,
             float         *secondary_acceleration,
             float          dt,
             float          samp_freq,
             int            N_data,
             float         *buf)
{

   // TODO: Make proper handle for this
   float norm_primary_squared[1024];
   float cross_correlation_primary[1024];
   float norm_secondary_squared[1024];
   float cross_correlation_secondary[1024];
   float cross_correlation[1024];
   float norm_squared[1024];

   int   N_window                   = MF->get_N_window();
   int   N_data_reference           = N_data - N_window + 1;
   float ref_norm_primary_squared   = MF->get_norm_ax() * MF->get_norm_ax();
   float ref_norm_secondary_squared = MF->get_norm_ay() * MF->get_norm_ay();

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
                     MF->get_norm_ax(),
                     buf,
                     dt,
                     samp_freq,
                     N_window,
                     N_data);

   phase::phase_correlation (MF->access_ay(),
                     secondary_acceleration,
                     cross_correlation_secondary,
                     MF->get_norm_ay(),
                     buf,
                     dt,
                     samp_freq,
                     N_window,
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

   for (int k = 0; k < N_data_reference; k++)
   {
      cross_correlation[k] /= norm_squared[k];
   }

   float max       = cross_correlation[0];
   int   max_index = 0;

   for (int index = 1; index < N_data_reference; index++)
   {
      if (cross_correlation[index] > max)
      {
         max = cross_correlation[index];
         max_index = index;
      }
   }

   float correlation = sqrtf( max );

   MF->set_correlation ( correlation );

   return;
}
