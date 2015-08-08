/*
 * Function NAME: match_filt_training
 *
 * time_window     - Signal window time (seconds)
 * N_window        - Signal window points (elements)
 * time_window_ref - Reference length (seconds)
 * N_window_ref    - Reference length (# elements)
 *
 */

#include "matchedfilter.h"
#include "run_mf.h"
#include "fileio.h"
#include "preproc.h"
#include "gettime.h"
#include "taper.h"
#include "filter.h"
#include "memory_management.h"
#include "define_parameters.h"
#include <iostream>

void match_filt_training(
              matchedfilter *MF,
              fio::kinIO    *KIN,
              float         *taper,
              fio::parameters *PARAMETERS,
              int            sens_num)
{

 float samp_freq       = PARAMETERS->get_samp_freq();
 float dt              = PARAMETERS->get_dt();
 float time_window     = PARAMETERS->get_time_window();
 int   N_window        = PARAMETERS->get_N_window();
 float time_window_ref = PARAMETERS->get_time_window_ref();
 int   N_window_ref    = PARAMETERS->get_N_window_ref();
 int   count;
 
 MEMORY mem_buffer( 6 * (N_window + 2) );

 float time_inc = (KIN->get_total_time() - time_window) / BINS;

 float start_time_ref   = 0.0f;
 float best_start_time  = start_time_ref;
 float start_time_data  = 0.0f;

 float sum_corr         = 0.0f;
 float best_correlation = 0.0f;

 float *__restrict__ ax = new float[N_window+2];   // Workspace for the signal in x
 float *__restrict__ ay = new float[N_window+2];   // Workspace for the signal in y
 float *__restrict__ az = new float[N_window+2];   // Workspace for the signal in z

 float *__restrict__ buf = new float[N_window+2];

 float *__restrict__ primary;
 float *__restrict__ secondary;

 float prev_perc_done = 0.0f;
 float curr_perc_done = 0.0f;

 float power;

 TIME measure_time;

 std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
 std::cout.precision(6);

 gettime();

 measure_time.start();

 std::cout << "% done\tthis average correlation\t"
           << "best correlation\tbest time"<< std::endl;

 /*
  * Loop through candidate reference signals.
  */

 while (KIN->valid_start_end (start_time_ref, time_window))
 {

    /* load into reference */

    KIN->load_sens_ax (ax, start_time_ref, 2, N_window);
    KIN->load_sens_ay (ay, start_time_ref, 2, N_window);
    KIN->load_sens_az (az, start_time_ref, 2, N_window);

    preproc(
        ax,            /* Acceleration data in x               */
        ay,            /* Acceleration data in y               */
        az,            /* Acceleration data in z               */
        &power,        /* Resulting power of the signal        */
        PARAMETERS,    /* Sampling frequency of the data       */
        N_window);     /* Number of sample points              */

    primary   = ax;
    secondary = ay;

      util::filter (
         primary,
         NUM_TENT_FILT_POINTS,
         N_window,
         mem_buffer);

      util::filter (
         secondary,
         NUM_TENT_FILT_POINTS,
         N_window,
         mem_buffer);

    MF->load_ref (
        primary,
        secondary,
        dt,
        samp_freq,
        time_window_ref,
        N_window_ref,
        N_window);

    MF->apply_fft(N_window);

    /*
     * Loop through signal to test against the candidate reference
     */

    for (count           = 0,
         start_time_data = 0.0f,
         sum_corr        = 0.0f;
            KIN->valid_start_end (start_time_data, time_window);
               count++)
    {

       KIN->load_sens_ax (ax, start_time_data, 2, N_window);
       KIN->load_sens_ay (ay, start_time_data, 2, N_window);
       KIN->load_sens_az (az, start_time_data, 2, N_window);

       preproc(
           ax,            /* Acceleration data in x               */
           ay,            /* Acceleration data in y               */
           az,            /* Acceleration data in z               */
           &power,        /* Resulting power of the signal        */
           PARAMETERS,    /* Sampling frequency of the data       */
           N_window);     /* Number of sample points              */

       util::filter (
           ax,
           NUM_TENT_FILT_POINTS,
           N_window,
           mem_buffer);

       util::filter (
           ay,
           NUM_TENT_FILT_POINTS,
           N_window,
           mem_buffer);

       primary   = ax;
       secondary = ay;

       run_mf (MF,
               primary,
               secondary,
               dt,
               samp_freq,
               N_window,
               mem_buffer);

       sum_corr += MF->get_correlation();

       start_time_data += time_inc;

    }

    float ave_correlation = sum_corr / (float)count;

    if (ave_correlation > best_correlation) {
       best_correlation = ave_correlation;
       best_start_time   = start_time_ref;
    }

    curr_perc_done = start_time_ref/(KIN->get_total_time() - time_window)*100.0f;
    if (curr_perc_done - prev_perc_done >= 10.0f)
    {

       std::cout << curr_perc_done   << "\t"     <<
                    ave_correlation  << "\t\t" <<
                    best_correlation << "\t\t"   <<
                    best_start_time  << "\t"     <<
                    std::endl;

       prev_perc_done = curr_perc_done;
    }

    start_time_ref += time_inc;
 }

 /* load the best section into the reference */

 std::cout << "Reference choosen from start time: " << best_start_time << " From "
           << KIN->get_total_time() << " Total seconds of data" << std::endl;

 KIN->load_sens_ax (ax, best_start_time, 2, N_window);
 KIN->load_sens_ay (ay, best_start_time, 2, N_window);
 KIN->load_sens_az (az, best_start_time, 2, N_window);

 /*
 ** Pre-process the raw acceleration data
 */

 preproc(
     ax,            /* Acceleration data in x               */
     ay,            /* Acceleration data in y               */
     az,            /* Acceleration data in z               */
     &power,        /* Resulting power of the signal        */
     PARAMETERS,    /* Sampling frequency of the data       */
     N_window);     /* Number of sample points              */

 /*
 ** Re-alias the primary and secondary acceleration data.
 ** Then, load this data into memory to be written out.
 */

 primary   = ax;
 secondary = ay;

 MF->load_ref (
     primary,
     secondary,
     dt,
     samp_freq,
     time_window_ref,
     N_window_ref,
     N_window);

 measure_time.end();

 std::cout << "Training time = " << gettime() << std::endl;

 std::cout << "Training time = " << measure_time.total_time() << std::endl;

 mem_buffer.clear_memory();

 delete[] ax;
 delete[] ay;
 delete[] az;
 delete[] buf;

}
