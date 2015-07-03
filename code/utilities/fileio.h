#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <fstream>

namespace fio {
 class kinIO {

   public:

      kinIO ( const char path[] );
      ~kinIO ();

      /* check if the start of the array from get_* has N many valid
         elements in its array. */
      bool valid_start_end (float start, float window);

      // Returns a pointer to the acceleration data in x,y,z respectively of sensor 1
      float *access_sens_ax (float start, int sens_num);
      float *access_sens_ay (float start, int sens_num);
      float *access_sens_az (float start, int sens_num);

      void load_sens_ax (float *ax, float time, int sens_num, int N);
      void load_sens_ay (float *ay, float time, int sens_num, int N);
      void load_sens_az (float *az, float time, int sens_num, int N);

      float get_total_time (void);

   private:

      int count_kinetisense_lines(
          /* Reads in the file data and counts how many lines of
             data are in the file. */
         const char path[]); /* [I  ] Path to the kinetisense data */

      float **read_kinetisense(
          /* Returns a pointer that holds the data. This will contain the acceleration
             and rotation data in units of Gs (1G = 9.81 m/s/s) and EMG data. There
             are 20 arrays of length N_lines as follows:

      float[0]            -sensor 1 acceleration data in x
      float[1]            -sensor 1 acceleration data in y
      float[2]            -sensor 1 acceleration data in z
      float[3]            -sensor 1 rotation data in x
      float[4]            -sensor 1 rotation data in y
      float[5]            -sensor 1 rotation data in z
      float[6]            -sensor 2 acceleration data in x
      float[7]            -sensor 2 acceleration data in y
      float[8]            -sensor 2 acceleration data in z
      float[9]            -sensor 2 rotation data in x
      float[10]           -sensor 2 rotation data in y
      float[11]           -sensor 2 rotation data in z
      float[12]           -sensor 3 acceleration data in x
      float[13]           -sensor 3 acceleration data in y
      float[14]           -sensor 3 acceleration data in z
      float[15]           -sensor 3 rotation data in x
      float[16]           -sensor 3 rotation data in y
      float[17]           -sensor 3 rotation data in z
      float[18]           -EMG 1
      float[19]           -EMG 2

           */
          const char path[],   /* File of the kinetisense data */
          const int  N_lines); /* number of lines in the file  */

      // Overloaded function of above
      float **read_kinetisense (const char path[]);

      // Number of lines of data in the kinetisense csv data file
      int N;

      // Sampling frequency (Hz)
      float samp_freq;

      // Total time read
      float total_time;

      // Pointers to the kinetisense data
      float **kin_data;

      float *sensor1_ax;
      float *sensor1_ay;
      float *sensor1_az;

      float *sensor1_wx;
      float *sensor1_wy;
      float *sensor1_wz;

      float *sensor2_ax;
      float *sensor2_ay;
      float *sensor2_az;

      float *sensor2_wx;
      float *sensor2_wy;
      float *sensor2_wz;

      float *sensor3_ax;
      float *sensor3_ay;
      float *sensor3_az;

      float *sensor3_wx;
      float *sensor3_wy;
      float *sensor3_wz;

 };

 void write_correlations(const std::string path, float *corr_ax, float *corr_ay, int N);

 void write_val(int val,   std::string power_file, bool init);
 void write_val(float val, std::string power_file, bool init);

/*****************************************************/

 class readRefs {

    public:

       readRefs(std::string in_file);
      ~readRefs(void);

       int get_Nrefs(void);
       std::string get_ref_path(int i_th);

    private:

       char *buffer;
       int length;
       int N_refs;
 };

/*****************************************************/

/* parameters class:

   Matched Filter processing:
        tag
        time_window
        freq_range
        cutoff_freq
        samp_freq
        threshold
        sex
        age
        weight
        height
        data_path

   Matched Filter training:
        time_window
        freq_range
        cutoff_freq
        samp_freq
        ref_time
        data_path
        ref_path
        activity_ID
*/

 class parameters {

   public:

      parameters (std::string path);

      void  print (void);

      float       get_dt (void);
      float       get_time_window (void);
      float       get_time_window_ref (void);
      float       get_samp_freq (void);
      float       get_freq_range (void);
      float       get_cutoff_freq (void);
      float       get_threshold (void);
      int         get_N_window (void);
      int         get_N_window_ref (void);
      int         get_sex (void);
      float       get_age (void);
      float       get_weight (void);
      float       get_height (void);
      bool        Do_taper (void);
      std::string get_tag (void);
      std::string get_data_path (void);
      std::string get_ref_path (void);
      std::string get_activity_ID (void);

   private:

      std::ifstream input;

      std::string tag;         bool b_tag;
      float time_window;       bool b_time_window;
      float freq_range;        bool b_freq_range;
      float cutoff_freq;       bool b_cutoff_freq;
      float samp_freq;         bool b_samp_freq;
      float ref_time;          bool b_ref_time;
      float threshold;         bool b_threshold;
      int   sex;               bool b_sex;
      float age;               bool b_age;
      float weight;            bool b_weight;
      float height;            bool b_height;
      std::string data_path;   bool b_data_path;
      std::string ref_path;    bool b_ref_path;
      std::string activity_ID; bool b_activity_ID;

      float dt;
      bool  b_taper;
      int   sens_training;

      float        get_parameter_f   ( std::string parameter);
      int          get_parameter_i   ( std::string parameter);
      std::string  get_parameter_s   ( std::string parameter);
      int          get_parameter_sex ( std::string parameter);

 };

/*****************************************************/

}

#endif
