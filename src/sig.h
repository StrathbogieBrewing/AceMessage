#ifndef SIG_H
#define SIG_H

#include "msg.h"
#include "fmt.h"
// #include "AceBus.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define SIG_PRIORITY_HIGHEST  (AceBus_kPriorityHighest  << 8)
// #define SIG_PRIORITY_HIGHHIGH (AceBus_kPriorityHighhigh << 8)
// #define SIG_PRIORITY_HIGHMED  (AceBus_kPriorityHighmed  << 8)
// #define SIG_PRIORITY_MEDHIGH  (AceBus_kPriorityMedhigh  << 8)
// #define SIG_PRIORITY_MEDIUM   (AceBus_kPriorityMedium   << 8)
// #define SIG_PRIORITY_MEDLOW   (AceBus_kPriorityMedlow   << 8)
// #define SIG_PRIORITY_LOWMED   (AceBus_kPriorityLowmed   << 8)
// #define SIG_PRIORITY_LOWLOW   (AceBus_kPriorityLowlow   << 8)
// #define SIG_PRIORITY_LOWEST   (AceBus_kPriorityLowest   << 8)

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

#define SIG_MSG_ID(M) (M & 0x000000FF)

// size includes 1 extra byte for the msg id
#define SIG_SIZE1 0x00000200
#define SIG_SIZE2 0x00000300
#define SIG_SIZE3 0x00000400
#define SIG_SIZE4 0x00000500
#define SIG_SIZE5 0x00000600
#define SIG_SIZE6 0x00000700
#define SIG_SIZE7 0x00000800
#define SIG_SIZE8 0x00000900
#define SIG_MSG_SIZE(M) ((M & 0x0000FF00) >> 8)

#define SIG_DIVU16BY10(X) (((uint32_t)(X) * 6554UL) >> 16L)
#define SIG_DIVU16BY100(X) (((uint32_t)(X) * 655UL) >> 16L)
#define SIG_DIVS16BY10(X) (((int32_t)(X) * 6554L) >> 16L)
#define SIG_DIVS16BY100(X) (((int32_t)(X) * 655L) >> 16L)

uint8_t sig_encode(msg_t *msg, uint32_t sig, int16_t value);
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
