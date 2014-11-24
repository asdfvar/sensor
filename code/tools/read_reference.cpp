#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

/**********************************************************************/

int count_ref_lines ( const char path[] ) {

  std::string line;
  std::ifstream ref_file;
  ref_file.open ( path );

  int N_data = 0;

  while (std::getline ( ref_file, line, ',' ) )
     N_data++;

  ref_file.close();

  return N_data;
}

/**********************************************************************/

float *read_reference ( const char path[], const int N )
{

   std::string line;
   std::ifstream ref_file;
   ref_file.open (path);

   float *ref = new float[N];

   ref_file.seekg( 0 );

   for ( int k = 0; k < N; k++ ) {
      std::getline ( ref_file, line, ',' );
      ref[k] = atof ( line.c_str() );
   }

   ref_file.close();

   return ref;
}

/**********************************************************************/

float *read_reference ( const char path[] )
{

   int N = count_ref_lines ( path );
   return read_reference ( path, N );

}

/**********************************************************************/
