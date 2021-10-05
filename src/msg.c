#include <string.h>

#include "msg.h"

uint8_t msg_getID(msg_t *msg){
  return msg->id;
}

void msg_setID(msg_t *msg, uint8_t id){
  msg->id = id;
}

uint8_t msg_getU8(msg_t *msg, uint8_t offset){
  return msg->data[offset];
}

void msg_setU8(msg_t *msg, uint8_t offset, uint8_t value){
  msg->data[offset] = value;
}

uint16_t msg_getU16(msg_t *msg, uint8_t offset){
  return (((uint16_t)msg->data[offset]) << 8) +
          (uint16_t)msg->data[offset + 1];
}

void msg_setU16(msg_t *msg, uint8_t offset, uint16_t value){
  msg->data[offset] = (value >> 8);
  msg->data[offset + 1] = value;
}
