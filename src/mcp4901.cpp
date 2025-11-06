#include "Arduino.h"
#include <SPI.h>    
#include "mcp4901.h"
#include "alim_ses.h"   
#include "util_alim.h"

extern uint16_t volts;
extern uint16_t vAdj;
extern float vFactor;
extern uint16_t aAdj;
extern uint16_t aFactor;
extern uint16_t amps;

extern uint8_t vbuf;   // 1 buffered ; 0 unbuffered
extern uint8_t vga;    // 1 gain 1 ; 0 gain 2
extern uint8_t vshdn;  // 1 active ; 0 shutdown

void outVolts( uint16_t val)
{
  byte value[2];
  val+=vAdj;
  value[0]=val>>8;
  value[1]=val&0xff;
  
  value[0] |= (vbuf<<(BUF-8)) | (vga<<(GA-8)) | (vshdn<<(SHDN-8)) ;

  spi_Write(value,'V',CSV_PIN);
}

void outAmps( uint16_t val)
{
  byte value[2];
  val+=aAdj;
  value[0]=val>>8;
  value[1]=val&0xff;
  
  value[0] |= (vbuf<<(BUF-8)) | (vga<<(GA-8)) | (vshdn<<(SHDN-8)) ;

  spi_Write(value,'A',CSA_PIN);
}

void mcp4901_init()
{
 POWER_ON_MCP
  delay(100);

  CSA_INIT
  CSV_INIT
  CSV_HIGH
  CSA_HIGH
  
  uint16_t val=0; //0x0db0;      //x0ffe;
  outVolts(val);

  Serial.print("(");Serial.print(vAdj);
  Serial.print(") aAdj Volts ? ");
  vAdj=getValue();

  Serial.print("  (");Serial.print(aAdj);
  Serial.print(") Adj Amps ? ");
  aAdj=getValue();

}

void ramp(char what,uint16_t valB,uint16_t valE,uint16_t stepsN,uint32_t dly)
{
  int16_t step=0;

  if(valB<valE){step=(valE-valB)/stepsN;}
  else {step=-((valB-valE)/stepsN);}
      /*  
        Serial.print(" valB=");Serial.print(valB);
        Serial.print(" valE=");Serial.print(valE);
        Serial.print(" step=");Serial.println(step);
      */ 
        uint16_t val=valB;
        for(uint8_t i=0;i<=stepsN;i++){
          //Serial.print(val);Serial.print(' ');
          if(what=='V'){outVolts(val);}
          else {outAmps(val);}
          //delay(dly);
          blink(1,dly);
          val+=step;
        }
}