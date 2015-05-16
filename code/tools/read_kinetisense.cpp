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
#include "fileio.h"

namespace fio {
int kinIO::count_kinetisense_lines(
       /* Reads in the file data and counts how many lines of
          data are in the file. */
       const char path[]) /* [I  ] Path to the kinetisense data */
{
   std::string line;
   std::ifstream kin_data;
   kin_data.open (path);

   int N_lines = 0;

   // first line is a header
   std::getline (kin_data, line);

   while (std::getline (kin_data, line)) N_lines++;

   kin_data.close();

   return N_lines;
}

/**********************************************************************/

float **kinIO::read_kinetisense(
          /* Populates the data buffer with the kinetisense csv file data.
             Returns a pointer to hold the data. This will contain the acceleration
             and rotation data in units of Gs (1G = 9.81 m/s/s) and EMG data. There
             are 20 arrays of length N_lines as follows:

   float[0]            -sensor 1 acceleration data in x
   float[1]            -sensor 1 acceleration data in y
   float[2]            -sensor 1 acceleration data in z
   float[3]            -sensor 1 rotation data in x
   float[4]            -sensor 1 rotation data in y
   float[5]            -sensor 1 rotation data in z
   float[6]            -sensor 2 acceleration data in x
   float[7]            -sensor 2 acceleration data in y
   float[8]            -sensor 2 acceleration data in z
   float[9]            -sensor 2 rotation data in x
   float[10]           -sensor 2 rotation data in y
   float[11]           -sensor 2 rotation data in z
   float[12]           -sensor 3 acceleration data in x
   float[13]           -sensor 3 acceleration data in y
   float[14]           -sensor 3 acceleration data in z
   float[15]           -sensor 3 rotation data in x
   float[16]           -sensor 3 rotation data in y
   float[17]           -sensor 3 rotation data in z
   float[18]           -EMG 1
   float[19]           -EMG 2

           */
       const char path[], /* [I  ] File of the kinetisense data */
       const int N_lines) 
{

   std::string header;
   std::string parameter;
   std::string line;
   std::ifstream kin_data;
   kin_data.open (path);

   float freq = 128.0; // Hz

   float **data = new float *[22];
   for (int k = 0; k < 20; k++)
      data[k] = new float[N_lines];

   kin_data.seekg(0);

   // read the header
   std::getline (kin_data, header);

   std::cout << "parsing header:" << std::endl;
   std::cout << header << std::endl;

   int ka_parse = 0;
   int kb_parse = 0;
   for (int index = 0; ka_parse < header.length(); index++)
   {
      kb_parse = header.find(",", ka_parse+1);
      if (kb_parse < header.length())
      {
         parameter = header.substr(ka_parse+1, kb_parse-ka_parse-1);
      }

      if (parameter == " Sensor 1 ax") {
         sensor1_ax = data[index];
      } else if (parameter == " Sensor 1 ay") {
         sensor1_ay = data[index];
      } else if (parameter == " Sensor 1 az") {
         sensor1_az = data[index];
      } else if (parameter == " Sensor 1 wx") {
         sensor1_wx = data[index];
      } else if (parameter == " Sensor 1 wy") {
         sensor1_wy = data[index];
      } else if (parameter == " Sensor 1 wz") {
         sensor1_wz = data[index];
      } else if (parameter == " Sensor 2 ax") {
         sensor2_ax = data[index];
      } else if (parameter == " Sensor 2 ay") {
         sensor2_ay = data[index];
      } else if (parameter == " Sensor 2 az") {
         sensor2_az = data[index];
      } else if (parameter == " Sensor 2 wx") {
         sensor2_wx = data[index];
      } else if (parameter == " Sensor 2 wy") {
         sensor2_wy = data[index];
      } else if (parameter == " Sensor 2 wz") {
         sensor2_wz = data[index];
      } else if (parameter == " Sensor 3 ax") {
         sensor3_ax = data[index];
      } else if (parameter == " Sensor 3 ay") {
         sensor3_ay = data[index];
      } else if (parameter == " Sensor 3 az") {
         sensor3_az = data[index];
      } else if (parameter == " Sensor 3 wx") {
         sensor3_wx = data[index];
      } else if (parameter == " Sensor 3 wy") {
         sensor3_wy = data[index];
      } else if (parameter == " Sensor 3 wz") {
         sensor3_wz = data[index];
      }

      ka_parse = kb_parse;
   }
   
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

/**********************************************************************/

float **kinIO::read_kinetisense( const char path[] ) {

   int N = count_kinetisense_lines( path );

   return read_kinetisense ( path, N );

}
}
