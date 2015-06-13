#include "matchedfilter.h"

void run_mf (matchedfilter *MF,
             float         *ax,
             float         *ay,
             float          dt,
             float          samp_freq,
             int            N_data,
             float         *buf)
{

   MF->set_corr_ax (
          phase_correlation (MF->access_ax(),
                     ax,
                     MF->get_norm_ax(),
                     buf,
                     dt,
                     samp_freq,
                     MF->get_N_window(),
                     N_data)
                   );
              
   MF->set_corr_ay (
          phase_correlation (MF->access_ay(),
                     ay,
                     MF->get_norm_ay(),
                     buf,
                     dt,
                     samp_freq,
                     MF->get_N_window(),
                     N_data)
                   );
              
   return;
}
