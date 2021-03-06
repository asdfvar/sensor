#include "memory_management.h"
#include <iostream>

/*
 * Constructor NAME: MEMORY
 */
MEMORY::MEMORY (size_t N_floats_in)
{
   N_floats = N_floats_in;
   float_ptr_base = new float[ N_floats ];
   float_ptr = float_ptr_base;
}

/*
 * Destructor NAME: MEMORY
 */
MEMORY::~MEMORY (void) {}

/*
 * Function NAME: allocate_float
 */
float *MEMORY::allocate_float (size_t N)
{

   /*
   ** Check if there is enough allocated memory
   */
   size_t memory_left = N_floats - (size_t)(float_ptr - float_ptr_base);

   if ( N > memory_left )
   {
      std::cout << "Error: Attempting to reserve more memory (" << N << ")" <<
                   "than what is left ( " << memory_left <<
                   " floats) from the total (" << N_floats << " floats)."
                   << std::endl;

      return NULL;

   } else {

      float *ptr = float_ptr;

      float_ptr += N;

      return ptr;
   }
}

/*
 * Function NAME: clear_memory
 */
void MEMORY::clear_memory (void)
{
   std::cout << "Freeing memory buffer" << std::endl;
   delete[] float_ptr_base;
}
