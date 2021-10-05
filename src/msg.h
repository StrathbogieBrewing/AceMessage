#ifndef MSG_H
#define MSG_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t id;
  uint8_t data[8];
} msg_t;

uint8_t msg_getID(msg_t *msg);
void msg_setID(msg_t *msg, uint8_t id);

uint8_t msg_getU8(msg_t *msg, uint8_t offset);
void msg_setU8(msg_t *msg, uint8_t offset, uint8_t value);

uint16_t msg_getU16(msg_t *msg, uint8_t offset);
void msg_setU16(msg_t *msg, uint8_t offset, uint16_t value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MSG_H
