#include "energy_expenditure.h"
#include "compendium.h"
#include <iostream>

/*
 * Function NAME: energy_expenditure
 */
float energy_expenditure (
        float    weight,
        float    height,
        float    age,
        int      sex,
        int      act,          /* ACTIVITY     */
        float    power,        /* signal power */
        float    time_window)
{

   float RMR, MET;
   float energy_exp; // K cal / min

   // compute the RMR using the Mufflin equation

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
         MET = 2.5f;
         break;

      case WALKING_LVL_MOD_FIRM:
         MET = 3.3f;
         break;

      case BICYCLING:
         MET = 8.0f;
         break;

      case JOGGING:
         MET = 7.0f;
         break;

      case RUNNING_5_MPH:
         MET = 8.0f;
         break;

      case RUNNING_6_MPH:
         MET = 10.0f;
         break;

      case RUNNING_7_MPH:
         MET = 11.5f;
         break;

      case RUNNING_8_MPH:
         MET = 13.5f;
         break;

      case RUNNING_9_MPH:
         MET = 15.0f;
         break;

      case RUNNING_10_MPH:
         MET = 16.0f;
         break;

      default: /* NONE */
         if (power < 0.5)      MET = 1.0f;
         else if (power < 2.0) MET = 3.0f;
         else if (power < 5.0) MET = 6.0f;
         else                  MET = 12.0f;
   }

   energy_exp = RMR * MET * 1.1574074e-5; // kCals / second

   return energy_exp;

}
