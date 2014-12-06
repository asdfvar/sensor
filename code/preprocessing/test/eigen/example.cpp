#include<iostream>
#include "eigen.h"

int main() {

   float mat[3][3] = {{1.0, 2.0, 3.0}, {2.0, 2.0, 4.0}, {3.0, 4.0, 2.0}};
   float eig[3];
   float eigVec[3][3];

   eigen_val(mat, eig);

   eigen_vec(mat, eig, &eigVec[0][0]);

   std::cout << "eigenvalues = "
     << eig[0] << "," << eig[1] << "," << eig[2] << std::endl;

   std::cout << "eigenvector 1 = "
       << eigVec[0][0] << "," << eigVec[0][1] << "," << eigVec[0][2] << std::endl
       << "eigenvector 2 = "
       << eigVec[1][0] << "," << eigVec[1][1] << "," << eigVec[1][2] << std::endl
       << "eigenvector 3 = "
       << eigVec[2][0] << "," << eigVec[2][1] << "," << eigVec[2][2] << std::endl;

/*
 * eigen values = 7.84091392, -0.55886747, -2.28204645
 *
 * eigen vector 1 = -0.4615797, -0.60338291, -0.65028705
 * eigen vector 2 = -0.8081039, 0.58839073, 0.02764848
 * eigen vector 3 = -0.36594026, -0.53826148, 0.75918529
 */

   // computing the eigen vectors without calling the eigen value computation first
   eigen_vec(mat, &eigVec[0][0]);

   // another way
   std::cout << std::endl;
   std::cout << "eigenvector 1 = "
       << eigVec[0][0] << "," << eigVec[0][1] << "," << eigVec[0][2] << std::endl
       << "eigenvector 2 = "
       << eigVec[1][0] << "," << eigVec[1][1] << "," << eigVec[1][2] << std::endl
       << "eigenvector 3 = "
       << eigVec[2][0] << "," << eigVec[2][1] << "," << eigVec[2][2] << std::endl;

   return 0;
}
