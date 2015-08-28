#include "string_utils.h"

/*
** on NAME: parse_string
 */
std::string parse_string (
                  std::string input_string,
                  std::string delimiter,
                  unsigned int index)
{
   unsigned int ka_parse = 0;
   unsigned int kb_parse = 0;

   for (unsigned int k = 0; k <= index; k++)
   {
      ka_parse = kb_parse;
      kb_parse = input_string.find( delimiter, ka_parse + 1);
   }

   if (ka_parse == kb_parse)
   {
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
** Function NAME: trim
*/
std::string trim ( std::string input_string)
{
   unsigned int start, end;

   if (input_string.length() == 0) return "";

   for (start = 0;
           start < input_string.length() && (input_string[start] == '\n' || input_string[start] == ' ');
              start++) {}

   if (start >= input_string.length()) start--;

   for (end = input_string.length() - 1;
           end > 0 && (input_string[end] == '\n' || input_string[end] == ' ');
              end--) {}

   return input_string.substr(start, end - start + 1);
}

/*
 * Function NAME: count_delimits
 */
unsigned int count_delimits (
                  std::string input_string,
                  const char delimiter)
{
   unsigned int count = 0;
   for (unsigned int k = 0; k < input_string.length(); k++)
   {
      if (input_string[k] == delimiter) count++;
   }

   return count;
}
