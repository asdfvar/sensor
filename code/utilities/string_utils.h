#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <iostream>
#include <stdio.h>

std::string trim ( std::string input_string);

std::string parse_string (
                  std::string input_string,
                  std::string delimiter,
                  unsigned int index);

unsigned int count_delimits (
                  std::string input_string,
                  const char delimiter);

#endif
