#ifndef _ALIM_SES_H
#define _ALIM_SES_H

#include "Arduino.h"

#define LED  4          // pin pour Led (13 pris par le clk du SPI)
#define ONLED HIGH
#define OFFLED LOW

#define TBLINKON 5
#define TBLINKOFF 2000-TBLINKON

#define ON HIGH
#define OFF LOW

#define SPI_SPEED 4000000 //4000000 // ADUM low power config

#define SPI_INIT  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE0));
#define SPI_START SPI.begin();
#define SPI_OFF   SPI.end();bitClear(DDR_MOSI,MOSI_PIN);bitClear(DDR_CLK,CLK_PIN); //digitalWrite(CSV_PIN,LOW);

#define CLKPIN     5
#define MISOPIN    4
#define MOSIPIN    3

#define PORT_MOSI PORTB
#define PORT_MISO PORTB
#define PORT_CLK  PORTB
#define DDR_MOSI  DDRB
#define DDR_MISO  DDRB
#define DDR_CLK   DDRB


#endif // _ALIM_SES_H   
