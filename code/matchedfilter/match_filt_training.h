void match_filt_training(
              matchedfilter *MF,
              fio::kinIO *KIN,
              std::string activity_ID,
              float samp_freq,
              float dt,
              float time_window, /* Signal window time (seconds) */
              int   N_window, /* Signal window points (elements) */
              float time_window_ref, /* Reference length (seconds) */
              int   N_window_ref, /* Reference length (# elements) */
              int   sens_num); /* Which Kinetesense sensor */
