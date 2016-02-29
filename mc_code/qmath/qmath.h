#ifndef QMATH_H
#define QMATH_H

  /*
  ** For micro-controller compiled code
  */

#ifndef PC

  #include "qmath_pc_16_fixed.h"

#else

  /*
  ** For PC compiled code
  */

  #define PC_16_fixed

  #ifdef PC_16_fixed
    #include "qmath_pc_16_fixed.h"
  #endif

  #ifdef PC_32_float
    #include "qmath_pc_32_float.h"
  #endif


#endif

#endif
