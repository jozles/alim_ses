#ifndef _MCP4901_H
#define _MCP4901_H

#include "Arduino.h"
#include <SPI.h>

#define CSA_PIN    1          // pin pour CSA du nrf
#define CSV_PIN    2          // pin pour CS du SPI

#define PORT_PWR_MCP PORTD
#define DDR_PWR_MCP DDRD
#define BIT_PWR_MCP 7
#define POWER_ON_MCP bitSet(DDR_PWR_MCP,BIT_PWR_MCP);bitClear(PORT_PWR_MCP,BIT_PWR_MCP);
#define POWER_OFF_MCP bitSet(PORT_PWR_MCP,BIT_PWR_MCP);

#define PORT_CSV  PORTB
#define PORT_CSA  PORTB

#define DDR_CSV   DDRB
#define DDR_CSA   DDRB

#define CSA_INIT   bitSet(DDR_CSA,CSA_PIN); //pinMode(CSA_PIN,OUTPUT);
#define CSA_OFF    bitClear(DDR_CSA,CSA_PIN); //pinMode(CSA_PIN,INPUT);
#define CSV_INIT  bitSet(DDR_CSV,CSV_PIN); //pinMode(CSV_PIN,OUTPUT);
#define CSV_OFF   bitClear(DDR_CSV,CSV_PIN); //pinMode(CSV_PIN,INPUT);
#define CSA_HIGH   bitSet(PORT_CSA,CSA_PIN); //digitalWrite(CSA_PIN,HIGH);
#define CSA_LOW    bitClear(PORT_CSA,CSA_PIN); //digitalWrite(CSA_PIN,LOW);
#define CSV_HIGH  bitSet(PORT_CSV,CSV_PIN); //digitalWrite(CSV_PIN,HIGH);
#define CSV_LOW   bitClear(PORT_CSV,CSV_PIN); //digitalWrite(CSV_PIN,LOW);




#define BUF 14
#define GA  13
#define SHDN 12


void mcp4901_init();
void ramp(char what,uint16_t valB,uint16_t valE,uint16_t stepsN,uint32_t dly);
void outVolts( uint16_t val);
void outAmps( uint16_t val);

#endif // _MCP4901_H


