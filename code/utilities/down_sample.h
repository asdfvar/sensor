#ifndef DOWN_SAMPLE_H
#define DOWN_SAMPLE_H

int down_sample (float *data,
                 float  sampling_freq,
                 float  time_length,
                 int    downsamp_fact,
                 float *workspace);

#endif
