#include <iostream>
#include <fstream>
#include <fstream>
#include <string>

int read_file_paths (const char path[], int line_number, std::string *file_path)
{
   std::string   line;
   std::ifstream fid;
   int N_lines = 0;

   fid.open (path);
   fid.seekg(0);

   while (std::getline (fid, line)) N_lines++;

   fid.close();

   if (line_number >= N_lines) return -1;


   fid.open (path);
   fid.seekg(0);

   std::getline (fid, line);
   for (int k=0; k<line_number; k++) std::getline (fid, line);

   *file_path = line;

   fid.close();

   return 0;
}
