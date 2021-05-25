#ifndef MSG_H
#define MSG_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
  MSG_UNIT = 0x0000,      // display at least one digit
  MSG_MILLI = 0x1000,     // make fixed point with 3 decimal places
  MSG_CENTI = 0x2000,     // make fixed point with 2 decimal places
  MSG_DECI = 0x3000,      // make fixed point with 1 decimal places
  MSG_TWODIGITS = 0x4000, // display at least two digit
  MSG_TIME = 0x5000,      // display as a time
  MSG_BOOL = 0x6000,      // display as on / off
  MSG_NULL = 0x7000,
};

#define MSG_FMT(M) (M & 0x8000)

enum {
  MSG_BYTE_0 = 0x0000,
  MSG_BYTE_1 = 0x0100,
  MSG_BYTE_2 = 0x0200,
  MSG_BYTE_3 = 0x0300,
  MSG_BYTE_4 = 0x0400,
  MSG_BYTE_5 = 0x0500,
  MSG_BYTE_6 = 0x0600,
  MSG_BYTE_7 = 0x0700,
};

#define MSG_OFFSET(M) ((M & 0x0700) >> 8)

enum {
  MSG_BYTE = 0x0000,
  MSG_WORD = 0x0800
};

#define MSG_SIZE(M) (M & 0x0800)

#define MSG_ID(M) (M & 0x00FF)

typedef struct {
  unsigned char msgID;
  unsigned char data[];
} msg_data_t;

typedef struct {
  const char *name;
  const int pack;
} msg_name_t;

void msg_pack(msg_data_t *data, int pack, int value);
int msg_unpack(msg_data_t *data, const int pack, int *value);
int msg_format(msg_data_t *data, const int pack, char *str);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MESSAGE_H
