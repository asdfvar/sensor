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

   std::string     input_file = argv[1];
   fio::parameters PARAMETERS (input_file);

   std::cout << "====================================" << std::endl;
   std::cout << "Training Matched Filter on " << PARAMETERS.get_activity_ID() << std::endl;
   std::cout << "====================================" << std::endl;

   PARAMETERS.print();

   float time_window       = PARAMETERS.get_time_window();
   float freq_range        = PARAMETERS.get_freq_range();
   float cutoff_freq       = PARAMETERS.get_cutoff_freq();
   float samp_freq         = PARAMETERS.get_samp_freq();
   float ref_time          = PARAMETERS.get_time_window_ref();
   std::string data_path   = PARAMETERS.get_data_path();
   std::string ref_path    = PARAMETERS.get_ref_path();
   std::string activity_ID = PARAMETERS.get_activity_ID();
   float dt                = PARAMETERS.get_dt();
   int   N_window          = PARAMETERS.get_N_window();
   float *taper = new float[N_window+2];   // taper used for applying the lowpass filter
   int   sens_num = 2; // sensor used for training

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
   match_filt_training (&MF,
                        &KIN,
                         taper,
                        &PARAMETERS);

   /* Write the data to file */
   MF.write(ref_path);

   delete[] taper;

   return 0;
}
#endif
