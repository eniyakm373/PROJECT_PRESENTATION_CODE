#include <EEPROM.h>
int fanspeed=0;
#define zero 0
#define low 50
#define low_medium 90
#define high_medium 150
#define high 255
#define EEPROM_ADDR 0x01
int fanbuttonon;
int fanbuttonoff = 0;
String voice;
void setup()
{
  Serial.begin(9600);
  pinMode(13,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  check_load_status();
}
void loop()
{
  int fanbuttonon=digitalRead(13);
  while(Serial.available())
  {
    delay(3);
    char c = Serial.read();
    voice+= c;
  }
  if(voice.length() >0)
  {
    if(voice == "low speed")
    {
      analogWrite(11,low);
      analogWrite(10,0);
      fanspeed=1;
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
    if(voice == "medium speed")
    {
      analogWrite(11,high_medium);
      analogWrite(10,0);
      fanspeed=3;
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
    if(voice == "full speed")
    {
      analogWrite(11,high);
      analogWrite(10,0);
      fanspeed=4;
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
    else if(voice == "turn off the fan")
    {
      analogWrite(11,0);
      analogWrite(10,0);
      fanspeed=0;
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
  voice = "";
  } 
  if(fanbuttonoff==0 && fanbuttonon==1)
  {
    fanspeed++;
    delay(100);
    if (fanspeed == 0)
    {
      analogWrite(11,zero);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
    if (fanspeed == 1)
    {
      analogWrite(11,low);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
      
    }
    if (fanspeed == 2)
    {
      analogWrite(11,low_medium);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
     
    }
    if (fanspeed == 3)
    {
      analogWrite(11,high_medium);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
      
    }
    if (fanspeed == 4)
    {
      analogWrite(11,high);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
    if (fanspeed == 5)
    {
      analogWrite(11,0);
      analogWrite(10,0);
      fanspeed=0;
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }
    }
   fanbuttonoff = fanbuttonon;
   delay(100); 
   
}
void check_load_status()
{
  fanspeed=EEPROM.read(EEPROM_ADDR);
  if (fanspeed == 1)
    {
      analogWrite(11,low);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
      
    }
    if (fanspeed == 2)
    {
      analogWrite(11,low_medium);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
     
    }
    if (fanspeed == 3)
    {
      analogWrite(11,high_medium);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
      
    }
    if (fanspeed == 4)
    {
      analogWrite(11,high);
      analogWrite(10,0);
      EEPROM.update(EEPROM_ADDR,fanspeed);
    }  
}
