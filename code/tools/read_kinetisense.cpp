/*
 * FUNCTIONAL DESCRIPTION:
 *    This routine reads in the kinetisense data.
 *
 * 
 */

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

int count_kinetisense_lines(
       const char path[]) /* [I  ] Path to the kinetisense data */
{
  std::string line;
  std::ifstream kin_data;
  kin_data.open (path);

  int N_lines = 0;

  while (std::getline (kin_data, line))
     N_lines++;

  kin_data.close();

  N_lines -= 5; // first 5 lines are header lines

  return N_lines;
}

/**********************************************************************/

float **read_kinetisense(
          /* Returns a pointer to hold the data. On input, this pointer
             is NULL. On output, this will contain the data acceleration
             data in units of Gs (1G = 9.81 m/s/s)*/
       const char path[]) /* [I  ] Path to the kinetisense data */
{

  std::string line;
  std::ifstream kin_data;
  kin_data.open (path);
  int N_lines = count_kinetisense_lines(path);

  float freq = 200.0; // Hz

  float **data = new float *[12];
  for (int k = 0; k < 12; k++)
     data[k] = new float[N_lines];

  kin_data.seekg(0);

  // read past the header
  for (int k = 0; k < 5; k++) std::getline (kin_data, line);
  
  for (int k = 0; k < N_lines; k++) {
     // Sensor 1 x-axis
     std::getline (kin_data, line, ',');
     data[0][k] = atof(line.c_str())/250.0;
     // Sensor 1 y-axis
     std::getline (kin_data, line, ',');
     data[1][k] = atof(line.c_str())/250.0;
     // Sensor 1 z-axis
     std::getline (kin_data, line, ',');
     data[2][k] = atof(line.c_str())/250.0;
     // Sensor 1 EMG
     std::getline (kin_data, line, ',');
     data[3][k] = atof(line.c_str());
     // Sensor 2 x-axis
     std::getline (kin_data, line, ',');
     data[4][k] = atof(line.c_str())/250.0;
     // Sensor 2 y-axis
     std::getline (kin_data, line, ',');
     data[5][k] = atof(line.c_str())/250.0;
     // Sensor 2 z-axis
     std::getline (kin_data, line, ',');
     data[6][k] = atof(line.c_str())/250.0;
     // Sensor 2 EMG
     std::getline (kin_data, line, ',');
     data[7][k] = atof(line.c_str());
     // Sensor 3 x-axis
     std::getline (kin_data, line, ',');
     data[8][k] = atof(line.c_str())/250.0;
     // Sensor 3 y-axis
     std::getline (kin_data, line, ',');
     data[9][k] = atof(line.c_str())/250.0;
     // Sensor 3 z-axis
     std::getline (kin_data, line, ',');
     data[10][k] = atof(line.c_str())/250.0;
     // Sensor 3 EMG
     std::getline (kin_data, line, ',');
     data[11][k] = atof(line.c_str());
  }

  kin_data.close();

  return data;
}
