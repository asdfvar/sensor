/*
 * DESCRIPTION:
 *    This file contains routines that read in the kinetisense data.
 *
 */

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

int count_kinetisense_lines(
       /* Reads in the file data and counts how many lines of
          data is in the file. */
       const char path[]) /* [I  ] Path to the kinetisense data */
{
  std::string line;
  std::ifstream kin_data;
  kin_data.open (path);

  int N_lines = 0;

  while (std::getline (kin_data, line))
     N_lines++;

  kin_data.close();

  N_lines -= 1; // first line is a header

  return N_lines;
}

/**********************************************************************/

float **read_kinetisense(
          /* Returns a pointer to hold the data. This will contain the acceleration
             and rotation data in units of Gs (1G = 9.81 m/s/s) and EMG data. There
             are 20 arrays of length N_lines as follows:

   float[0]       -sensor 1 acceleration data in x
   float[1]            -sensor 1 acceleration data in y
   float[2]            -sensor 1 acceleration data in z
   float[3]            -sensor 1 rotation data in x
   float[4]            -sensor 1 rotation data in y
   float[5]            -sensor 1 rotation data in z
   float[6]            -sensor 2 acceleration data in x
   float[7]            -sensor 2 acceleration data in y
   float[8]            -sensor 2 acceleration data in z
   float[9]            -sensor 2 rotation data in x
   float[10]            -sensor 2 rotation data in y
   float[11]            -sensor 2 rotation data in z
   float[12]            -sensor 3 acceleration data in x
   float[13]            -sensor 3 acceleration data in y
   float[14]            -sensor 3 acceleration data in z
   float[15]            -sensor 3 rotation data in x
   float[16]            -sensor 3 rotation data in y
   float[17]            -sensor 3 rotation data in z
   float[18]            -EMG 1
   float[19]            -EMG 2

           */
       const char path[]) /* [I  ] File of the kinetisense data */
{

  std::string line;
  std::ifstream kin_data;
  kin_data.open (path);
  int N_lines = count_kinetisense_lines(path);

  float freq = 128.0; // Hz

  float **data = new float *[20];
  for (int k = 0; k < 20; k++)
     data[k] = new float[N_lines];

  kin_data.seekg(0);

  // read past the header
  std::getline (kin_data, line);

  for (int k = 0; k < N_lines; k++) {
     for (int p = 0; p < 20; p++) {
        std::getline (kin_data, line, ',');
        data[p][k] = atof(line.c_str());
     }
        std::getline (kin_data, line);
  }

  kin_data.close();

  return data;
}
