#include <SPI.h>
#include "alim_ses.h"
#include "mcp4901.h"
#include "cs5550.h"
#include "util_alim.h"


uint8_t led = LED;

uint16_t volts=0;
uint16_t vAdj=14;
float vFactor=500;
uint16_t aAdj=0;
uint16_t aFactor=7.96;
uint16_t amps=0;

uint16_t voltsB,voltsE,ampsB,ampsE,stepsN,dly;

uint8_t vbuf=0;   // 1 buffered ; 0 unbuffered
uint8_t vga=1;    // 1 gain 1 ; 0 gain 2
uint8_t vshdn=1;  // 1 active ; 0 shutdown

unsigned long tmpBlink = millis();         // temps dernier blink
int  perBlink = 100;
uint8_t savled;


void setup() {

  Serial.begin(115200);
  
  Serial.print("\n+start SPI ");delay(10);
  SPI_START
  SPI_INIT
  Serial.println(" done ");delay(10);

  Serial.print("+start MCP4901 ");delay(10);
  mcp4901_init();
  Serial.println(" done ");delay(10);
 
  Serial.print("+start CS6550 ");delay(10);
  cs5550_init();
  while(1){}
  
  cs5550_calib();
  Serial.println(" done ");delay(10);

}

void loop()
{
  blink(2);
  delay(1000);
  float bid;

  //Serial.print("\n\n\rquoi (F fixe / Vv rampe V / Aa rampe A)?");

  char quoi='\0';
  quoi=inch("\n\n\rquoi (F fixe / Vv rampe V / Aa rampe A)?");
  Serial.println(quoi);

  switch(quoi){
    
    case 'F':
      Serial.print("\nVolts ? ");
      bid=getFloatValue();
      Serial.print("  ");Serial.print(bid);
      volts=(uint16_t)(bid*vFactor);
      Serial.print(" ->");Serial.print(volts);
      
      Serial.print("\n\rmAmps ? ");
      bid=getFloatValue();
      Serial.print("  ");Serial.print(bid);
      amps=(uint16_t)(bid*aFactor);
      Serial.print(" ->");Serial.print(amps);
      
      outAmps(amps);
      outVolts(volts);

      delay(2);

      getValues();


    break;

    case 'V':
    {
      voltsB=0;voltsE=0;stepsN=0;dly=0;

      Serial.print("\ndurée step ?");
      dly=getValue();
      Serial.print("\namps maxi (mA)?");
      bid=getFloatValue();
      amps=(uint16_t)(bid*aFactor);
      Serial.print("\nvolts beg ? ");
      bid=getFloatValue();
      voltsB=(uint16_t)(bid*vFactor);
      Serial.print("\nvolts end ? ");
      bid=getFloatValue();
      voltsE=(uint16_t)(bid*vFactor);
      Serial.print("\nnbre steps ? ");
      stepsN=getValue();

      Serial.println();
      
      if(stepsN==0){break;}
      else { 
        outAmps(amps);
        quoi='\0';      
        while(quoi!=0x1b){
          ramp('V',voltsB,voltsE,stepsN,dly);      
          outVolts(0);delay(dly);
          quoi=peekCh();
        }
      }
    }
    break;

    case 'v':
      ramp('V',voltsB,voltsE,stepsN,dly);
    break;

   case 'A':
    {
      ampsB=0;ampsE=0;stepsN=0;dly=0;

      Serial.print("\ndurée step mS ?");
      dly=getValue();
      Serial.print("\nvolts ?");
      volts=getValue();
      Serial.print("\namps beg ? ");
      bid=getFloatValue();
      ampsB=(uint16_t)(bid*aFactor);
      Serial.print("\nvamps end ? ");
      bid=getFloatValue();
      ampsE=(uint16_t)(bid*aFactor);
      Serial.print("\nnbre steps ? ");
      stepsN=getValue();

      Serial.println();

      outAmps(ampsB);
      outVolts(volts);
      
      if(stepsN==0){break;}
      else {
         while(quoi!=0x1b){
          ramp('A',ampsB,ampsE,stepsN,dly);
          outAmps(0);delay(dly);
          quoi=peekCh();
         }
      }
    }
    break;

    case 'a':
      ramp('A',ampsB,ampsE,stepsN,dly);
    break;

    default:
    break;

  }

}

