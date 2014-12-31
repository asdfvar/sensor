class matchedfilter {

   public:

      matchedfilter  (void);
      ~matchedfilter (void);

      /* Load the reference data as well as point to some work buffer space */

      void load_ref (float *ref_ax, float *ref_ay,
                     float dt, float samp_freq, float time_window,
                     int N_data, int N_window,
                     float *work_buf);

      /* run the main matched filter program for this instance */

      void run (float *sig_ax, float *sig_ay, float dt_sig, float sig_samp_freq, int data_N,
                float *corr_ax, float *corr_ay);

   private:

      int N_data_ref;   // Number of data points allocated for the reference signal
      int N_window_ref; // Number of sampling points that makes up the reference signal
      float dt_ref;     // Delta time intervals between samples of the reference signal
      float samp_freq_ref; // Sampling frequency of the reference signal
      float time_window_ref; // Time window of data making up the reference signal
      float *ref_ax;    // Reference signal in x (Primary direction)
      float *ref_ay;    // Reference signal in y (Secondary direction)

      bool loaded_ref;

      float *work_buffer; // Buffer space the same size as the signal

      void crosscorr(float *ref, float *signal, float *buffer, float dt, float samp_freq,
                     int N_window_ref, int N_data, float *corr, int *shift);

};
