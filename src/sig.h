#ifndef SIG_H
#define SIG_H

#include "msg.h"
#include "fmt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SIG_PRIORITY_HIGHEST  (0x0000)
#define SIG_PRIORITY_HIGHHIGH (0x8000)
#define SIG_PRIORITY_HIGHMED  (0xC000)
#define SIG_PRIORITY_MEDHIGH  (0xE000)
#define SIG_PRIORITY_MEDIUM   (0xF000)
#define SIG_PRIORITY_MEDLOW   (0xF800)
#define SIG_PRIORITY_LOWMED   (0xFC00)
#define SIG_PRIORITY_LOWLOW   (0xFE00)
#define SIG_PRIORITY_LOWEST   (0xFF00)

#define SIG_UNIT ((uint32_t)FMT_UNIT << 16)  // display at least one digit
#define SIG_MILL ((uint32_t)FMT_MILL << 16)  // make fixed point with 3 decimal places
#define SIG_CENT ((uint32_t)FMT_CENT << 16)  // make fixed point with 2 decimal places
#define SIG_DECI ((uint32_t)FMT_DECI << 16)  // make fixed point with 1 decimal places
#define SIG_2DGT ((uint32_t)FMT_2DGT << 16)  // display at least two digit
#define SIG_TIME ((uint32_t)FMT_TIME << 16)  // display as a time
#define SIG_BOOL ((uint32_t)FMT_BOOL << 16)  // display as on / off
#define SIG_NULL ((uint32_t)FMT_NULL << 16)
#define SIG_UINT ((uint32_t)FMT_UINT << 16)
#define SIG_FORMAT(M) ((M & 0x00FF0000) >> 16)

#define SIG_OFF0 0x00000000
#define SIG_OFF1 0x01000000
#define SIG_OFF2 0x02000000
#define SIG_OFF3 0x03000000
#define SIG_OFF4 0x04000000
#define SIG_OFF5 0x05000000
#define SIG_OFF6 0x06000000
#define SIG_OFF7 0x07000000
#define SIG_OFFSET(M) ((M & 0x0F000000) >> 24)

#define SIG_BYTE 0x00000000
#define SIG_WORD 0x10000000
#define SIG_SIZE(M) (M & 0x70000000)

#define SIG_RW 0x80000000
#define SIG_RO 0x00000000
#define SIG_ACCESS(M) (M & 0x80000000)

#define SIG_MSG_ID(M) (M & 0x0000FFFF)

void sig_encode(msg_t *msg, uint32_t sig, int16_t value);
fmt_t sig_decode(msg_t *msg, uint32_t sig, int16_t *value);
uint8_t sig_toString(msg_t *msg, uint32_t sig, char *str);

typedef struct {
  const char *name;
  const uint32_t sig;
} sig_name_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SIG_H
