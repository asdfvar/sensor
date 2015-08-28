#include "fileio.h"
#include "energy_expenditure.h"
#include "string_utils.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace fio {
 /*
  * Constructor NAME: kinIO
  */
 kinIO::kinIO (const char path[] )
 {

   N          = count_kinetisense_lines( path );
   samp_freq  = 128.0f; // Hz
   kin_data   = read_kinetisense( path );
   total_time = (float)N / samp_freq;

 }

/******************************************************************/

 /*
  * Destructor NAME: kinIO
  */
 kinIO::~kinIO ()
 {

   for (int k = 0; k < 20; k++)
     delete[] kin_data[k];

 }

/******************************************************************/

 /*
  * Function NAME: valid_start_end
  */
 bool kinIO::valid_start_end (float start, float window)
 {
   if ( start + window > total_time ) return false;
   else return true;
 }

/******************************************************************/

 /*
  * Function NAME: access_sens_ax
  */
 float *kinIO::access_sens_ax (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if      (sens_num == 1) return kin_data[0]  + k;
   else if (sens_num == 2) return kin_data[6]  + k;
   else if (sens_num == 3) return kin_data[12] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 /*
  * Function NAME: access_sens_ay
  */
 float *kinIO::access_sens_ay (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if      (sens_num == 1) return kin_data[1]  + k;
   else if (sens_num == 2) return kin_data[7]  + k;
   else if (sens_num == 3) return kin_data[13] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 /*
  * Function NAME: access_sens_az
  */
 float *kinIO::access_sens_az (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if      (sens_num == 1) return kin_data[2]  + k;
   else if (sens_num == 2) return kin_data[8]  + k;
   else if (sens_num == 3) return kin_data[17] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 /*
  * Function NAME: load_sens_ax
  */
 void kinIO::load_sens_ax (float *__restrict__ ax, float time, int sens_num, int N)
 {
   int k_start = (int)(time * samp_freq);

         if (sens_num == 1) for (int k = 0; k < N; k++) ax[k] = sensor1_ax[k_start + k];
    else if (sens_num == 2) for (int k = 0; k < N; k++) ax[k] = sensor2_ax[k_start + k];
    else if (sens_num == 3) for (int k = 0; k < N; k++) ax[k] = sensor3_ax[k_start + k];
 }

/******************************************************************/

 /*
  * Function NAME: load_sens_ay
  */
 void kinIO::load_sens_ay (float *__restrict__ ay, float time, int sens_num, int N)
 {
   int k_start = (int)(time * samp_freq);

         if (sens_num == 1) for (int k = 0; k < N; k++) ay[k] = sensor1_ay[k_start + k];
    else if (sens_num == 2) for (int k = 0; k < N; k++) ay[k] = sensor2_ay[k_start + k];
    else if (sens_num == 3) for (int k = 0; k < N; k++) ay[k] = sensor3_ay[k_start + k];
 }

/******************************************************************/

 /*
  * Function NAME: load_sens_az
  */
 void kinIO::load_sens_az (float *__restrict__ az, float time, int sens_num, int N)
 {
   int k_start = (int)(time * samp_freq);

         if (sens_num == 1) for (int k = 0; k < N; k++) az[k] = sensor1_az[k_start + k];
    else if (sens_num == 2) for (int k = 0; k < N; k++) az[k] = sensor2_az[k_start + k];
    else if (sens_num == 3) for (int k = 0; k < N; k++) az[k] = sensor3_az[k_start + k];
 }

/******************************************************************/

 /*
  * Function NAME: get_total_time
  */
 float kinIO::get_total_time (void)
 {
    return total_time;
 }

/******************************************************************/

 /*
  * Function NAME: write_val
  */
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

 /*
  * Function NAME: write_val
  */
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

 /*
  * Constructor NAME: readRefs
  */
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
    input.read (buffer, length);

    N_refs = 0;

    std::string line;

   for (int k=0; k<length; k++) {
      if (buffer[k] == '\n') N_refs++;
   }

    input.close();

 }
 
/******************************************************************/

 /*
  * Destructor NAME: readRefs
  */
 readRefs::~readRefs (void) {
    delete[] buffer;
 }

/******************************************************************/

 /*
  * Function NAME: get_Nrefs
  */
 int readRefs::get_Nrefs(void) {
    return N_refs;
 }

/******************************************************************/

 /*
  * Function NAME: get_ref_path
  */
 std::string readRefs::get_ref_path(int i_th) {

   if (i_th > N_refs)
   {
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

 /*
  * Constructor NAME: parameters
  */
 parameters::parameters (std::string path) {

    input.open ( path.c_str() );

    tag           = get_parameter_s   ("tag"        );
    time_window   = get_parameter_f   ("time_window"); // seconds to analyze a signal
    freq_range    = get_parameter_f   ("freq_range" ); // Hz
    cutoff_freq   = get_parameter_f   ("cutoff_freq"); // Hz
    samp_freq     = get_parameter_f   ("samp_freq"  ); // Hz
    ref_time      = get_parameter_f   ("ref_time"   ); // reference time for training
    threshold     = get_parameter_f   ("threshold"  );
    sex           = get_parameter_sex ("sex"        );
    age           = get_parameter_f   ("age"        ); // yrs
    weight        = get_parameter_f   ("weight"     ); // kg
    height        = get_parameter_f   ("height"     ); // cm
    data_path     = get_parameter_s   ("data_path"  );
    ref_path      = get_parameter_s   ("ref_path"   ); // used for training
    activity_ID   = get_parameter_s   ("activity_ID"); // used for training
    select_sensor = get_parameter_i   ("sensor"     ); // which sensor to use

    b_tag         = (tag         != "-1")  ? true : false;
    b_time_window = (time_window >= 0.0f)  ? true : false;
    b_freq_range  = (freq_range  >= 0.0f)  ? true : false;
    b_cutoff_freq = (cutoff_freq >= 0.0f)  ? true : false;
    b_samp_freq   = (samp_freq   >= 0.0f)  ? true : false;
    b_ref_time    = (ref_time    >= 0.0f)  ? true : false;
    b_threshold   = (threshold   >= 0.0f)  ? true : false;
    b_sex         = (sex         != -1  )  ? true : false;
    b_age         = (age         >= 0.0f)  ? true : false;
    b_weight      = (weight      >= 0.0f)  ? true : false;
    b_height      = (height      >= 0.0f)  ? true : false;
    b_data_path   = (data_path   != "-1")  ? true : false;
    b_ref_path    = (ref_path    != "-1")  ? true : false;
    b_activity_ID = (activity_ID != "-1")  ? true : false;
    b_select_sensor = (select_sensor >= 0) ? true : false;

    input.close();

    // defaults
    if ( !b_select_sensor ) select_sensor = 2;

    if (b_samp_freq) dt = 1.0f / samp_freq; else dt = -1.0f; // seconds
    b_taper        = (b_cutoff_freq) ? true : false;

 }

/******************************************************************/

 /*
  * Function NAME: print
  */
 void parameters::print (void)
 {

    std::cout << std::endl;
    std::cout << "Parameters:" << std::endl;
    if (b_tag)         std::cout << "tag         = " << tag         << std::endl;
    if (b_time_window) std::cout << "time_window = " << time_window << std::endl;
    if (b_freq_range)  std::cout << "freq_range  = " << freq_range  << std::endl;
    if (b_cutoff_freq) std::cout << "cutoff_freq = " << cutoff_freq << std::endl;
    if (b_samp_freq)   std::cout << "samp_freq   = " << samp_freq   << std::endl;
    if (b_ref_time)    std::cout << "ref_time    = " << ref_time    << std::endl;
    if (b_threshold)   std::cout << "threshold   = " << threshold   << std::endl;
    if (b_sex)         std::cout << "sex         = " << sex         << std::endl;
    if (b_age)         std::cout << "age         = " << age         << std::endl;
    if (b_weight)      std::cout << "weight      = " << weight      << std::endl;
    if (b_height)      std::cout << "height      = " << height      << std::endl;
    if (b_data_path)   std::cout << "data_path   = " << data_path   << std::endl;
    if (b_ref_path)    std::cout << "ref_path    = " << ref_path    << std::endl;
    if (b_activity_ID) std::cout << "activity_ID = " << activity_ID << std::endl;
    if (b_samp_freq)   std::cout << "dt          = " << dt          << std::endl;
    if (b_taper)       std::cout << "applying data smoothing"       << std::endl;
                       std::cout << "Kinetisense sensor " << select_sensor << std::endl;
    std::cout << std::endl;

 }

/******************************************************************/

 /*
  * Function NAME: get_parameter_f
  */
 float parameters::get_parameter_f (std::string parameter)
 {

    parameter = trim( parameter );

    input.clear();
    input.seekg(0);

    std::string line;
    std::string inp_parameter;
    std::string value;

    do {

       std::getline (input, line);

       inp_parameter = parse_string (line, "=", 0);
       inp_parameter = trim( inp_parameter );

    } while (parameter != inp_parameter && !input.eof());


    if (input.eof())
    {
       std::cout << parameter << " not found" << std::endl;
       return -1.0;

    } else {

       value = parse_string (line, "=", 1);
       value = trim (value);
       return atof(value.c_str());

    }

    return -1.0;
 }

/******************************************************************/

 /*
  * Function NAME: get_parameter_i
  */
 int parameters::get_parameter_i (std::string parameter)
 {

    parameter = trim( parameter );

    input.clear();
    input.seekg(0, input.beg);

    std::string line;
    std::string inp_parameter;
    std::string value;

    do {

       std::getline (input, line);
       inp_parameter = parse_string (line, "=", 0);
       inp_parameter = trim( inp_parameter );

    } while (parameter != inp_parameter && !input.eof());

    if (input.eof())
    {

       std::cout << parameter << " not found" << std::endl;
       return -1;

    } else {

       value = parse_string (line, "=", 1);
       value = trim (value);
       return atoi(value.c_str());

    }

    return -1;
 }

/******************************************************************/

 /*
  * Function NAME: get_parameter_s
  */
 std::string parameters::get_parameter_s (std::string parameter)
 {

    parameter = trim( parameter );

    input.clear();
    input.seekg(0, input.beg);

    std::string line;
    std::string inp_parameter;
    std::string value;

    do {

       std::getline (input, line);
       inp_parameter = parse_string (line, "=", 0);
       inp_parameter = trim( inp_parameter );

    } while (parameter != inp_parameter && !input.eof());

    if (input.eof())
    {

       std::cout << parameter << " not found" << std::endl;
       return "-1";

    } else {

       value = parse_string (line, "=", 1);
       value = trim (value);
       return value;

    }

    return "-1";
 }

/******************************************************************/

 /*
  * Function NAME: get_parameter_sex
  */
 int parameters::get_parameter_sex (std::string parameter)
 {

    parameter = trim( parameter );

    input.clear();
    input.seekg(0, input.beg);

    std::string line;
    std::string inp_parameter;
    std::string value;

    do {

       std::getline (input, line);
       inp_parameter = parse_string (line, "=", 0);
       inp_parameter = trim( inp_parameter );

    } while (parameter != inp_parameter && !input.eof());

    if (input.eof())
    {

       std::cout << parameter << " not found" << std::endl;
       return -1;

    } else {

       value = parse_string (line, "=", 1);
       value = trim (value);

       if (value == "M")
       {
          return MALE;
       }
       else if (value == "F")
       {
          return FEMALE;
       }
       else
       {
          std::cout << "Sex not specified" << std::endl;
          return -1;
       }

    }

    return -1;
 }

/******************************************************************/

 /*
  * Function NAME: get_dt
  */
 float parameters::get_dt (void)
 {
    return dt;
 }

/******************************************************************/

 /*
  * Function NAME: get_samp_freq
  */
 float parameters::get_samp_freq (void)
 {
    return samp_freq;
 }

/******************************************************************/

 /*
  * Function NAME: get_N_window
  */
 int parameters::get_N_window (void)
 {
    return (int)(samp_freq * time_window);
 }

/******************************************************************/

 /*
  * Function NAME: get_N_window_ref
  */
 int parameters::get_N_window_ref (void)
 {
    return (int)(samp_freq * ref_time);
 }

/******************************************************************/

 /*
  * Function NAME: Do_taper
  */
 bool parameters::Do_taper (void)
 {
    return b_taper;
 }

/******************************************************************/

 /*
  * Function NAME: get_freq_range
  */
 float parameters::get_freq_range (void)
 {
    return freq_range;
 }

/******************************************************************/

 /*
  * Function NAME: get_cutoff_freq
  */
 float parameters::get_cutoff_freq (void)
 {
    return cutoff_freq;
 }

/******************************************************************/

 /*
  * Function NAME: get_time_window
  */
 float parameters::get_time_window (void)
 {
    return time_window;
 }

/******************************************************************/

 /*
  * Function NAME: get_time_window_ref
  */
 float parameters::get_time_window_ref (void)
 {
    return ref_time;
 }

/******************************************************************/

 /*
  * Function NAME: get_threashold
  */
 float parameters::get_threshold (void)
 {
    return threshold;
 }

/******************************************************************/

 /*
  * Function NAME: get_sex
  */
 int parameters::get_sex (void)
 {
    return sex;
 }

 /*
  * Function NAME: get_sensor
  */
 int parameters::get_sensor (void)
 {
    return select_sensor;
 }

/******************************************************************/

 /*
  * Function NAME: get_age
  */
 float parameters::get_age (void)
 {
    return age;
 }

/******************************************************************/

 /*
  * Function NAME: get_weight
  */
 float parameters::get_weight (void)
 {
    return weight;
 }

/******************************************************************/

 /*
  * Function NAME: get_height
  */
 float parameters::get_height (void)
 {
    return height;
 }

/******************************************************************/

 /*
  * Function NAME: get_tag
  */
 std::string parameters::get_tag (void)
 {
    return tag;
 }

/******************************************************************/

 /*
  * Function NAME: get_data_path
  */
 std::string parameters::get_data_path (void)
 {
    return data_path;
 }

/******************************************************************/

 /*
  * Function NAME: get_ref_path
  */
 std::string parameters::get_ref_path (void)
 {
    return ref_path;
 }

/******************************************************************/

 /*
  * Function NAME: get_activity_ID
  */
 std::string parameters::get_activity_ID (void)
 {
    return activity_ID;
 }

/******************************************************************/

}
