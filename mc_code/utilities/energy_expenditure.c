#include "energy_expenditure.h"
#include "stdio.h"

/*
 * Function NAME: energy_expenditure
 */
float energy_expenditure (
        float    weight,
        float    height,
        float    age,
        int      sex,
        int      act,
        float    power)
{

   float RMR, MET;
   float energy_exp; // K cal / min

   // compute the RMR using the Mufflin equation

   switch (sex) {

      case 1: // MALE
         RMR = 10.0 * weight + 6.25 * height - 5.0 * age + 5.0;
         break;

      case 2: // FEMALE
         RMR = 10.0 * weight + 6.25 * height - 5.0 * age - 161.0;
         break;

      default:
         printf("Sex unspecified\n");
         RMR = 0.0f;
   }

   // get the MET

   switch (act) {

      case 17152: // WALKING_LVL_SLOW_FIRM
         MET = 2.5f;
         break;

      case 17190: // WALKING_LVL_MOD_FIRM
         MET = 3.3f;
         break;

      case 1015: // BICYCLING
         MET = 8.0f;
         break;

      case 12020: // JOGGING
         MET = 7.0f;
         break;

      case 12030: // RUNNING_5_MPH
         MET = 8.0f;
         break;

      case 12050: // RUNNING_6_MPH
         MET = 10.0f;
         break;

      case 12070: // RUNNING_7_MPH
         MET = 11.5f;
         break;

      case 12090: // RUNNING_8_MPH
         MET = 13.5f;
         break;

      case 12110: // RUNNING_9_MPH
         MET = 15.0f;
         break;

      case 12120: // RUNNING_10_MPH
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
