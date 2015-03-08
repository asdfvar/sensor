#include "fileio.h"
#include "energy_expenditure.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace fio {
 kinIO::kinIO (const char path[] )
 {

   N          = count_kinetisense_lines( path );
   samp_freq  = 128.0; // Hz
   kin_data   = read_kinetisense( path );
   total_time = (float)N / samp_freq;

 }

/******************************************************************/

 kinIO::~kinIO ()
 {

   for (int k = 0; k < 20; k++)
     delete[] kin_data[k];

 }

/******************************************************************/

 bool kinIO::valid_start_end (float start, float window)
 {
   if ( start + window > total_time ) return false;
   else return true;
 }

/******************************************************************/

 float *kinIO::get_sens_ax (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[0] + k;
   else if (sens_num == 2) return kin_data[6] + k;
   else if (sens_num == 3) return kin_data[12] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 float *kinIO::get_sens_ay (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[1] + k;
   else if (sens_num == 2) return kin_data[7] + k;
   else if (sens_num == 3) return kin_data[13] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 float *kinIO::get_sens_az (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[2] + k;
   else if (sens_num == 2) return kin_data[8] + k;
   else if (sens_num == 3) return kin_data[17] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 float kinIO::get_total_time (void)
 {
    return total_time;
 }

/******************************************************************/

 void write_val(float val, std::string out_file_path, bool init)
 {

   std::ofstream out_file;
   if (init) {
      out_file.open (out_file_path.c_str());
      std::cout << "Writing data to " << out_file_path << std::endl;
   } else {
      out_file.open (out_file_path.c_str(), std::ios::app);
   }
   out_file << val << "\n";
   out_file.close();

 }

/******************************************************************/

 void write_val(int val, std::string out_file_path,  bool init)
 {

   std::ofstream out_file;
   if (init) {
      out_file.open (out_file_path.c_str());
   } else {
      out_file.open (out_file_path.c_str(), std::ios::app);
   }
   out_file << val << "\n";
   out_file.close();

 }

/******************************************************************/

 inputFile::inputFile( std::string in_file_in ) {

    std::string in_file = in_file_in;
    input.open ( in_file.c_str() );

 }

/******************************************************************/

 inputFile::~inputFile (void) {
    std::cout << "Closing input file" << std::endl;
    input.close();
 }

/******************************************************************/

 float inputFile::get_parameter_f(std::string parameter) {

    input.seekg(0);

    std::string line;
    std::string inp_parameter;
    std::string delimiter = "=";
    std::string value;
    int delimiter_pos;

    int inc=0;
    do {
       std::getline (input, line);
       delimiter_pos = line.find(delimiter);
       inp_parameter = line.substr(0, delimiter_pos);
       inc++;
    } while (parameter != inp_parameter && !input.eof() && inc<999);

    if (input.eof()) {
       std::cout << "Parameter (float) not found" << std::endl;
       return -1.0;
    } else if (inc==999) {
       std::cout << "Max attempts to read parameter (float) made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       return atof(value.c_str());
    }

    return -1.0;
 }

/******************************************************************/

 int inputFile::get_parameter_i(std::string parameter) {

    input.seekg(0, input.beg);

    std::string line;
    std::string inp_parameter;
    std::string delimiter = "=";
    std::string value;
    int delimiter_pos;

    int inc=0;
    do {
       std::getline (input, line);
       delimiter_pos = line.find(delimiter);
       inp_parameter = line.substr(0, delimiter_pos);
       inc++;
    } while (parameter != inp_parameter && !input.eof() && inc<999);

    if (input.eof()) {
       std::cout << "Parameter (int) not found" << std::endl;
       return -1;
    } else if (inc==999) {
       std::cout << "Max attempts to read parameter (int) made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       return atof(value.c_str());
    }

    return -1;
 }

/******************************************************************/

 std::string inputFile::get_parameter_s(std::string parameter) {

    input.seekg(0, input.beg);

    std::string line;
    std::string inp_parameter;
    std::string delimiter = "=";
    std::string value;
    int delimiter_pos;

    int inc=0;
    do {
       std::getline (input, line);
       delimiter_pos = line.find(delimiter);
       inp_parameter = line.substr(0, delimiter_pos);
       inc++;
    } while (parameter != inp_parameter && !input.eof() && inc<999);

    if (input.eof()) {
       std::cout << "Parameter (string) not found" << std::endl;
       return "-1";
    } else if (inc==999) {
       std::cout << "Max attempts to read parameter (string) made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       return value;
    }

    return "-1";
 }

/******************************************************************/

 int inputFile::get_parameter_sex(std::string parameter) {

    input.seekg(0, input.beg);

    std::string line;
    std::string inp_parameter;
    std::string delimiter = "=";
    std::string value;
    int delimiter_pos;

    int inc=0;
    do {
       std::getline (input, line);
       delimiter_pos = line.find(delimiter);
       inp_parameter = line.substr(0, delimiter_pos);
       inc++;
    } while (parameter != inp_parameter && !input.eof() && inc<999);

    if (input.eof()) {
       std::cout << "Parameter (int) not found" << std::endl;
       return -1;
    } else if (inc==999) {
       std::cout << "Max attempts to read parameter (int) made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       if (value == "M")
          return MALE;
       else if (value == "F")
          return FEMALE;
       else {
          std::cout << "Sex not specified" << std::endl;
          return -1;
       }
    }

    return -1;
 }


/******************************************************************/

 readRefs::readRefs (std::string in_file)
 {

    std::ifstream input;
    input.open ( in_file.c_str() );

    // get length of file:
    input.seekg (0, input.end);
    length = input.tellg();
    input.seekg (0, input.beg);

    // allocate memory:
    buffer = new char [length];

    // read data as a block:
    input.read (buffer,length);

    N_refs = 0;

    std::string line;

   for (int k=0; k<length; k++) {
      if (buffer[k] == '\n') N_refs++;
   }

    input.close();

 }
 
/******************************************************************/

 readRefs::~readRefs (void) {
    delete[] buffer;
 }

/******************************************************************/

 int readRefs::get_Nrefs(void) {
    return N_refs;
 }

/******************************************************************/

 std::string readRefs::get_ref_path(int i_th) {

   if (i_th > N_refs) {
      std::cout << "Attempting to get reference "
                   "at line " << i_th << " but there "
                   "are only " << N_refs << " references."
                << std::endl;
      return "\0";
   }

   std::string line;
   int nln    = 1;
   int k_char = 0;

   for (k_char=0; k_char<length && nln < i_th; k_char++) {
      if (buffer[k_char] == '\n') nln++;
   }

   for (; k_char<length && buffer[k_char] != '\n'; k_char++) {
      if (buffer[k_char] != '\r') line.push_back (buffer[k_char]);
   }

   return line;
 }

/******************************************************************/

}
