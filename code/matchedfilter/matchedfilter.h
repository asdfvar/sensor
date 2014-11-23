class matchedfilter {

   public:

      matchedfilter (float *ref, int N);
      ~matchedfilter (void);

      float run (float *signal, int N);

   private:

      int N;
      float *ref;

      void crosscorr(float *ref, float *signal, int N, float *corr, int *shift);

};
