#include <iostream>
#include "fileio.h"
#include "preproc.h"
#include "matchedfilter.h"

extern "C" {
#include "fft.h"
}

int main() {

#ifdef pc
   const std::string kin_data_path = "../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking   = "../data/craig_walking_tredmil_reference_signals_1_5s.csv";

   /* Get kinetisense data */

   fio::kinIO KIN( kin_data_path.c_str() );
#endif

/*
 * PROCESS DATA
 */

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

#ifdef pc
   /* Get reference data */

   matchedfilter MF1( ref_walking.c_str(), N_window );

#endif

/*
 * MAIN LOOP
 */

#ifdef pc
   while (KIN.valid_start_end (start_time, time_window))
   {
#endif

#ifdef pc
      data_ax = KIN.get_sens2_ax (start_time);
      data_ay = KIN.get_sens2_ay (start_time);
      data_az = KIN.get_sens2_az (start_time);

      for (int k=0; k<N_window+2; k++) {
         ax[k] = data_ax[k];
         ay[k] = data_ay[k];
         az[k] = data_az[k];
      }
#endif

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

      MF1.run (ax, ay, dt, samp_freq, N_window, work_buffer);

      std::cout << "Signal power = " << power;
      std::cout << " Primary correlation = " << MF1.get_corr_ax();
      std::cout << " Secondary correlation = " << MF1.get_corr_ay() << std::endl;

//   neuralnetwork ( ... );

#ifdef pc
      start_time += 0.5;
   }
#endif

   return 0;
}
