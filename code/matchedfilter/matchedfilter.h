enum data_form {TIME, FREQ};

class matchedfilter {

   public:

      matchedfilter  (int N_data);
      matchedfilter  (const char path[], int N_data);
      ~matchedfilter (void);

      /* run the main matched filter program for this instance */

      int run (float *sig_ax, float *sig_ay, float dt_sig, float sig_samp_freq, int data_N,
               float *work_buffer);

      void load_ref (float *ax_in, float *ay_in,
                     float dt_in, float samp_freq_in,
                     float time_window_in, int N_window_in, int N_data_in);

      float get_corr_ax (void); // Return correlation in x
      float get_corr_ay (void); // Return correlation in y

   private:

      int   N_data_ref;       // Number of data points allocated for the reference signal
      int   N_window_ref;     // Number of sampling points that makes up the reference signal
      float dt_ref;           // Delta time intervals between samples of the reference signal
      float samp_freq_ref;    // Sampling frequency of the reference signal
      float time_window_ref;  // Time window of data making up the reference signal

      float *ref_ax;          // Reference in x (Primary direction)
      float *ref_ay;          // Reference in y (Secondary direction)

      float corr_ax;          // Normalized correlation in x (Primary direction)
      float corr_ay;          // Normalized correlation in y (Secondary direction)

      /* Boolean cases to make sure values and such are set before calling certain routines */

      bool correlations_computed;
      data_form ref_data_form;

      /* Cross correlation */

      float crosscorr(float *ref, float *signal, float *buffer, float dt, float samp_freq,
                     int N_window_ref, int N_data, data_form ref_form);

};
