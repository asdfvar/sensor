#include <iostream>
#include "eigen.h"

int preproc(
     float *ax,      /* Acceleration data in x               */
     float *ay,      /* Acceleration data in y               */
     float *az,      /* Acceleration data in z               */
     float *power,   /* Resulting power of the signal        */
     float dt,       /* Delta time comstant                  */
     float window,   /* Time window of the data              */
     float samp_freq,/* Sampling frequency of the data       */
     int   N)        /* Number of sample points              */
{

   int i,j,k;
   float cov_mat[3][3]; // Covariance matrix

   /* Demean the data */

   float ave;
   for (k = 0, ave = 0.0; k < N; k++) ave += ax[k];
   ave /= (float) N;
   for (k = 0; k < N; k++) ax[k] -= ave;
   for (k = 0, ave = 0.0; k < N; k++) ave += ay[k];
   ave /= (float) N;
   for (k = 0; k < N; k++) ay[k] -= ave;
   for (k = 0, ave = 0.0; k < N; k++) ave += az[k];
   ave /= (float) N;
   for (k = 0; k < N; k++) az[k] -= ave;

   /* Compute the power of the signal */

   *power = 0.0;
   for (k = 0; k < N; k++) {
      *power += ax[k] * ax[k];
      *power += ay[k] * ay[k];
      *power += az[k] * az[k];
   }
   *power *= dt;
   *power /= window;

   /* Build the covariance matrix */

   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         cov_mat[i][j] = 0.0;

   for (k = 0; k < N; k++) {
      cov_mat[0][0] += ax[k] * ax[k];
      cov_mat[0][1] += ax[k] * ay[k];
      cov_mat[0][2] += ax[k] * az[k];
      cov_mat[1][1] += ay[k] * ay[k];
      cov_mat[1][2] += ay[k] * az[k];
      cov_mat[2][2] += az[k] * az[k];
   }

   cov_mat[1][0] = cov_mat[0][1];
   cov_mat[2][0] = cov_mat[0][2];
   cov_mat[2][1] = cov_mat[1][2];

   float eigVal[3];
   float eigVec[3][3];

   eigen(cov_mat, eigVal, &eigVec[0][0]);

   float tmp;

   /* Re-order the eigen values in descending order along with their associated eigen vectors */
   for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++) {
         if (eigVal[j] < eigVal[j+1]) {
            tmp = eigVal[j];
            eigVal[j] = eigVal[j+1];
            eigVal[j+1] = tmp;

            for (k = 0; k < 3; k++){
               tmp = eigVec[j][k];
               eigVec[j][k] = eigVec[j+1][k];
               eigVec[j+1][k] = tmp;
            }
         }
      }
   }

   /* Re-orient the axes in the direction of motion */
   float *eigVec_1 = &eigVec[0][0];
   float *eigVec_2 = &eigVec[1][0];
   float *eigVec_3 = &eigVec[2][0];

   float x,y,z;

   for (k = 0; k < N; k++) {
      x = ax[k];
      y = ay[k];
      z = az[k];

      ax[k] = x*eigVec_1[0] + y*eigVec_1[1] + z*eigVec_1[2];
      ay[k] = x*eigVec_2[0] + y*eigVec_2[1] + z*eigVec_2[2];
      az[k] = x*eigVec_3[0] + y*eigVec_3[1] + z*eigVec_3[2];
   }

   return 0;
}
