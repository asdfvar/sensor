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

   /* Setup Kinetisense data */
   fio::kinIO KIN( data_path.c_str() );

   /* Setup training data */
   matchedfilter MF (N_window, atoi(activity_ID.c_str()));

   /* Train on the data provided */
   match_filt_training (&MF, &KIN, taper, apply_taper, samp_freq, dt, time_window,
                        N_window, ref_time, N_ref_time, sens_training);

   /* Write the data to file */
   MF.write(ref_path);

#endif

   delete[] ax;
   delete[] ay;
   delete[] az;
   delete[] work_buffer;
   delete[] taper;

   return 0;
}
