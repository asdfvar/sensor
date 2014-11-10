/*
 data class
 */

enum { t_space, f_space };

class DATA {

   public:

      DATA( float *, /* Pointer to the data */
            int );   /* Number of data elements in this set */
      ~DATA();

   private:

      float *data;
      int    N;
      int state;
};
