/*
 * Example using the ANN
 */

#include <stdio.h>
#include <iostream>
#include "ann.h"

int main(){
   
   int LayerSizes[5] = {3, 4, 4, 4, 2};
   float inp[3] = {3.0f, 1.29f, 2.02f};
   float *out;

   // Construct the network
   ann NN(LayerSizes, 5, -1.0f, 2.0f, 0.125f);
   
   // Target inputs (Example)
   float inpSet[4][3] = {{ 5.0, 2.2, 3.1},
                          { 4.8, 1.9, 3.0},
                          {-8.0,-2.0,-2.9},
                          {-7.8,-2.1,-2.7}};

   // Target outputs (Example)
   float t[4][2] = {{1,0},
                     {1,0},
                     {0,1},
                     {0,1}};

   // Train the network
   NN.train(&inpSet[0][0], &t[0][0], 4, 1000, true);
   
   // Run the network on a provided input
   out = NN.forward(inp);
   
   // Display results
   std::cout << "Example input result" << std::endl;
   printf("[%f, %f, %f] -> [%f, %f]\n",
          inp[0],inp[1],inp[2],out[0],out[1]);

   /*********************************************************************************/

   // Compare to expected outputs

   std::cout << std::endl
             << "Comparing training input values to expected outputs" << std::endl;

   for (int i = 0; i < 4; i++) {
      out = NN.forward(&inpSet[i][0]);
      printf("[%f, %f, %f] -> [%f, %f] ",
             inpSet[i][0],inpSet[i][1],inpSet[i][2],out[0],out[1]);
      printf("expected: [%f, %f]\n", t[i][0], t[i][1]);
   }
   
   return 0;
}
