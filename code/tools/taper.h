void taper_f(
       float *taper,
       float time_window,
       float cutoff_freq,
       float freq_range,  // Hz. In each direction from cut-off frequency
       float samp_freq,
       float dt,
       int   N);
