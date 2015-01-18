#include <iostream>
#include <stdlib.h>
#include <string>
#include "fileio.h"
#include "preproc.h"
#include "matchedfilter.h"
#include "match_filt_training.h"
#include "compendium.h"
#include "gettime.h"

#define TIME_INC 0.5

extern "C" {
#include "fft.h"
}

int main(int argc, char *argv[]) {

   float power;
   float start_time  = 0.0;             // seconds from start
   float time_window = 4.0;             // seconds to analyze a signal
   float samp_freq   = 128.0;           // Hz
   float dt          = 1.0 / samp_freq; // seconds
   int   N_window    = (int) (samp_freq * time_window); // Number of data points of the signal
   float *ax = new float[N_window+2];   // Workspace for the signal in x
   float *ay = new float[N_window+2];   // Workspace for the signal in y
   float *az = new float[N_window+2];   // Workspace for the signal in z
   float *data_ax, *data_ay, *data_az;
   float *work_buffer = new float[N_window+2]; // The additional 2 is needed for nyquist (Complex)
   float proc_time;

   float ref_time = 1.5;    // reference time for training
   int   N_ref_time = (int)(ref_time * samp_freq);
   int   sens_training = 2; // sensor used for training
   int itt = 0;
   std::string tmp = argv[5];
   int N_references = atoi(tmp.c_str());

   activity act;

#ifdef pc
   const std::string training = "training";
   const std::string data     = "data";

   std::string mode        = argv[1];
   std::string data_path   = argv[3];
   std::string corr_path   = argv[4];
   std::string ref_path    = argv[6];
   std::string activity_ID = argv[2];

   /* Setup Kinetisense data */
   fio::kinIO KIN( data_path.c_str() );

   if (mode == training) {

      /* Setup training data */
      matchedfilter MF (N_window, atoi(activity_ID.c_str()));

      /* Train on the data provided */
      match_filt_training (&MF, &KIN, samp_freq, dt, time_window,
                           N_window, ref_time, N_ref_time, sens_training);

      /* Write the data to file */
      MF.write(ref_path);

   } else if (mode == data ) {

      matchedfilter *MF;

      mf_list MF_activities;

      for (int i_ref=0; i_ref<N_references; i_ref++) {
         ref_path = argv[i_ref+6];
         MF_activities.append ( new matchedfilter (ref_path.c_str(), N_window) );
      }

      for (itt=0; KIN.valid_start_end (start_time, time_window); itt++)
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

         preproc(
             ax,            /* Acceleration data in x               */
             ay,            /* Acceleration data in y               */
             az,            /* Acceleration data in z               */
             &power,        /* Resulting power of the signal        */
             dt,            /* Delta time comstant                  */
             time_window,   /* Time window of the data              */
             samp_freq,     /* Sampling frequency of the data       */
             N_window);     /* Number of sample points              */

/*
 * MATCHED FILTER
 */

         // Loop through the activities
         for (int k=0; k<MF_activities.get_N(); k++) {
            MF = MF_activities.get_MF();

            gettime();
            MF->run (ax, ay, dt, samp_freq, N_window, work_buffer);
            proc_time = gettime();

            if (itt == 0) MF->write_corr(corr_path, true);
            else          MF->write_corr(corr_path, false);

            MF_activities.goto_next();
         }
         MF_activities.goto_first();

//   neuralnetwork ( ... );

/*
 * ENERGY EXPENDITURE
 */

         if (MF->get_corr_ax() > 0.95 && MF->get_corr_ay() > 0.95) {
            act = WALKING_LVL_MOD_FIRM;
         }

         start_time += TIME_INC;
      }
   }
#endif

   delete ax;
   delete ay;
   delete az;
   delete work_buffer;

   return 0;
}
