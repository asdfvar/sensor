#include "energy_expenditure.h"
#include "compendium.h"
#include <iostream>

float energy_expenditure (
        float    weight,
        float    height,
        float    age,
        SEX      sex,
        int      act,          /* ACTIVITY     */
        float    power,        /* signal power */
        float    time_window)
{

   float RMR, MET;
   float energy_exp; // K cal / min

   // compute the RMR

   switch (sex) {

      case MALE:
         RMR = 10.0 * weight + 6.25 * height - 5.0 * age + 5.0;
         break;

      case FEMALE:
         RMR = 10.0 * weight + 6.25 * height - 5.0 * age - 161.0;
         break;

      default:
         std::cout << "Sex unspecified" << std::endl;
         RMR = 0.0f;
   }

   // get the MET

   switch (act) {

      case WALKING_LVL_SLOW_FIRM:
         MET = 2.5;
         break;

      case WALKING_LVL_MOD_FIRM:
         MET = 3.3;
         break;

      case BICYCLING:
         MET = 8.0;
         break;

      default: /* NONE */
         MET = 1.0;
   }

   energy_exp = RMR * MET;

   return energy_exp;

}
