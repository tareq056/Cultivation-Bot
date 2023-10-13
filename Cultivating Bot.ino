#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

Servo servo;

const int buzzer = 53;
int readBluetooth;

int RightA1 = 22;
int RightB1 = 24;

int RightA2 = 26;
int RightB2 = 28;

int LeftA1 = 51;
int LeftB1 = 49;

int LeftA2 = 34;
int LeftB2 = 36;



int waterpin = 6; //38
int soilpin = A1;


int seedpin01 = 42;
int seedpin02 = 44;

int seedEnable = 8;

int soil = 0;

int pirPin = 12; //the digital pin connected to the PIR sensor's output

int buzzer1 = 13;
int in7 = 14;

int waterlevel= 0;
int watersensor = A8;

void setup() {

  servo.attach(11);
  servo.write(0);



  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pirPin, INPUT);

  pinMode(buzzer, OUTPUT);  

  pinMode(buzzer, OUTPUT);

  pinMode(RightA1,OUTPUT);
  pinMode(RightA1,OUTPUT);
  
  pinMode(RightA2,OUTPUT);
  pinMode(RightB2,OUTPUT);

  pinMode(LeftA1,OUTPUT);
  pinMode(LeftB1,OUTPUT);

  pinMode(LeftA2,OUTPUT);
  pinMode(LeftB2,OUTPUT);

  pinMode(waterpin,OUTPUT);
  pinMode(soilpin,INPUT);

  pinMode(in7,OUTPUT);


  pinMode(seedpin01,OUTPUT);
  pinMode(seedpin02,OUTPUT);
  pinMode(seedEnable,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  LCD_HUMIDITY();
  control();
  pirMotion();
  SoilTest();
  waterSensor();
  digitalWrite(in7,HIGH);
}


void waterSensor()
{
  waterlevel = analogRead(watersensor);
  if(waterlevel>1)
  {
    Serial.print("Water:");
    Serial.print(waterlevel);
  }
}

void SoilTest()
{
  soil = analogRead(soilpin);
  Serial.print(soil);
  if(soil>300 && soil<400)
  {
    digitalWrite(waterpin,HIGH);

  }
  else
  {
        
    delay(1500);
    
    digitalWrite(waterpin,LOW);
  }
}



void LCD_HUMIDITY()
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  //Serial.print((int)temperature); Serial.print(" *C, "); 
  //Serial.print((int)humidity); Serial.println(" H");

  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print((int)temperature);lcd.print(" *C");

  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print((int)humidity);lcd.print(" H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1600);
}



void pirMotion()
{
  if(digitalRead(pirPin) == HIGH){
      
        tone(buzzer1, 1000); // Send 1KHz sound signal...
        delay(2000);   // ...for 1 sec
        noTone(buzzer1);     // Stop sound...
        delay(2500);
        
        //Right Motor
        digitalWrite(RightA1, LOW);
        digitalWrite(RightB1, LOW);

        digitalWrite(RightA2, LOW);
        digitalWrite(RightB2, LOW);

        //Left Motor
        digitalWrite(LeftA1, LOW);
        digitalWrite(LeftB1, LOW);

        digitalWrite(LeftA2, LOW);
        digitalWrite(LeftB2, LOW); 
         
  }
  if(digitalRead(pirPin) == LOW)
  {
        noTone(buzzer1);     // Stop sound...
        delay(2500);
  }
}

void control()
{
 if(Serial.available() > 0)
  {
      readBluetooth = Serial.read();

  } 
   
  
     if(readBluetooth == 'Y')
      {
          digitalWrite(seedpin01,HIGH);
          digitalWrite(seedpin02,LOW);
          digitalWrite(seedEnable,100);
      }
      if(readBluetooth == 'T')
      {
          digitalWrite(seedpin01,LOW);
          digitalWrite(seedpin02,LOW);
          digitalWrite(seedEnable,100);
      }
  //Forward
      if(readBluetooth=='U')
      {
        BUZZERCODE();
        //Right Motor
        digitalWrite(RightA1, HIGH);
digitalWrite(RightB1, LOW);

        digitalWrite(RightA2, HIGH);
        digitalWrite(RightB2, LOW);

        //Left Motor
        digitalWrite(LeftA1, LOW);
        digitalWrite(LeftB1, HIGH);

        digitalWrite(LeftA2, LOW);
        digitalWrite(LeftB2, HIGH);
         
      }
      //Back
      if(readBluetooth == 'D')
      {
        BUZZERCODE();
        //Right Motor
        digitalWrite(RightA1, LOW);
        digitalWrite(RightB1, HIGH);

        digitalWrite(RightA2, LOW);
        digitalWrite(RightB2, HIGH);

        //Left Motor
        digitalWrite(LeftA1, HIGH);
        digitalWrite(LeftB1, LOW);

        digitalWrite(LeftA2, HIGH);
        digitalWrite(LeftB2, LOW);        
      }     
      //Left 
      //Left UP
      if(readBluetooth == 'L')
      {
        BUZZERCODE();
        //Right Motor
        digitalWrite(RightA1, HIGH);
        digitalWrite(RightB1, LOW);

        digitalWrite(RightA2, HIGH);
        digitalWrite(RightB2, LOW);

        //Left Motor
        digitalWrite(LeftA1, LOW);
        digitalWrite(LeftB1, LOW);

        digitalWrite(LeftA2, LOW);
        digitalWrite(LeftB2, LOW);  
        
      }
      //Right
      //Right UP
      if(readBluetooth == 'R')
      {
        BUZZERCODE();
        //Right Motor
        digitalWrite(RightA1, LOW);
        digitalWrite(RightB1, LOW);

        digitalWrite(RightA2, LOW);
        digitalWrite(RightB2, LOW);

        //Left Motor
        digitalWrite(LeftA1, HIGH);
        digitalWrite(LeftB1, LOW);

        digitalWrite(LeftA2, HIGH);
        digitalWrite(LeftB2, LOW);        
      }
      //Forward Left
      if(readBluetooth == 'S')
      {
 
          //Right Motor
        digitalWrite(RightA1, LOW);
        digitalWrite(RightB1, LOW);

        digitalWrite(RightA2, LOW);
        digitalWrite(RightB2, LOW);

        //Left Motor
        digitalWrite(LeftA1, LOW);
        digitalWrite(LeftB1, LOW);

        digitalWrite(LeftA2, LOW);
        digitalWrite(LeftB2, LOW);         
      }
      //Forward Right
      if(readBluetooth == 'I')
      {
        
      }
      //Back Left
      if(readBluetooth == 'H')
      {
        BUZZERCODE();
         //Right Motor
        digitalWrite(RightA1, LOW);
        digitalWrite(RightB1, HIGH);

        digitalWrite(RightA2, LOW);
        digitalWrite(RightB2, HIGH);

        //Left Motor
        digitalWrite(LeftA1, LOW);
        digitalWrite(LeftB1, LOW);

        digitalWrite(LeftA2, LOW);
        digitalWrite(LeftB2, LOW);        
      }
      //Back Right
      if(readBluetooth == 'J')
      {
        BUZZERCODE();
         //Right Motor
        digitalWrite(RightA1, LOW);
        digitalWrite(RightB1, LOW);

        digitalWrite(RightA2, LOW);
        digitalWrite(RightB2, LOW);

        //Left Motor
        digitalWrite(LeftA1, LOW);
        digitalWrite(LeftB1, HIGH);

        digitalWrite(LeftA2, LOW);
        digitalWrite(LeftB2, HIGH);        
      }
      if(readBluetooth == 'N')
      {
        for(int c=0;c<180;c++)
        {
          servo.write(c);
        }
      }
     if(readBluetooth == 'M')
      {
        for(int c=180;c>0;c--)
        {
          servo.write(c);
        }
      }
      if(readBluetooth == 'B')
      {

          servo.write(0);
      }
      if(readBluetooth == 'C')
      {
         digitalWrite(waterpin,HIGH);
      }
      if(readBluetooth == 'V')
      {
         digitalWrite(waterpin,LOW);
      }
 }


 void BUZZERCODE()
 {
   tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);  
 }
