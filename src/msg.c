#include <string.h>

#include "msg.h"

// void msg_pack(msg_data_t *data, msg_pack_t *pack, int value) {
//   data->msgID = pack->msgID;
//   unsigned char byteOffset = pack->bitOffset >> 3;
//   if (pack->bitCount == 8) {
//     data->data[byteOffset] = value;
//   }
//   if (pack->bitCount == 16) {
//     data->data[byteOffset] = (value >> 8);
//     data->data[byteOffset + 1] = value;
//   }
// }

void msg_pack(msg_data_t *data, const int pack, int value) {
  data->msgID = MSG_ID(pack);
  unsigned char byteOffset = MSG_OFFSET(pack);
  if (MSG_SIZE(pack) == MSG_BYTE) {
    data->data[byteOffset] = value;
  }
  if (MSG_SIZE(pack) == MSG_WORD) {
    data->data[byteOffset] = (value >> 8);
    data->data[byteOffset + 1] = value;
  }
}

int msg_unpack(msg_data_t *data, const int pack, int *value) {
  if (data->msgID != MSG_ID(pack)) {
    return MSG_NULL;
  }
  unsigned char byteOffset = MSG_OFFSET(pack);
  if (MSG_SIZE(pack) == MSG_BYTE) {
    *value = (int)((signed char)data->data[byteOffset]);
  } else if (MSG_SIZE(pack) == MSG_WORD) {
    *value = ((int)((signed char)data->data[byteOffset]) << 8) +
             data->data[byteOffset + 1];
  } else {
    return MSG_NULL;
  }
  return MSG_FMT(pack);
}

int _itoa(char *str, int format, int value) {
  unsigned char digit;
  unsigned char enable_digits = 0;
  char *ptr;
  ptr = str;
  // do sign
  if (value < 0) {
    value = -value;
    *str++ = '-';
  }
  // do 10000's
  digit = '0';
  while (value > 9999) {
    value -= 10000;
    digit++;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    *str++ = digit;
    enable_digits = 1;
  }
  // do 1000's
  digit = '0';
  while (value > 999) {
    value -= 1000;
    digit++;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    *str++ = digit;
    enable_digits = 1;
  }
  // do 100's
  digit = '0';
  while (value > 99) {
    value -= 100;
    digit++;
  }
  if (format == MSG_MILLI) {
    if (enable_digits == 0)
      *str++ = '0';
    *str++ = '.';
    enable_digits = 1;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    *str++ = digit;
    enable_digits = 1;
  }
  // do 10's
  digit = '0';
  while (value > 9) {
    value -= 10;
    digit++;
  }
  if (format == MSG_CENTI) {
    if (enable_digits == 0)
      *str++ = '0';
    *str++ = '.';
    enable_digits = 1;
  }
  if ((digit != '0') || (enable_digits != 0) || (format == MSG_TWODIGITS)) {
    *str++ = digit;
    enable_digits = 1;
  }
  // do 1's
  digit = '0' + value;
  if (format == MSG_DECI) {
    if (enable_digits == 0)
      *str++ = '0';
    *str++ = '.';
  }
  *str++ = digit;
  *str = 0;

  return str - ptr;
}

int msg_format(msg_data_t *data, const int pack, char *str) {
  int value;
  int format = msg_unpack(data, pack, &value);
  if (format == MSG_TIME) {
    int hours = 0;
    while (value >= 60) {
      ++hours;
      value -= 60;
    }
    str += _itoa(str, MSG_TWODIGITS, hours);
    *str++ = ':';
    _itoa(str, MSG_TWODIGITS, value);
  } else if (format == MSG_BOOL) {
    if (value)
      strcpy(str, "true"); // compatible with json
    else
      strcpy(str, "false");
  } else {
    _itoa(str, format, value);
  }
  return strlen(str);
}
