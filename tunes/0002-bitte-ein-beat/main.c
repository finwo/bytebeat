#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "../../lib/resample.c"

#define  PI   3.14159265358979323846
#define  SR   ((double)8000)
#define  BPM  ((double)185)
#define  BPS  (BPM/((double)60))
#define  SPB  (SR/BPS)

const double kick_gain[]      = {0, PI*2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int    kick_gains       = sizeof(kick_gain) / sizeof(double);

const double bass_gain[] = {0, 2, 1, 0, 0, 0, 0, 0, 0, 0.1, 0.2, 0.3, 0.5, 0.8, 1.3, 2.1, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
const int    bass_gains  = sizeof(bass_gain) / sizeof(double);

double range(const double value[], int values, double d) {
  int    S = floor(d * values);
  double A = (S-1) < 0       ? 0 : value[S - 1];
  double B =                       value[S    ];
  double C = (S+1) >= values ? 0 : value[S + 1];
  double D = (S+2) >= values ? 0 : value[S + 2];
  return resample4(A, B, C, D, (d - ((double)S / values)) * values);
}

int main() {
  uint64_t t         = 0;
  double   sample    = 0;
  double   basetone  = 0;
  double   amplitude = 0;

  double kickPhase = 0;

  for(; t < (SR * 10); t++) {
    sample = 0;

    // "kick"
    kickPhase += (PI*2/SR) * (41.20 + ( (1-sqrt(fmod(t,SPB)/SPB)) * 123.61 ));
    basetone   = tanh(sin(sin(kickPhase) * range(kick_gain, kick_gains, fmod(t,SPB)/SPB)) * 3);
    sample    += basetone * 0.5;

    // Bass line
    basetone  = tanh((
                   sin(((PI*2)/SR)* 41.00*t)      + // E1
                  (sin(((PI*2)/SR)* 82.51*t)*0.5)   // E2
                ) * range(bass_gain, bass_gains, fmod(t,SPB)/SPB));
    sample += basetone * 0.5;

    putchar((unsigned char)((sample * 127) + 128));
  }

  return 0;
}
