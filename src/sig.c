#include "sig.h"

void sig_encode(msg_t *msg, uint32_t sig, int16_t value){
  msg_setID(msg, SIG_MSG_ID(sig));
  uint8_t offset = SIG_OFFSET(sig);
  if (SIG_SIZE(sig) == SIG_BYTE) {
    msg_setU8(msg, offset, value);
  }
  if (SIG_SIZE(sig) == SIG_WORD) {
    msg_setU16(msg, offset, value);
  }
}

fmt_t sig_decode(msg_t *msg, uint32_t sig, int16_t *value){
  if (msg_getID(msg) != SIG_MSG_ID(sig)) {
    return FMT_NULL;
  }
  uint8_t offset = SIG_OFFSET(sig);
  if (SIG_SIZE(sig) == SIG_BYTE) {
    *value = (int8_t)msg_getU8(msg, offset);
  } else if (SIG_SIZE(sig) == SIG_WORD) {
    *value = msg_getU16(msg, offset);
  } else {
    return FMT_NULL;
  }
  return SIG_FORMAT(sig);
}

uint8_t sig_toString(msg_t *msg, uint32_t sig, char *str){
  int16_t value;
  fmt_t format = sig_decode(msg, sig, &value);
  return fmt_toString(str, value, format);
}

  // if (format == SIG_TIME) {
  //   int16_t hours = 0;
  //   while (value >= 60) {
  //     ++hours;
  //     value -= 60;
  //   }
  //   str += fmt_toString(str, FMT_2DGT, hours);
  //   *str++ = ':';
  //   fmt_toString(str, FMT_2DGT, value);
  // } else if (format == SIG_BOOL) {
  //   if (value)
  //     strcpy(str, "true");
  //   else
  //     strcpy(str, "false");
  // } else {
  //   toString(str, format, value);
  // }
  // return strlen(str);
// }

// int msg_format(msg_t *msg, const int pack, char *str) {
//   int value;
//   int format = msg_unpack(data, pack, &value);
//   if (format == SIG_TIME) {
//     int hours = 0;
//     while (value >= 60) {
//       ++hours;
//       value -= 60;
//     }
//     str += _itoa(str, SIG_TWODIGITS, hours);
//     *str++ = ':';
//     _itoa(str, SIG_TWODIGITS, value);
//   } else if (format == SIG_BOOL) {
//     if (value)
//       strcpy(str, "true"); // compatible with json
//     else
//       strcpy(str, "false");
//   } else {
//     _itoa(str, format, value);
//   }
//   return strlen(str);
// }

// void msg_pack(msg_t *msg, const int pack, int value) {
//   msg->id = SIG_SIG_ID(pack);
//   unsigned char byteOffset = SIG_OFFSET(pack);
//   if (SIG_SIZE(pack) == SIG_BYTE) {
//     msg->data[byteOffset] = value;
//   }
//   if (SIG_SIZE(pack) == SIG_WORD) {
//     msg->data[byteOffset] = (value >> 8);
//     msg->data[byteOffset + 1] = value;
//   }
// }
//
// int msg_unpack(msg_t *msg, const int pack, int *value) {
//   if (msg->id != SIG_ID(pack)) {
//     return SIG_NULL;
//   }
//   unsigned char byteOffset = SIG_OFFSET(pack);
//   if (SIG_SIZE(pack) == SIG_BYTE) {
//     *value = (int)((signed char)msg->data[byteOffset]);
//   } else if (SIG_SIZE(pack) == SIG_WORD) {
//     *value = ((int)((signed char)msg->data[byteOffset]) << 8) +
//              msg->data[byteOffset + 1];
//   } else {
//     return SIG_NULL;
//   }
//   return SIG_FMT(pack);
// }

// void msg_pack(msg_t *msg, msg_pack_t *pack, int value) {
//   msg->id = pack->id;
//   unsigned char byteOffset = pack->bitOffset >> 3;
//   if (pack->bitCount == 8) {
//     msg->data[byteOffset] = value;
//   }
//   if (pack->bitCount == 16) {
//     msg->data[byteOffset] = (value >> 8);
//     msg->data[byteOffset + 1] = value;
//   }
// }
