#include <iostream>
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
   int index = 0;

   activity act;

#ifdef pc
   const std::string training = "training";
   const std::string data       = "data";

   std::string data_path = argv[3];
   std::string corr_path = argv[4];
   std::string ref_path  = argv[5];
   std::string activity_ID = argv[2];

   /* Setup Kinetisense data */
   fio::kinIO KIN( data_path.c_str() );
   int size = KIN.get_total_time() / TIME_INC;

   float *corr_ax = new float[size];
   float *corr_ay = new float[size];

   if (argv[1] == training) {

      /* Setup training data */
      matchedfilter MF (N_window);

      /* Train on the data provided */
      match_filt_training (&MF, &KIN, activity_ID, samp_freq, dt, time_window,
                           N_window, ref_time, N_ref_time, sens_training);

      /* Write the data to file */
      MF.write(ref_path);

   } else if (argv[1] == data ) {

      matchedfilter *MF;

      mf_list MF_acts;
      MF_acts.insert ( new matchedfilter (ref_path.c_str(), activity_ID, N_window) );

      MF = MF_acts.get_MF();

      while (KIN.valid_start_end (start_time, time_window))
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

         gettime();
         MF->run (ax, ay, dt, samp_freq, N_window, work_buffer);
         proc_time = gettime();

         corr_ax[index] = MF->get_corr_ax();
         corr_ay[index] = MF->get_corr_ay();

//   neuralnetwork ( ... );

/*
 * ENERGY EXPENDITURE
 */

         if (MF->get_corr_ax() > 0.95 && MF->get_corr_ay() > 0.95) {
            act = WALKING_LVL_MOD_FIRM;
         }

         std::cout << "Energy expenditure = " << power << std::endl;

         start_time += TIME_INC;
         index++;
      }
   }
#endif

   fio::write_correlations(corr_path, corr_ax, corr_ay, index);

   delete ax;
   delete ay;
   delete az;
   delete corr_ax;
   delete corr_ay;
   delete work_buffer;

   return 0;
}
