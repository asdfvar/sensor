#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <string>

namespace fio {
 class kinIO {
   public:

      kinIO ( const char path[] );
      ~kinIO ();

      /* check if the start of the array from get_* has N many valid
         elements in its array. */
      bool valid_start_end (float start, float window);

      // Returns a pointer to the acceleration data in x,y,z respectively of sensor 1
      float *get_sens_ax (float start, int sens_num);
      float *get_sens_ay (float start, int sens_num);
      float *get_sens_az (float start, int sens_num);

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
          const char path[], /*   File of the kinetisense data */
          const int  N_lines); /* number of lines in the file */

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
 };
}

#endif
