
  #include "stdint.h"

  #define BYTES_PER_ELMNT 4

  #define QMATH_q1     int16_t
  #define QMATH_q2     int16_t
  #define QMATH_q3     int16_t
  #define QMATH_q4     int16_t
  #define QMATH_q5     int16_t
  #define QMATH_q6     int16_t
  #define QMATH_q7     int16_t
  #define QMATH_q8     int16_t
  #define QMATH_q9     int16_t
  #define QMATH_q10    int16_t
  #define QMATH_q11    int16_t
  #define QMATH_q12    int16_t
  #define QMATH_q13    int16_t
  #define QMATH_q14    int16_t
  #define QMATH_q15    int16_t

  #define QMATH_Q1(A)    ((int16_t)(A * 2.0f))
  #define QMATH_Q2(A)    ((int16_t)(A * 2.0f * 2.0f))
  #define QMATH_Q3(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q4(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q5(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q6(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q7(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q8(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q9(A)    ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q10(A)   ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q11(A)   ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q12(A)   ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q13(A)   ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q14(A)   ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))
  #define QMATH_Q15(A)   ((int16_t)(A * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f * 2.0f))

  // multiplication
  #define QMATH_Q1mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 1)
  #define QMATH_Q2mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 2)
  #define QMATH_Q3mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 3)
  #define QMATH_Q4mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 4)
  #define QMATH_Q5mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 5)
  #define QMATH_Q6mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 6)
  #define QMATH_Q7mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 7)
  #define QMATH_Q8mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 8)
  #define QMATH_Q9mpy(A, B)    ((int16_t)(((int32_t)A * (int32_t)B) >> 9))
  #define QMATH_Q10mpy(A, B)   ((int16_t)(((int32_t)A * (int32_t)B) >> 10)
  #define QMATH_Q11mpy(A, B)   ((int16_t)(((int32_t)A * (int32_t)B) >> 11)
  #define QMATH_Q12mpy(A, B)   ((int16_t)(((int32_t)A * (int32_t)B) >> 12)
  #define QMATH_Q13mpy(A, B)   ((int16_t)(((int32_t)A * (int32_t)B) >> 13)
  #define QMATH_Q14mpy(A, B)   ((int16_t)(((int32_t)A * (int32_t)B) >> 14)
  #define QMATH_Q15mpy(A, B)   ((int16_t)(((int32_t)A * (int32_t)B) >> 15)

  // square root
  #define QMATH_Q1sqrt(A)      sqrtf(A)
  #define QMATH_Q2sqrt(A)      sqrtf(A)
  #define QMATH_Q3sqrt(A)      sqrtf(A)
  #define QMATH_Q4sqrt(A)      sqrtf(A)
  #define QMATH_Q5sqrt(A)      sqrtf(A)
  #define QMATH_Q6sqrt(A)      sqrtf(A)
  #define QMATH_Q7sqrt(A)      sqrtf(A)
  #define QMATH_Q8sqrt(A)      sqrtf(A)
  #define QMATH_Q9sqrt(A)      sqrtf(A)
  #define QMATH_Q11sqrt(A)     sqrtf(A)
  #define QMATH_Q12sqrt(A)     sqrtf(A)
  #define QMATH_Q13sqrt(A)     sqrtf(A)
  #define QMATH_Q14sqrt(A)     sqrtf(A)
  #define QMATH_Q15sqrt(A)     sqrtf(A)
  #define QMATH_Q16sqrt(A)     sqrtf(A)

  // division
  #define QMATH_Q1div(A, B)    (A / B)
  #define QMATH_Q2div(A, B)    (A / B)
  #define QMATH_Q3div(A, B)    (A / B)
  #define QMATH_Q4div(A, B)    (A / B)
  #define QMATH_Q5div(A, B)    (A / B)
  #define QMATH_Q6div(A, B)    (A / B)
  #define QMATH_Q7div(A, B)    (A / B)
  #define QMATH_Q8div(A, B)    (A / B)
  #define QMATH_Q9div(A, B)    (A / B)
  #define QMATH_Q10div(A, B)   (A / B)
  #define QMATH_Q11div(A, B)   (A / B)
  #define QMATH_Q12div(A, B)   (A / B)
  #define QMATH_Q13div(A, B)   (A / B)
  #define QMATH_Q14div(A, B)   (A / B)
  #define QMATH_Q15div(A, B)   (A / B)

  #define QMATH_Q1toF(A)  ((float)A * 0.5f)
  #define QMATH_Q2toF(A)  ((float)A * 0.5f * 0.5f)
  #define QMATH_Q3toF(A)  ((float)A * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q4toF(A)  ((float)A * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q5toF(A)  ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q6toF(A)  ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q7toF(A)  ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q8toF(A)  ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q9toF(A)  ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q10toF(A) ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q11toF(A) ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q12toF(A) ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q13toF(A) ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q14toF(A) ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)
  #define QMATH_Q15toF(A) ((float)A * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f)

