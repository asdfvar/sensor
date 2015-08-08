/*
 * start_time    - seconds from start
 * N_window      - Number of data points of the signal
 * sens_training - sensor used for training
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include "fileio.h"
#include "preproc.h"
#include "matchedfilter.h"
#include "match_filt_training.h"
#include "energy_expenditure.h"
#include "compendium.h"
#include "memory_management.h"
#include "gettime.h"
#include "taper.h"
#include "filter.h"
#include "run_mf.h"
#include "define_parameters.h"

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
   float start_time      = 0.0f;
   int   N_window        = PARAMETERS.get_N_window();
   float *ax             = new float[N_window+2];
   float *ay             = new float[N_window+2];
   float *az             = new float[N_window+2];
   float *primary        = new float[N_window+2];
   float *secondary      = new float[N_window+2];
   int   sens_training = 2;
   float power, energy_rate;
   int   itt = 0, max_index;
   float corr;
   int   act;
   float tmp;
   float total_energy = 0.0f;
   matchedfilter *MF;
   MEMORY mem_buffer(6 * (N_window + 2));

   /* Setup Kinetisense data */

   fio::kinIO KIN( data_path.c_str() );

   /* Setup the matched filters */

   mf_list MF_activities;
   std::string ref_path;

   for (int i_ref=1; i_ref<=InRefs.get_Nrefs(); i_ref++) {

      ref_path = InRefs.get_ref_path(i_ref);
      MF = new matchedfilter (ref_path.c_str(), N_window);

      MF->filter (
          NUM_TENT_FILT_POINTS,
          mem_buffer);

      MF->apply_fft(N_window);
      MF_activities.append ( MF );

   }

   bool  initial_write    = true;

   TIME preproc_time    ( -1 );
   TIME match_filt_time ( -1 );

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

      preproc_time.start();

      preproc(
          ax,            /* Acceleration data in x               */
          ay,            /* Acceleration data in y               */
          az,            /* Acceleration data in z               */
          &power,        /* Resulting power of the signal        */
          &PARAMETERS,   /* Sampling frequency of the data       */
          N_window);     /* Number of sample points              */

      util::filter (
          ax,
          NUM_TENT_FILT_POINTS,
          N_window,
          mem_buffer);

      util::filter (
          ay,
          NUM_TENT_FILT_POINTS,
          N_window,
          mem_buffer);

      preproc_time.end();

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

         match_filt_time.start();

         run_mf (MF,
                 primary,
                 secondary,
                 PARAMETERS.get_dt(),
                 PARAMETERS.get_samp_freq(),
                 N_window,
                 mem_buffer);

         match_filt_time.end();

         MF->write_corr ("output/correlations" + PARAMETERS.get_tag(),
                         initial_write);

         // find which activity has the highest correlation
         if ( MF->get_correlation() > corr )
         {
            corr = MF->get_correlation();
            max_index = k;
         }
      }
      MF_activities.goto_first();

      /*
       * ENERGY EXPENDITURE
       */

      for (int k = 0; k < max_index; k++)
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

      energy_rate = energy_expenditure (
                                   PARAMETERS.get_weight(),
                                   PARAMETERS.get_height(),
                                   PARAMETERS.get_age(),
                                   PARAMETERS.get_sex(),
                                   act,
                                   power,
                                   PARAMETERS.get_time_window());

      total_energy += energy_rate * TIME_INC;

      fio::write_val (power,
                      "output/power"    + PARAMETERS.get_tag(),
                      initial_write);

      fio::write_val (act,
                      "output/activity" + PARAMETERS.get_tag(),
                      initial_write);

      fio::write_val (total_energy,
                      "output/energy"   + PARAMETERS.get_tag(),
                      initial_write);

      initial_write = false;
      MF_activities.goto_first();

   }

   std::cout << "average pre-processing time = " << preproc_time.average() << std::endl;
   std::cout << "average matched-filter time = " << match_filt_time.average() << std::endl;
   std::cout << "Total energy expenditure = " << total_energy << " kCals" << std::endl;

   mem_buffer.clear_memory();

   delete[] ax;
   delete[] ay;
   delete[] az;
   delete[] primary;
   delete[] secondary;

   return 0;
}
#endif
