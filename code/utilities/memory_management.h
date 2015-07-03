#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>

class MEMORY
{
   public:

      MEMORY  (size_t N_floats);
      ~MEMORY (void);

      void clear_memory (void);

      float *allocate_float (size_t N);

   private:

      float *float_ptr_base;
      float *float_ptr;
      int    N_floats;
};

#endif
