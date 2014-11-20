class matchedfilter {

   public:

      matchedfilter (float *ref, int N);
      ~matchedfilter (void);

      float run (float *signal, int N);

   private:

      int N;
      float *ref;

};
