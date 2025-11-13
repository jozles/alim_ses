#include "alim_ses.h"
#include "util_alim.h"
#include "mcp4901.h"
#include "cs5550.h"
#include "Arduino.h"

extern unsigned long tmpBlink;         // temps dernier blink
extern int  perBlink;
extern uint8_t savled;

void dyn_led()
{
if (millis() > (tmpBlink + perBlink)) {
    tmpBlink = millis();
    if (digitalRead(LED) == ONLED) {
      digitalWrite(LED, OFFLED);
      perBlink = TBLINKOFF;
    }
    else {
      digitalWrite(LED, ONLED);
      perBlink = TBLINKON;
    } 
  }
}

void dynBlk(){
  if((millis()-tmpBlink)>1000){     // && bitRead(PORT_LED,BIT_LED)==0){
    bitSet(PORT_LED,BIT_LED);
    tmpBlink=millis();}
  if((millis()-tmpBlink)>100 && bitRead(PORT_LED,BIT_LED)!=0){
    bitClear(PORT_LED,BIT_LED);
    tmpBlink=millis();}
}

void blink(uint8_t num,uint32_t dly)
{
  if(num!=0){
    for(uint8_t i=0;i<num;i++){digitalWrite(LED,HIGH);delay(dly);digitalWrite(LED,LOW);delay(10);}
  }
}

void blink(uint8_t num)
{
  blink(num,10);
}

char inch(const char* data)
{
  if(data!=NULL){Serial.print(data);}
  char a=' ';
  while(a==' '){
    if (Serial.available()) {a=Serial.read();}
    else dynBlk();
  }
  Serial.print(a);Serial.println();
  return a;
}

void spi_Write(byte* data,char port,uint8_t pin)
{
  switch (port){
    case 'A':bitClear(PORT_CSA,pin);break;
    case 'V':bitClear(PORT_CSV,pin);break;
    case 'M':bitClear(PORT_CSM,pin);break;
    default: break;
  }
    SPI.transfer(*data);
    SPI.transfer(*(data+1));
  switch (port){
    case 'A':bitSet(PORT_CSA,pin);break;
    case 'V':bitSet(PORT_CSV,pin);break;
    case 'M':bitSet(PORT_CSM,pin);break;
    default: break;
  }
}

char getCh()
{
  while(!Serial.available()){}
  return Serial.read();
}

char peekCh()
{
  if(Serial.available()){return Serial.read();}
  else {return '\0';}
}


uint16_t getValue()
{
  uint16_t v=0;
  char c='\0';
  while(c!=0x1b){
    while((c<'0' || c>'9') && c!=0x1b){c=inCh();}
    if(c!=0x1b){Serial.print(c);c-='0';v*=10;v+=c;}
  }
  return v;
}

float getFloatValue()
{
  float v=0;
  char c='\0';
  uint8_t decimal=0;
  while(c!=0x1b){
    while(((c<'0' || c>'9') && c!='.') && c!=0x1b){c=inCh();}
    if(c!=0x1b){
      Serial.print(c);
      if(c=='.' && decimal==0){decimal=1;c='\0';}
      else {
        //Serial.print(c);
        c-='0';
        if(decimal==0){
          v*=10;v+=c;
        } else {
          /*float d=0.1;
          for(uint8_t i=0;i<decimal;i++){d*=0.1;}
          v+=c*d;*/
          float v1=c;
          for(uint8_t i=0;i<decimal;i++){v1*=0.1;}
          v+=v1;
          decimal++;
        }
      }
    }
  }
  return v;
}


void hexPrint8(byte b)
{
  if((b&0xF0)==0){Serial.print("0");}
  Serial.print(b,HEX);
}

void hexPrint32(byte* data)
{
  hexPrint24(data);
  hexPrint8(data[3]);
}

void hexPrint24(byte* data)
{
  hexPrint8(data[0]);
  hexPrint8(data[1]);
  hexPrint8(data[2]);
  Serial.print(" ");
}

void printFloat(float val)
{
      char buff[16];
      memset(buff,'0',9);
      dtostrf(val, 3, 4,buff);
      Serial.print(buff);
      Serial.print(" ");
}



