#include <string.h>

#include "fmt.h"

static uint8_t toString(char *str, int16_t value, fmt_t format) {
  uint8_t digit;
  uint8_t enable_digits = 0;
  char *ptr;
  ptr = str;

  uint16_t unsignedValue = (uint16_t)value;
  if((format & FMT_UINT) == 0){
    if (value < 0) {  // do sign
      unsignedValue = (uint16_t)(-value);
      *str++ = '-';
    }
  } else {
    format &= ~FMT_UINT;  // clear unsigned flag
  }

  digit = '0';  // do 10000's
  while (unsignedValue > 9999) {
    unsignedValue -= 10000;
    digit++;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    *str++ = digit;
    enable_digits = 1;
  }
  digit = '0';  // do 1000's
  while (unsignedValue > 999) {
    unsignedValue -= 1000;
    digit++;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    *str++ = digit;
    enable_digits = 1;
  }
  digit = '0';  // do 100's
  while (unsignedValue > 99) {
    unsignedValue -= 100;
    digit++;
  }
  if (format == FMT_MILL) {
    if (enable_digits == 0) {
      *str++ = '0';
    }
    *str++ = '.';
    enable_digits = 1;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    *str++ = digit;
    enable_digits = 1;
  }
  digit = '0';  // do 10's
  while (unsignedValue > 9) {
    unsignedValue -= 10;
    digit++;
  }
  if (format == FMT_CENT) {
    if (enable_digits == 0)
      {*str++ = '0';}
    *str++ = '.';
    enable_digits = 1;
  }
  if ((digit != '0') || (enable_digits != 0) || (format == FMT_2DGT)) {
    *str++ = digit;
    enable_digits = 1;
  }
  digit = '0' + unsignedValue;  // do 1's
  if (format == FMT_DECI) {
    if (enable_digits == 0){
      *str++ = '0';
    }
    *str++ = '.';
  }
  *str++ = digit;
  *str = 0;
  return str - ptr;
}

uint8_t fmt_toString(char *str, int16_t value, fmt_t format){
  if (format == FMT_TIME) {
    int16_t hours = 0;
    while (value >= 60) {
      ++hours;
      value -= 60;
    }
    *str++ = '\"';
    str += toString(str, hours, FMT_2DGT);
    *str++ = ':';
    toString(str, value, FMT_2DGT);
    *str++ = '\"';
  } else if (format == FMT_BOOL) {
    if (value)
      strcpy(str, "true");
    else
      strcpy(str, "false");
  } else if (format == FMT_NULL){
    strcpy(str, "null");
  } else {
    toString(str, value, format);
  }
  return strlen(str);
}
