#include <string>
class matchedfilter {

   public:

      matchedfilter  (int N_data, int activity_ID);
      matchedfilter  (const char path[], int N_data);
      ~matchedfilter (void);

      /* run the main matched filter program for this instance */

      int run (float *sig_ax, float *sig_ay, float dt_sig,
               float sig_samp_freq, int data_N, float *taper,
               bool apply_taper, float *work_buffer);

      void load_ref (float *ax_in, float *ay_in,
                     float dt_in, float samp_freq_in,
                     float time_window_in, int N_window_in, int N_data_in);

      float get_corr_ax (void); // Return correlation in x
      float get_corr_ay (void); // Return correlation in y

      void set_ID(int);  // set the activity ID
      int  get_ID(void); // get the activity ID

      bool write(std::string); // write the data to file
      void write_corr (std::string file, bool initial_write);
      void print_all (void);
      void apply_taper (
                                 float *taper_buff,
                                 float cutoff_freq,
                                 float freq_range);
      void apply_fft(int N);
      void apply_ifft(int N);

   private:

      int   N_data_ref;       // Number of data points allocated for the reference signal
      int   N_window_ref;     // Number of sampling points of the reference signal <= N_data_ref
      float dt_ref;           // Delta time intervals between samples of the reference signal
      float samp_freq_ref;    // Sampling frequency of the reference signal
      float time_window_ref;  // Time window of data making up the reference signal

      int   activity_ID;      // Compendium ID of the activity

      float *ref_ax;          // Reference in x (Primary direction)
      float *ref_ay;          // Reference in y (Secondary direction)

      float norm_ref_ax;      // Normalizing factor of the reference
      float norm_ref_ay;      // Normalizing factor of the reference

      float corr_ax;          // Normalized correlation in x (Primary direction)
      float corr_ay;          // Normalized correlation in y (Secondary direction)

      /* Boolean cases to make sure values and such are set before calling certain routines */

      bool correlations_computed;

};

/* Cross correlation */

float crosscorr(float *ref, float *signal, float norm_ref, float *taper, bool apply_taper,
                float *buffer, float dt, float samp_freq,
                int N_window_ref, int N_data);

/******************************/

class node {

   public:

      node( matchedfilter* );
      ~node (void);

      matchedfilter *MF;

      node *prev;
      node *next;
};

/******************************/

class mf_list {

   public:

      mf_list(void);
      ~mf_list(void);

      void insert (matchedfilter*);
      node *pop (void);
      void goto_next(void);
      void goto_last(void);
      bool is_last (void);
      void goto_prev(void);
      void goto_first(void);
      void append (matchedfilter*);
      matchedfilter *get_MF (void);
      int get_N (void);

   private:

      int  N;

      node *first;
      node *NODE;
      node *last;

};
