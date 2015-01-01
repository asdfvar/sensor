#include <iostream>
#include "fileio.h"
#include "ref.h"
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

   fio KIN( kin_data_path.c_str() );
#endif

/*
 * PROCESS DATA
 */

   float power;
   float start_time  = 0.0;             // seconds
   float time_window = 4.0;             // seconds
   float samp_freq   = 128.0;           // Hz
   float dt          = 1.0 / samp_freq; // seconds
   int   N_window    = (int) (samp_freq * time_window);
   float *ax = new float[N_window+2];
   float *ay = new float[N_window+2];
   float *az = new float[N_window+2];
   float *data_ax, *data_ay, *data_az;
   float corr_ax, corr_ay;
   float *work_buffer = new float[N_window+2];

#ifdef pc
   int   ref_N;
   float ref_freq;
   float ref_time;

   /* Get reference data */

   ref::read_reference_headers (
                        ref_walking.c_str(),
                        &ref_N,
                        &ref_freq,
                        &ref_time);

   float *ref_data_primary   = new float[N_window+2];
   for (int k=0; k<N_window+2; k++) ref_data_primary[k] = 0.0;

   float *ref_data_secondary = new float[N_window+2];
   for (int k=0; k<N_window+2; k++) ref_data_secondary[k] = 0.0;

   ref::read_reference (ref_walking.c_str(),
                        ref_data_primary,
                        ref_data_secondary,
                        ref_N);

   matchedfilter MF1;

   MF1.load_ref (ref_data_primary, ref_data_secondary,
                 dt, samp_freq, ref_time, N_window, ref_N, work_buffer);
#endif

/*
 * MAIN LOOP
 */

#ifdef pc
   while (KIN.valid_start_end (start_time, time_window))
   {
#endif

/*
 * PRE-PROCESSING
 */

#ifdef pc
      data_ax = KIN.get_sens2_ax (start_time);
      data_ay = KIN.get_sens2_ay (start_time);
      data_az = KIN.get_sens2_az (start_time);

      for (int k=0; k<512; k++) {
         ax[k] = data_ax[k];
         ay[k] = data_ay[k];
         az[k] = data_az[k];
      }

#endif

      preproc(
          ax,            /* Acceleration data in x               */
          ay,            /* Acceleration data in y               */
          az,            /* Acceleration data in z               */
          &power,        /* Resulting power of the signal        */
          dt,            /* Delta time comstant                  */
          time_window,   /* Time window of the data              */
          samp_freq,     /* Sampling frequency of the data       */
          N_window);     /* Number of sample points              */

      std::cout << "Signal power = " << power << std::endl;

      MF1.run (ax, ay, dt, samp_freq, N_window, &corr_ax, &corr_ay, work_buffer);

/*
 * MATCHED FILTER
 */

//   neuralnetwork ( ... );

#ifdef pc
      start_time += 0.5;
   }
#endif

   return 0;
}
