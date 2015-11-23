#ifndef RUN_MF_H
#define RUN_MF_H

float run_mf (float *primary_acceleration,
              float *secondary_acceleration,
              float *reference_x,
              float *reference_y,
              float  dt,
              float  time_window,
              float  ref_time_window,
              float  samp_freq,
              float *mem_buffer_f);

#endif
