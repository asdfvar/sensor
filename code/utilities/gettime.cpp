#include "gettime.h"
#include <time.h>
#include <sys/time.h>
#include <iostream>

#define SEC 2.0

/*
  returns the time in seconds between this call
  and the previous call of this function
*/

/*
 * Function NAME: gettime
 */
float gettime(void)
{

   static bool init_done = false;
   static struct timeval start, end;
   float dt;

   if (!init_done) {
      gettimeofday(&start, NULL);
      gettimeofday(&end,   NULL);
      init_done = true;
   }

   // update the delta time dt

   gettimeofday(&end, NULL);
   dt = (float)((end.tv_sec*1000000 + end.tv_usec) -
        (start.tv_sec*1000000 + start.tv_usec))/1000000.0;

   gettimeofday(&start, NULL);

   return dt;
}

/**
 ** Function NAME: waitUntil
 ** 
 **  Function to wait until the time in dt has passed since the
 **  last call of this function. If it is the first call of this
 **  function, return after dt time of calling this function.
 **/

float waitUntil(float dt)
{

   static bool init_done = false;
   static struct timeval start, end;
   float currentDt;

   if (!init_done) {
      gettimeofday(&start, NULL);
      gettimeofday(&end,   NULL);
      init_done = true;
   }

   do {
   gettimeofday(&end,   NULL);
   currentDt = (float)((end.tv_sec*1000000 + end.tv_usec) -
        (start.tv_sec*1000000 + start.tv_usec))/1000000.0;
   } while (currentDt < dt);

   gettimeofday(&start, NULL);

   return currentDt;
}

TIME::TIME (int N_in)
{

  N = N_in;
  total = 0.0;

}

TIME::TIME (void)
{

  N = 0;
  total = 0.0;

}

TIME::~TIME (void)
{
   std::cout << "Total time " << total << std::endl;
}

void TIME::start (void)
{
   struct timeval time_struct;
   gettimeofday(&time_struct, NULL);

   start_time = time_struct.tv_sec + time_struct.tv_usec * 1.0e-6;

}

void TIME::end (void)
{
   struct timeval time_struct;
   gettimeofday(&time_struct, NULL);

   N++;
   if (N > 0)
   {
      double current = time_struct.tv_sec + time_struct.tv_usec * 1.0e-6;
      total += current - start_time;
   }
}

double TIME::average (void)
{
   double average = total / (double)N;

   return average;
}

double TIME::total_time (void)
{
   return total;
}
