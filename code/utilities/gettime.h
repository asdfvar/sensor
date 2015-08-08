#ifndef GETTIME_H
#define GETTIME_H

float gettime(void);

float waitUntil(float dt);

class TIME
{

   public:

      TIME(void);
      TIME (int N);
      ~TIME(void);

      void start(void);
      void end(void);

      double average(void);
      double total_time(void);

   private:

      int N;
      double start_time;
      double total;
};

#endif
