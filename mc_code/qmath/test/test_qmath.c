#include <stdio.h>
#include "qmath.h"
#include "stdint.h"

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

#ifdef PC
   int16_t p = 14848; // 3.625 in Q12
   int16_t q = 5120;  // 1.25 in Q12
   int16_t r;

   //r = (p >> 6) * (q >> 6);
   r = (p * q) >> 12; // 14848 * 10^-12 * 5120*10^-12 = (18560*10^-12)*10^-12
   printf("r = %d\n", r);
   printf("float(r) = %f\n", (float)(int)r * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f);

#endif

   return 0;
}
