#include <iostream>
#include "fileio.h"
#include "ref.h"
#include "preproc.h"
#include "matchedfilter.h"

extern "C" {
#include "fft.h"
}

int main() {

   const std::string kin_data_path = "../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking   = "../data/craig_walking_tredmil_reference_signals.csv";

   /* Get kinetisense data */

   fio KIN( kin_data_path.c_str() );

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

   float *ref_data_primary   = new float[ref_N];
   float *ref_data_secondary = new float[ref_N];

   ref::read_reference (ref_walking.c_str(),
                        ref_data_primary,
                        ref_data_secondary,
                        ref_N);
#endif

/*
 * PROCESS DATA
 */

   float power;
   float start_time  = 0.0; // seconds
   float time_window = 4.0; // seconds
   float samp_freq   = 128.0; // Hz
   float dt          = 1.0 / samp_freq; // seconds
   int N_window      = (int) (samp_freq * time_window);

   float *ax, *ay, *az;

#ifdef pc
   while (KIN.valid_start_end (start_time, time_window))
   {
#endif

/*
 * PRE-PROCESSING
 */

      ax = KIN.get_sens2_ax (start_time);
      ay = KIN.get_sens2_ay (start_time);
      az = KIN.get_sens2_az (start_time);

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


/*
 * MATCHED FILTER
 */

//   neuralnetwork ( ... );

#ifdef pc
      start_time += 0.5;
   }
#endif

   delete[] ref_data_primary;
   delete[] ref_data_secondary;

   return 0;
}
