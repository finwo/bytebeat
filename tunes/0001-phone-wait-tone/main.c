#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define  PI   3.14159265358979323846
#define  SR   ((double)8000)

int main() {
  uint64_t t      = 0;
  double   sample = 0;
  double   basetone;

  for(; t < (SR * 12); t++) {
    sample = 0;

    basetone = sin(((PI*2)/SR)*425*t);

    // Ringing signal
    if ( (t%((uint64_t)SR*5)) < (SR*1) ) {
      sample   += basetone * 0.3;
    }

    // Busy signal
    /* if ( (t%((uint64_t)SR*1)) < (SR*0.4) ) { */
    /*   sample   += basetone * 0.3; */
    /* } */

    // Output, sample limit = -1..1
    putchar((unsigned char)((sample * 127) + 128));
  }

  return 0;
}
