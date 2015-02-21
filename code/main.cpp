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

#define TIME_INC 0.5

extern "C" {
#include "fft.h"
}

#ifdef pc
int main(int argc, char *argv[]) {

   std::string    input_file = argv[1];
   std::string    refs_file  = argv[2];
   int            act;
   fio::inputFile InFile(input_file);
   fio::readRefs  InRefs(refs_file);

   std::string tag         = InFile.get_parameter_s("tag"        ); // tag name for this run
   float time_window       = InFile.get_parameter_f("time_window"); // seconds to analyze a signal
   float freq_range        = InFile.get_parameter_f("freq_range" ); // Hz
   float cutoff_freq       = InFile.get_parameter_f("cutoff_freq"); // Hz
   float samp_freq         = InFile.get_parameter_f("samp_freq"  ); // Hz
   float ref_time          = InFile.get_parameter_f("ref_time"   ); // reference time for training
   float threshold         = InFile.get_parameter_f("threshold"  );
   std::string data_path   = InFile.get_parameter_s("data_path"  );
   std::string ref_path;
   float age    = 30.0;  // yrs
   float weight = 70.0;  // kg
   float height = 180.0; // cm
   int   sex    = MALE;
   float dt              = 1.0 / samp_freq; // seconds
   float start_time      = 0.0;             // seconds from start
   int   N_window        = (int) (samp_freq * time_window); // Number of data points of the signal
   float *ax    = new float[N_window+2];   // Workspace for the signal in x
   float *ay    = new float[N_window+2];   // Workspace for the signal in y
   float *az    = new float[N_window+2];   // Workspace for the signal in z
   float *taper = new float[N_window+2];   // taper used for applying the lowpass filter
   bool  apply_taper   = true;
   int   N_ref_time    = (int)(ref_time * samp_freq);
   int   sens_training = 2; // sensor used for training
   float *work_buffer  = new float[N_window+2]; // The additional 2 is needed for nyquist (Complex)
   float power, energy;
   float *data_ax, *data_ay, *data_az;
   float proc_time;
   int   itt = 0, max_index;
   float corr;
   float tmp;

   if (cutoff_freq < 0) apply_taper = false;

   taper_f(taper,
           time_window,
           cutoff_freq,
           freq_range,
           samp_freq,
           dt,
           N_window);

   /* Setup Kinetisense data */
   fio::kinIO KIN( data_path.c_str() );

   matchedfilter *MF;
   mf_list MF_activities;

   for (int i_ref=1; i_ref<=InRefs.get_Nrefs(); i_ref++) {
      ref_path = InRefs.get_ref_path(i_ref);
      MF_activities.append ( new matchedfilter (ref_path.c_str(), N_window) );
   }

   float ave_preproc_time = 0.0f;
   bool  initial_write = true;

   for (itt=0; KIN.valid_start_end (start_time, time_window); itt++, start_time += TIME_INC)
   {

      data_ax = KIN.get_sens_ax (start_time, 2);
      data_ay = KIN.get_sens_ay (start_time, 2);
      data_az = KIN.get_sens_az (start_time, 2);

      for (int k=0; k<N_window+2; k++) {
         ax[k] = data_ax[k];
         ay[k] = data_ay[k];
         az[k] = data_az[k];
      }

/*
 * PRE-PROCESSING
 */

      gettime();
      preproc(
          ax,            /* Acceleration data in x               */
          ay,            /* Acceleration data in y               */
          az,            /* Acceleration data in z               */
         &power,         /* Resulting power of the signal        */
          dt,            /* Delta time comstant                  */
          time_window,   /* Time window of the data              */
          samp_freq,     /* Sampling frequency of the data       */
          N_window);     /* Number of sample points              */
      proc_time = gettime();
      ave_preproc_time += proc_time;

/*
 * MATCHED FILTER
 */

      // run the matched filter through the activities
      corr = -1.1f; // -1 is the lowest obtainable minimum
      max_index = 0;
      for (int k=0; k<MF_activities.get_N(); k++, MF_activities.goto_next()) {

         MF = MF_activities.get_MF();

         gettime();
         MF->run (ax, ay, dt, samp_freq, N_window, taper, apply_taper, work_buffer);
         proc_time = gettime();

         MF->write_corr ("output/correlations", tag);

         // find which activity has the highest correlation
         tmp = 0.5f * (MF->get_corr_ax() + MF->get_corr_ay());
         if ( tmp > corr ) {
            corr = tmp;
            max_index = k;
         }
      }
      MF_activities.goto_first();

/*
 * ENERGY EXPENDITURE
 */

      for (int k=0; k<max_index; k++, MF_activities.goto_next()) {}

      MF = MF_activities.get_MF();
      corr = 0.5f * (MF->get_corr_ax() + MF->get_corr_ay());

      if (corr >= threshold) {
         // good match
         act = MF->get_ID();
      } else {
         // no good match
         act = NONE;
      }

      energy = energy_expenditure (weight,
                                   height,
                                   age,
                                   sex,
                                   act,
                                   power,
                                   time_window);

      fio::write_val (power,  "output/power"    + tag, initial_write);
      fio::write_val (act,    "output/activity" + tag, initial_write);
      fio::write_val (energy, "output/energy"   + tag, initial_write);

      initial_write = false;
      MF_activities.goto_first();
   }

   ave_preproc_time /= (float) itt;
   std::cout << "average pre-processing time = " << ave_preproc_time << std::endl;

   delete[] ax;
   delete[] ay;
   delete[] az;
   delete[] work_buffer;
   delete[] taper;

   return 0;
}
#endif
