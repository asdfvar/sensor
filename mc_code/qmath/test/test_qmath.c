#include <stdio.h>
#include "qmath.h"

int main()
{

#ifdef PC
   printf("PC defined\n");
#else
   printf("PC not defined. Compiled for the micro-controller\n");
#endif

   QMATH_q9 x = QMATH_Q9( 7.0f );
   QMATH_q9 y = QMATH_Q9( 3.0f );
   QMATH_q9 z;

   z = QMATH_Q9mpy(x, y);

   printf("z = %f\n", z);

   QMATH_q10 pi = QMATH_Q10( 3.14159f );
   QMATH_q10 diameter = QMATH_Q10( 4.0f );
   QMATH_q10 circ;

   circ = QMATH_Q10mpy(diameter, pi);

   printf("circumference = %f\n", circ);

   return 0;
}
