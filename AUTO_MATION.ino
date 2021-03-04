#define zero 0
#define low 90
#define medium 150
#define high 255
#include <DHT.h>
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
int t;
int count=0;
boolean state1;
boolean state2;
int i=1;
void setup()
{
  
  dht.begin();
  Serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,INPUT);
  pinMode(3,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A1,INPUT);
}
void loop()
{


  int IR1read=digitalRead(8);
  int IR2read=digitalRead(7);
  int IR3read=digitalRead(13);
  int gas_value=digitalRead(A0);
  //door alarm
  if(IR3read==HIGH)
  {
    digitalWrite(12,1);
    delay(100);
    digitalWrite(12,0);
    delay(100);
    digitalWrite(12,1);
    delay(100);
    digitalWrite(12,0);
    delay(100);
    digitalWrite(12,1);
    delay(100);
    digitalWrite(12,0);
    delay(100);
  }
  else
  {
    digitalWrite(12,0);
  }
 //gas monitor
  if(gas_value==HIGH)
  {
    digitalWrite(2,HIGH);
  }
  else
  {
    digitalWrite(2,LOW);
  }
//people counter
   if (digitalRead(8)==0 && i==1 && state1){

     i = 2;
     state1 = false;
  }

   if (digitalRead(7)==0 && i==2 &&   state2){

     i = 1 ;
     count++;
     Serial.println(count);
     state2 = false;
  }

   if (digitalRead(7)==0 && i==1 && state2 ){

     i = 2 ;
     state2 = false;
  }

  if (digitalRead(8)==0 && i==2 && state1 ){

     count--;
     Serial.println(count);
     i = 1;
     state1 = false;
  }  

    if (digitalRead(8)){
     state1 = true;
    }

     if (digitalRead(7)){
     state2 = true;
    }
        

  if(count>0)
   {
    t=dht.readTemperature();
    if(t<10)
    {
     analogWrite(11,zero);
     analogWrite(10,0);
    }
    if(t>10 and t<25)
    {
      analogWrite(11,low);
     analogWrite(10,0);
    }
    if(t>25 and t<35)
    {
    analogWrite(11,medium);
    analogWrite(10,0);
    }
    if(t>35)
    {
    analogWrite(11,high);
    analogWrite(10,0);
    }
   }
   if(count<=0)
   {
    analogWrite(11,0);
    analogWrite(10,0);
    analogWrite(4,0);
   }
   if(count>0)
   {
    analogWrite(4,255);
   }
  //turning on the entry light and lights in hall
  if(IR1read == 1||IR2read == 1)
   {
    analogWrite(9,255);
   }
   //turning off the entry lightand closing the door
   if(IR1read == 0&&IR2read == 0)
   {
    analogWrite(9,0);
   }

  int a=1;
  int b=0;
  t=dht.readTemperature();
  while(Serial.available()) {
   delay(3);
  char character = Serial.read();
    if(character == 'T'){Serial.println(t);}
    if(count>0)
  {
    if(character == 'O'){Serial.println(a);}
  }
  else
  {
    if(character == 'O'){Serial.println(b);}
  } 
    if(character=='P')
      {
        Serial.println(count);
      }
if(digitalRead(6)==1)
        { 
      if(character=='E')
      {
        
          Serial.println(a);
        }
        else
        {
          Serial.print(b);
        }
      }
    
}
}
