#include "filter.h"
#include <iostream>

int main()
{

   MEMORY memory( 100 );

   float data[10] = {1.0, -7.0, 3.0, 4.0, 3.0,
                     -2.0, 9.0, 2.0, -3.0, 1.0};

   float data2[10];

   for (int k = 0; k < 10; k++) data2[k] = data[k];

   apply_filter (data2, 5, 10, memory);

   std::cout << std::endl;
   std::cout << "from" << std::endl;
   for (int k = 0; k < 10; k++)
   {
      std::cout << data[k] << " ";
   }
   std::cout << std::endl;

   std::cout << "to" << std::endl;
   for (int k = 0; k < 10; k++)
   {
      std::cout << data2[k] << " ";
   }
   std::cout << std::endl;

   memory.clear_memory();

   return 0;
}
