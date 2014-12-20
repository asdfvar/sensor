#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

namespace ref {
/**********************************************************************/

void read_reference_headers (
                     const char path[],
                     int *ref_N,
                     float *ref_freq,
                     float *ref_time )
 {

   std::string line;
   std::string name;
   std::string value;
   std::string delimiter = "=";
   std::ifstream ref_file;

   ref_file.open (path);
   ref_file.seekg( 0 );

   // read the headers
   std::getline ( ref_file, line );

   name = line.substr(0, line.find(delimiter));
   value = line.substr(line.find(delimiter)+1, line.length() );
   if (name.compare("N ") == 0) *ref_N = atoi(value.c_str());
   else if (name.compare("frequency ") == 0) *ref_freq = atof(value.c_str());
   else if (name.compare("time ") == 0) *ref_time = atof(value.c_str());

   std::getline ( ref_file, line );

   name = line.substr(0, line.find(delimiter));
   value = line.substr(line.find(delimiter)+1, line.length() );
   if (name.compare("N ") == 0) *ref_N = atoi(value.c_str());
   else if (name.compare("frequency ") == 0) *ref_freq = atof(value.c_str());
   else if (name.compare("time ") == 0) *ref_time = atof(value.c_str());

   std::getline ( ref_file, line );

   name = line.substr(0, line.find(delimiter));
   value = line.substr(line.find(delimiter)+1, line.length() );
   if (name.compare("N ") == 0) *ref_N = atoi(value.c_str());
   else if (name.compare("frequency ") == 0) *ref_freq = atof(value.c_str());
   else if (name.compare("time ") == 0) *ref_time = atof(value.c_str());

   ref_file.close();

 }

/**********************************************************************/

void read_reference (const char path[],
                     float *ref_data_primary,
                     float *ref_data_secondary,
                     int N)
 {


   std::string line;
   std::ifstream ref_file;

   ref_file.open (path);
   ref_file.seekg(0);

   // read past the headers
   std::getline ( ref_file, line );
   std::getline ( ref_file, line );
   std::getline ( ref_file, line );

   for ( int k = 0; k < N; k++ ) {
      std::getline ( ref_file, line, ',' );
      ref_data_primary[k] = atof ( line.c_str() );
   }

   ref_file.seekg(0);
   // read past the headers and first reference data
   std::getline ( ref_file, line );
   std::getline ( ref_file, line );
   std::getline ( ref_file, line );
   std::getline ( ref_file, line );

   for ( int k = 0; k < N; k++ ) {
      std::getline ( ref_file, line, ',' );
      ref_data_secondary[k] = atof ( line.c_str() );
   }

   ref_file.close();
 }
}
