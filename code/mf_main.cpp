#include <iostream>
#include <stdlib.h>
#include <string>
#include "fileio.h"
#include "preproc.h"
#include "matchedfilter.h"
#include "match_filt_training.h"
#include "energy_expenditure.h"
#include "compendium.h"
#include "gettime.h"
#include "taper.h"
#include "filter.h"
#include "run_mf.h"

#define TIME_INC 0.5

extern "C" {
#include "fft.h"
}

#ifdef pc
int main(int argc, char *argv[]) {

   std::cout << "======================" << std::endl;
   std::cout << "Running Matched Filter" << std::endl;
   std::cout << "======================" << std::endl;

   std::string    input_file = argv[1];
   std::string    refs_file  = argv[2];
   fio::readRefs  InRefs(refs_file);
   fio::parameters PARAMETERS (input_file);

   PARAMETERS.print();

   std::string data_path   = PARAMETERS.get_data_path();
   float start_time      = 0.0f;             // seconds from start
   int   N_window        = PARAMETERS.get_N_window(); // Number of data points of the signal
   float *ax             = new float[N_window+2];   // Workspace for the signal in x
   float *ay             = new float[N_window+2];   // Workspace for the signal in y
   float *az             = new float[N_window+2];   // Workspace for the signal in z
   float *primary        = new float[N_window+2];
   float *secondary      = new float[N_window+2];
#ifdef TAPER
   float *taper = new float[N_window+2];   // taper used for applying the lowpass filter
#endif
   int   sens_training = 2; // sensor used for training
   float *buf  = new float[N_window+2]; // The additional 2 is needed for nyquist (Complex)
   float power, energy;
   int   itt = 0, max_index;
   float corr;
   int   act;
   float tmp;
   matchedfilter *MF;

#ifdef TAPER
   taper_f(taper,
           PARAMETERS.get_time_window(),
           PARAMETERS.get_cutoff_freq(),
           PARAMETERS.get_freq_range(),
           PARAMETERS.get_samp_freq(),
           PARAMETERS.get_dt(),
           N_window);
#endif

   /* Setup Kinetisense data */

   fio::kinIO KIN( data_path.c_str() );

   /* Setup the matched filters */

   mf_list MF_activities;
   std::string ref_path;

   for (int i_ref=1; i_ref<=InRefs.get_Nrefs(); i_ref++) {

      ref_path = InRefs.get_ref_path(i_ref);
      MF = new matchedfilter (ref_path.c_str(), N_window);

      if (PARAMETERS.Do_taper()) {
           MF->apply_taper (buf,
                            PARAMETERS.get_cutoff_freq(),
                            PARAMETERS.get_freq_range());
      }

      MF->apply_fft(N_window);
      MF_activities.append ( MF );

   }

   float proc_time;
   float ave_preproc_time = 0.0f;
   float ave_mf_time      = 0.0f;
   bool  initial_write    = true;

   /* Iterate through the data */

   for (itt=0;
        KIN.valid_start_end (start_time, PARAMETERS.get_time_window());
        itt++, start_time += TIME_INC)
   {

      KIN.load_sens_ax (ax, start_time, 2, N_window);
      KIN.load_sens_ay (ay, start_time, 2, N_window);
      KIN.load_sens_az (az, start_time, 2, N_window);

      /*
       * PRE-PROCESSING
       */

      gettime();
      preproc(
          ax,            /* Acceleration data in x               */
          ay,            /* Acceleration data in y               */
          az,            /* Acceleration data in z               */
          &power,        /* Resulting power of the signal        */
          &PARAMETERS,   /* Sampling frequency of the data       */
          N_window);     /* Number of sample points              */

      if (PARAMETERS.Do_taper())
      {

#ifdef TAPER
         apply_taper (ax, taper, N_window);
         apply_taper (ay, taper, N_window);
#else
         apply_filter (ax, 1, N_window);
         apply_filter (ay, 1, N_window);
#endif

      }

      proc_time = gettime();
      ave_preproc_time += proc_time;

      /*
       * MATCHED FILTER
       */

      // run the matched filter through the activities
      corr = -1.1f; // -1 is the lowest obtainable minimum
      max_index = 0;
      for (int k=0; k<MF_activities.get_N(); k++, MF_activities.goto_next())
      {

         MF = MF_activities.get_MF();

         for (int p = 0; p < N_window+2; p++) primary[p]   = ax[p];
         for (int p = 0; p < N_window+2; p++) secondary[p] = ay[p];

         gettime();

         run_mf (MF,
                 primary,
                 secondary,
                 PARAMETERS.get_dt(),
                 PARAMETERS.get_samp_freq(),
                 N_window,
                 buf);

         proc_time = gettime();
         ave_mf_time += proc_time;

         MF->write_corr ("output/correlations" + PARAMETERS.get_tag(),
                         initial_write);

         // find which activity has the highest correlation
         if ( MF->get_correlation() > corr )
         {
            corr = tmp;
            max_index = k;
         }
      }

      /*
       * ENERGY EXPENDITURE
       */

      for (int k=0; k<max_index; k++)
      {
         MF_activities.goto_next();
      }

      MF = MF_activities.get_MF();

      corr = MF->get_correlation();

      if (corr >= PARAMETERS.get_threshold()) {
         // good match
         act = MF->get_ID();
      } else {
         // no good match
         act = NONE;
      }

      energy = energy_expenditure (PARAMETERS.get_weight(),
                                   PARAMETERS.get_height(),
                                   PARAMETERS.get_age(),
                                   PARAMETERS.get_sex(),
                                   act,
                                   power,
                                   PARAMETERS.get_time_window());

      fio::write_val (power,
                      "output/power"    + PARAMETERS.get_tag(),
                      initial_write);

      fio::write_val (act,
                      "output/activity" + PARAMETERS.get_tag(),
                      initial_write);

      fio::write_val (energy,
                      "output/energy"   + PARAMETERS.get_tag(),
                      initial_write);

      initial_write = false;
      MF_activities.goto_first();

   }

   ave_preproc_time /= (float) itt;
   std::cout << "average pre-processing time = " << ave_preproc_time << std::endl;
   ave_mf_time /= (float) itt;
   std::cout << "average matched-filter time = " << ave_mf_time << std::endl;

   delete[] ax;
   delete[] ay;
   delete[] az;
   delete[] buf;
   delete[] primary;
   delete[] secondary;
#ifdef TAPER
   delete[] taper;
#endif

   return 0;
}
#endif
