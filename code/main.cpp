#include <iostream>
#include <stdlib.h>
#include <string>
#include "fileio.h"
#include "preproc.h"
#include "matchedfilter.h"
#include "match_filt_training.h"
#include "compendium.h"
#include "gettime.h"
#include "taper.h"

#define TIME_INC 0.5

extern "C" {
#include "fft.h"
}

int main(int argc, char *argv[]) {

#ifdef pc
   std::string mode = argv[1];
   std::string input_file = argv[2];
   std::string refs_file  = argv[3];
   activity act;
   fio::inputFile InFile(input_file);
   fio::readRefs InRefs(refs_file);

   std::string tag         = InFile.get_parameter_s("tag"        ); // tag name for this run
   float time_window       = InFile.get_parameter_f("time_window"); // seconds to analyze a signal
   float freq_range        = InFile.get_parameter_f("freq_range" ); // Hz
   float cutoff_freq       = InFile.get_parameter_f("cutoff_freq"); // Hz
   float samp_freq         = InFile.get_parameter_f("samp_freq"  ); // Hz
   float ref_time          = InFile.get_parameter_f("ref_time"   ); // reference time for training
   std::string data_path   = InFile.get_parameter_s("data_path"  );
   std::string ref_path    = InFile.get_parameter_s("ref_path"   ); // used for training
   std::string activity_ID = InFile.get_parameter_s("activity_ID"); // used for training
   float dt              = 1.0 / samp_freq; // seconds
   float start_time      = 0.0;             // seconds from start
   int   N_window        = (int) (samp_freq * time_window); // Number of data points of the signal
   float *ax    = new float[N_window+2];   // Workspace for the signal in x
   float *ay    = new float[N_window+2];   // Workspace for the signal in y
   float *az    = new float[N_window+2];   // Workspace for the signal in z
   float *taper = new float[N_window+2];   // taper used for applying the lowpass filter
   bool  apply_taper = true;
   int   N_ref_time = (int)(ref_time * samp_freq);
   int   sens_training = 2; // sensor used for training
   float *work_buffer = new float[N_window+2]; // The additional 2 is needed for nyquist (Complex)
   float power;
   float *data_ax, *data_ay, *data_az;
   float proc_time;
   int   itt = 0;


   taper_f(taper,
           time_window,
           cutoff_freq,
           freq_range,
           samp_freq,
           dt,
           N_window);

   const std::string training = "training";
   const std::string data     = "data";

   /* Setup Kinetisense data */
   fio::kinIO KIN( data_path.c_str() );

   /*****************
    * Training Mode *
    *****************/

   if (mode == training) {

      /* Setup training data */
      matchedfilter MF (N_window, atoi(activity_ID.c_str()));

      /* Train on the data provided */
      match_filt_training (&MF, &KIN, taper, apply_taper, samp_freq, dt, time_window,
                           N_window, ref_time, N_ref_time, sens_training);

      /* Write the data to file */
      MF.write(ref_path);

   /************************
    * Data processing Mode *
    ************************/

   } else if (mode == data ) {

      matchedfilter *MF;
      mf_list MF_activities;

      for (int i_ref=1; i_ref<=InRefs.get_Nrefs(); i_ref++) {
         ref_path = InRefs.get_ref_path(i_ref);
         MF_activities.append ( new matchedfilter (ref_path.c_str(), N_window) );
      }

      float ave_preproc_time = 0.0f;
      bool initial_write = true;

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
             &power,        /* Resulting power of the signal        */
             dt,            /* Delta time comstant                  */
             time_window,   /* Time window of the data              */
             samp_freq,     /* Sampling frequency of the data       */
             N_window);     /* Number of sample points              */
         proc_time = gettime();
         ave_preproc_time += proc_time;

/*
 * MATCHED FILTER
 */

         // Loop through the activities
         for (int k=0; k<MF_activities.get_N(); k++, MF_activities.goto_next()) {
            MF = MF_activities.get_MF();

            gettime();
            MF->run (ax, ay, dt, samp_freq, N_window, taper, apply_taper, work_buffer);
            proc_time = gettime();

            MF->write_corr ("output/correlations", tag);
         }
         MF_activities.goto_first();

//   neuralnetwork ( ... );

/*
 * ENERGY EXPENDITURE
 */

         if (MF->get_corr_ax() > 0.95 && MF->get_corr_ay() > 0.95) {
            act = WALKING_LVL_MOD_FIRM;
         }

         fio::write_val (power, "output/power"    + tag,    initial_write);
         fio::write_val (act,   "output/activity" + tag, initial_write);
         fio::write_val (power, "output/energy"   + tag,   initial_write);
         initial_write = false;

      }

      ave_preproc_time /= (float) itt;
      std::cout << "average pre-processing time = " << ave_preproc_time << std::endl;
   }
#endif

   delete ax;
   delete ay;
   delete az;
   delete work_buffer;

   return 0;
}
