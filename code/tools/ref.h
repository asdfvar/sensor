#ifndef REF_H
#define REF_H

namespace ref {

   void read_reference_headers (
                      const char path[],
                      int *N,
                      float *ref_freq,
                      float *ref_time );

   void read_reference (
                      const char path[],
                      float *ref_data_primary,
                      float *ref_data_secondary,
                      int N);

   int count_ref_lines ( const char path[] );

}

#endif
