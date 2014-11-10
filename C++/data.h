/*
 Data class
 Class wrapper to handle the data specific operations and attributes
 */

enum { t_space, f_space };

class DATA {

   public:

      DATA( float *, /* Pointer to the data */
            int,     /* Number of data elements in this set (N). Make sure there
                        is enough memory allocated to hold one more data element
                        (N+1) to accomidate the fft packing the nyquist.*/
            float ); /* Delta time dt */
      ~DATA();

      void data_fft( void );  /* Performs an FFT on the data */
      void data_ifft( void );  /* Performs an FFT on the data */

   private:

      float *data;
      int    N;
      float  dt;
      float  df;
      int    state; // Current state of the data (t_space or f_space)
};
