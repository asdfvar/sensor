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

/*
 * Function NAME: parse_string
 */
static std::string parse_string (
                  std::string input_string,
                  unsigned int index)
{
   unsigned int ka_parse = 0;
   unsigned int kb_parse = 0;

   for (unsigned int k = 0; k <= index; k++)
   {
      ka_parse = kb_parse;
      kb_parse = input_string.find(",", ka_parse + 1);
   }

   if (ka_parse == kb_parse)
   {
      std::cout << __FILE__ << ":" << __LINE__ << ":"
                << "Invalid index" << std::endl;
      return "-1";
   }

   if (index == 0)
   {
      return input_string.substr(ka_parse, kb_parse - ka_parse);
   }
   else
   {
      return input_string.substr(ka_parse + 1, kb_parse - ka_parse - 1);
   }

}

/*
 * Function NAME: count_delimits
 */
static unsigned int count_delimits (
                  std::string input_string,
                  const char delimiter)
{
   unsigned int count = 0;
   for (unsigned int k = 0; k < input_string.length(); k++)
   {
//std::cout << input_string[k] << std::endl;
      if (input_string[k] == delimiter) count++;
   }

   return count;
}

namespace fio {

/*
 * Function NAME: count_kinetisense_lines
 */
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

/*
 * Function NAME: read_kinetisense
 *
 * Populates the data buffer with the kinetisense csv file data.
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
float **kinIO::read_kinetisense(
       const char path[], /* [I  ] File of the kinetisense data */
       const int N_lines) 
{

   std::string header;
   std::string parameter;
   std::string data_string;
   std::string line;
   std::ifstream kin_data;
   kin_data.open (path);

   kin_data.seekg(0);

   /*
   **  Read the header
   */

   std::getline (kin_data, header);

   std::cout << "parsing header:" << std::endl;
   std::cout << header << std::endl;

   std::string stuff;

   unsigned int num_params = count_delimits(header, ',') + 1;

   float **data = new float *[num_params];
   for (unsigned int k = 0; k < num_params; k++)
   {
      data[k] = new float[N_lines];
   }

   for (unsigned int index = 0; index < num_params; index++)
   {
      parameter = parse_string ( header, index );

      /*
      ** Alias to the appropriate sensor
      */
      if (parameter == "Sensor 1 ax") {
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

   }
   
   for (int k = 0; k < N_lines; k++) {

      std::getline (kin_data, line);

      for (unsigned int index = 0; index < num_params; index++) {
         data_string    = parse_string ( line, index );
         data[index][k] = atof(data_string.c_str());
      }

   }

   kin_data.close();

   return data;
}

/**********************************************************************/

/*
 * Function NAME: read_kinetisense
 */
float **kinIO::read_kinetisense( const char path[] )
{

   int N = count_kinetisense_lines( path );

   return read_kinetisense ( path, N );

}

}
