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

/*
 *
 * Function NAME: waitUntil
 * 
  Function to wait until the time in dt has passed since the
  last call of this function. If it is the first call of this
  function, return after dt time of calling this function.
*/

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
