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

#ifdef pc
int main(int argc, char *argv[]) {

   std::string    input_file = argv[1];
   fio::inputFile InFile(input_file);

   float time_window       = InFile.get_parameter_f("time_window"); // seconds to analyze a signal
   float freq_range        = InFile.get_parameter_f("freq_range" ); // Hz
   float cutoff_freq       = InFile.get_parameter_f("cutoff_freq"); // Hz
   float samp_freq         = InFile.get_parameter_f("samp_freq"  ); // Hz
   float ref_time          = InFile.get_parameter_f("ref_time"   ); // reference time for training
   std::string data_path   = InFile.get_parameter_s("data_path"  );
   std::string ref_path    = InFile.get_parameter_s("ref_path"   ); // used for training
   std::string activity_ID = InFile.get_parameter_s("activity_ID"); // used for training
   float dt              = 1.0 / samp_freq; // seconds
   int   N_window        = (int) (samp_freq * time_window); // Number of data points of the signal
   float *taper = new float[N_window+2];   // taper used for applying the lowpass filter
   bool  Do_taper = true;
   int   N_ref_time = (int)(ref_time * samp_freq);
   int   sens_training = 2; // sensor used for training

   if (cutoff_freq < 0) Do_taper = false;

   taper_f(taper,
           time_window,
           cutoff_freq,
           freq_range,
           samp_freq,
           dt,
           N_window);

   /* Setup Kinetisense data */
   fio::kinIO KIN( data_path.c_str() );

   /* Setup training data */
   matchedfilter MF (N_window, atoi(activity_ID.c_str()));

   /* Train on the data provided */
   match_filt_training (&MF, &KIN, taper, Do_taper, cutoff_freq, freq_range,
                        samp_freq, dt, time_window, N_window, ref_time,
                        N_ref_time, sens_training);

   /* Write the data to file */
   MF.write(ref_path);

   delete[] taper;

   return 0;
}
#endif
