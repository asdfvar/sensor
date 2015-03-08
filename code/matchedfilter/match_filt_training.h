void match_filt_training(
              matchedfilter *MF,
              fio::kinIO *KIN,
              float *taper,
              float cutoff_freq,
              float freq_range,
              bool  apply_taper,
              float samp_freq,
              float dt,
              float time_window, /* Signal window time (seconds) */
              int   N_window, /* Signal window points (elements) */
              float time_window_ref, /* Reference length (seconds) */
              int   N_window_ref, /* Reference length (# elements) */
              int   sens_num); /* Which Kinetesense sensor */
