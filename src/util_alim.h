#ifndef _UTILALIM_H
#define _UTILALIM_H

#include "Arduino.h"

void spi_Write(byte* data,char port,uint8_t pin);
void dyn_led();
void blink(uint8_t num,uint32_t dly);
void blink(uint8_t num);
char getCh();
char peekCh();
uint16_t getValue();
float getFloatValue();
void printFloat(float val);
void hexPrint8(byte b);
void hexPrint32(byte* data);
void hexPrint24(byte* data);


#endif // _UTILALIM_H