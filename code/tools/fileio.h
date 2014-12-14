
namespace fio {

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
       const char path[], /* [I  ] File of the kinetisense data */
       const int  N_lines); /* number of lines in the file */

   float **read_kinetisense( const char path[] );
   void read_reference_headers ( const char path[],
                         int *N, float *ref_freq, float *ref_time );
   void read_reference ( const char path[], float *ref_data, int N);
   int count_ref_lines ( const char path[] );
}
