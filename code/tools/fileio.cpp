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

 float *kinIO::access_sens_ax (float time, int sens_num)
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

 float *kinIO::access_sens_ay (float time, int sens_num)
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

 float *kinIO::access_sens_az (float time, int sens_num)
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

 void kinIO::load_sens_ax (float *__restrict__ ax, float time, int sens_num, int N)
 {
   int k_start = (int)(time * samp_freq);

    if (sens_num == 1)      for (int k=0; k<N; k++) ax[k] = kin_data[0][k + k_start];
    else if (sens_num == 2) for (int k=0; k<N; k++) ax[k] = kin_data[6][k + k_start];
    else if (sens_num == 3) for (int k=0; k<N; k++) ax[k] = kin_data[12][k + k_start];
 }

/******************************************************************/

 void kinIO::load_sens_ay (float *__restrict__ ay, float time, int sens_num, int N)
 {
   int k_start = (int)(time * samp_freq);

    if (sens_num == 1)      for (int k=0; k<N; k++) ay[k] = kin_data[1][k + k_start];
    else if (sens_num == 2) for (int k=0; k<N; k++) ay[k] = kin_data[7][k + k_start];
    else if (sens_num == 3) for (int k=0; k<N; k++) ay[k] = kin_data[13][k + k_start];
 }

/******************************************************************/

 void kinIO::load_sens_az (float *__restrict__ az, float time, int sens_num, int N)
 {
   int k_start = (int)(time * samp_freq);

    if (sens_num == 1)      for (int k=0; k<N; k++) az[k] = kin_data[2][k + k_start];
    else if (sens_num == 2) for (int k=0; k<N; k++) az[k] = kin_data[8][k + k_start];
    else if (sens_num == 3) for (int k=0; k<N; k++) az[k] = kin_data[17][k + k_start];
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

 float inputFile::get_parameter_f(std::string parameter)
 {

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

 int inputFile::get_parameter_i(std::string parameter)
 {

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

 std::string inputFile::get_parameter_s(std::string parameter)
 {

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

 int inputFile::get_parameter_sex(std::string parameter)
 {

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

 parameters::parameters (std::string path) {

    input.open ( path.c_str() );

    tag         = get_parameter_s   ("tag"        );
    time_window = get_parameter_f   ("time_window"); // seconds to analyze a signal
    freq_range  = get_parameter_f   ("freq_range" ); // Hz
    cutoff_freq = get_parameter_f   ("cutoff_freq"); // Hz
    samp_freq   = get_parameter_f   ("samp_freq"  ); // Hz
    ref_time    = get_parameter_f   ("ref_time"   ); // reference time for training
    threshold   = get_parameter_f   ("threshold"  );
    sex         = get_parameter_sex ("sex"        );
    age         = get_parameter_f   ("age"        ); // yrs
    weight      = get_parameter_f   ("weight"     ); // kg
    height      = get_parameter_f   ("height"     ); // cm
    data_path   = get_parameter_s   ("data_path"  );
    ref_path    = get_parameter_s   ("ref_path"   ); // used for training
    activity_ID = get_parameter_s   ("activity_ID"); // used for training

    b_tag         = (tag != "-1")          ? true : false;
    b_time_window = (time_window >= 0.0f)  ? true : false;
    b_freq_range  = (freq_range >= 0.0f)   ? true : false;
    b_cutoff_freq = (cutoff_freq >= 0.0f)  ? true : false;
    b_samp_freq   = (samp_freq >= 0.0f)    ? true : false;
    b_ref_time    = (ref_time >= 0.0f)     ? true : false;
    b_threshold   = (threshold >= 0.0f)    ? true : false;
    b_sex         = (sex != -1)            ? true : false;
    b_age         = (age >= 0.0f)          ? true : false;
    b_weight      = (weight >= 0.0f)       ? true : false;
    b_height      = (height >= 0.0f)       ? true : false;
    b_data_path   = (data_path != "-1")    ? true : false;
    b_ref_path    = (ref_path != "-1")     ? true : false;
    b_activity_ID = (activity_ID != "-1")  ? true : false;

    input.close();

    if (b_samp_freq) dt = 1.0f / samp_freq; else dt = -1.0f; // seconds
    b_taper        = (b_cutoff_freq) ? true : false;
    sens_training   = 2;

 }

/******************************************************************/

 void parameters::print (void)
 {

    std::cout << std::endl;
    if (b_tag)         std::cout << "tag = "         << tag         << std::endl;
    if (b_time_window) std::cout << "time_window = " << time_window << std::endl;
    if (b_freq_range)  std::cout << "freq_range = "  << freq_range  << std::endl;
    if (b_cutoff_freq) std::cout << "cutoff_freq = " << cutoff_freq << std::endl;
    if (b_samp_freq)   std::cout << "samp_freq = "   << samp_freq   << std::endl;
    if (b_ref_time)    std::cout << "ref_time = "    << ref_time    << std::endl;
    if (b_threshold)   std::cout << "threshold = "   << threshold   << std::endl;
    if (b_sex)         std::cout << "sex = "         << sex         << std::endl;
    if (b_age)         std::cout << "age = "         << age         << std::endl;
    if (b_weight)      std::cout << "weight = "      << weight      << std::endl;
    if (b_height)      std::cout << "height = "      << height      << std::endl;
    if (b_data_path)   std::cout << "data_path = "   << data_path   << std::endl;
    if (b_ref_path)    std::cout << "ref_path = "    << ref_path    << std::endl;
    if (b_activity_ID) std::cout << "activity_ID = " << activity_ID << std::endl;
    if (b_samp_freq)   std::cout << "dt = "          << dt          << std::endl;
    if (b_taper)       std::cout << "applying data smoothing"       << std::endl;
                       std::cout << "Kinetisense sensor " << sens_training << std::endl;
    std::cout << std::endl;

 }

/******************************************************************/

 float parameters::get_parameter_f (std::string parameter)
 {

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
       std::cout << parameter << " not found" << std::endl;
       return -1.0;
    } else if (inc==999) {
       std::cout << "Max attempts to read " << parameter << " made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       return atof(value.c_str());
    }

    return -1.0;
 }

/******************************************************************/

 int parameters::get_parameter_i (std::string parameter)
 {

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
       std::cout << parameter << " not found" << std::endl;
       return -1;
    } else if (inc==999) {
       std::cout << "Max attempts to read " << parameter << " made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       return atof(value.c_str());
    }

    return -1;
 }

/******************************************************************/

 std::string parameters::get_parameter_s (std::string parameter)
 {

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
       std::cout << parameter << " not found" << std::endl;
       return "-1";
    } else if (inc==999) {
       std::cout << "Max attempts to read " << parameter << " made" << std::endl;
    } else {
       value = line.substr(delimiter_pos+1, line.length());
       return value;
    }

    return "-1";
 }

/******************************************************************/

 int parameters::get_parameter_sex (std::string parameter)
 {

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
       std::cout << parameter << " not found" << std::endl;
       return -1;
    } else if (inc==999) {
       std::cout << "Max attempts to read " << parameter << " made" << std::endl;
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

 float parameters::get_dt (void)
 {
    return dt;
 }

/******************************************************************/

 float parameters::get_samp_freq (void)
 {
    return samp_freq;
 }

/******************************************************************/

 int parameters::get_N_window (void)
 {
    return (int)(samp_freq * time_window);
 }

/******************************************************************/

 bool parameters::Do_taper (void)
 {
    return b_taper;
 }

/******************************************************************/

 float parameters::get_freq_range (void)
 {
    return freq_range;
 }

/******************************************************************/

 float parameters::get_cutoff_freq (void)
 {
    return cutoff_freq;
 }

/******************************************************************/

 float parameters::get_time_window (void)
 {
    return time_window;
 }

/******************************************************************/

 float parameters::get_threshold (void)
 {
    return threshold;
 }

/******************************************************************/

 int parameters::get_sex (void)
 {
    return sex;
 }

/******************************************************************/

 float parameters::get_age (void)
 {
    return age;
 }

/******************************************************************/

 float parameters::get_weight (void)
 {
    return weight;
 }

/******************************************************************/

 float parameters::get_height (void)
 {
    return height;
 }

/******************************************************************/

 std::string parameters::get_tag (void)
 {
    return tag;
 }

/******************************************************************/

 std::string parameters::get_data_path (void)
 {
    return data_path;
 }

/******************************************************************/

}
