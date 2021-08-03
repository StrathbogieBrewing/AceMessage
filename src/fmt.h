#ifndef FMT_H
#define FMT_H

#include <stdint.h>

typedef enum {
  FMT_UNIT = 0, // display at least one digit
  FMT_MILL,     // make fixed point with 3 decimal places
  FMT_CENT,     // make fixed point with 2 decimal places
  FMT_DECI,     // make fixed point with 1 decimal places
  FMT_2DGT,     // display at least two digit
  FMT_TIME,     // display as a time
  FMT_BOOL,     // display as on / off
  FMT_NULL
} fmt_t;

#define FMT_MAXSTRLEN (8)

uint8_t fmt_toString(char *str, int16_t value, fmt_t format);

#endif // FMT_H
