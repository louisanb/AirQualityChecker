#include <Time.h>
#include <SD.h>
#include <SparkFunHTU21D.h>
#include <Wire.h>
#include "Adafruit_HTU21DF.h"
//#include <Wire.h>
//#include <SoftwareSerial.h>
//#define SDcard 0 //1 has SDcard 0 no 
//#define SDcard
//#define debug //to use this you may also need to definge digital and others 
//#define rx
#define debugS3   
//#define miso
//#define outPut
#define digital
//#define atc
//#define powerControl 
//#define s2
#define delayy
//String incData;   // for incoming serial data
int delayTime=500;
long sensor=19200;
long testSerial=57600;
const int chipSelect = 53;
int Apin=0;
int powerPin=7;
int dp=22;
int di=50; 
int doo=51;
boolean s3;
void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        Serial1.begin(9600);
        Serial3.begin(sensor);
        #if defined testSpeed///////////////////////1
        Serial2.begin(testSerial);
        #endif//////////////////////////////////////2
        //if (Serial.available() > 0) {
           Serial.println("Serial.available()");
           Serial.println(Serial.available());
           Serial.println("Serial3.available()");
           Serial.println(Serial3.available());
        if (Serial.available()>0) {
           Serial.println("Serial Enabled");
           Serial.println("Serial.available()");
           Serial.println(Serial.available());
           }
        if(Serial1.available()!=0) {
           Serial.println("Serial1 Enabled");
           }
        if(Serial3.available()>0) {
           s3=true;
           Serial.println("Serial3.available()");
           Serial.println(Serial3.available());
           Serial.println("Serial3 Enabled");
           Serial.println("s3=");
           Serial.println(s3);
           }
        Serial.println("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  #if defined powerControl
  Serial.println("powerControl enabled");
  pinMode(powerPin, OUTPUT);
  #endif
  #if defined digital
  pinMode(dp,INPUT);
  #endif
  #if defined miso
    pinMode(di,INPUT);
  pinMode(doo,OUTPUT);
  #endif
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
         float incData; 
         float tData;
         int input;
         float PincData;
         #if defined digital////////////////////////////1
         float dig;
         dig=digitalRead(dp);
         #endif/////////////////////////////////////////2
         #if defined powerControl///////////////////////1
        // Serial.println("powerControl enabled");
         float outVolts=5;
         float PoutVolts;
         //PoutVolts=outVolts*1023/5;
         PoutVolts=1023;
         analogWrite(powerPin, PoutVolts);
         #endif ////////////////////////////////////////2
         #if defined s2/////////////////////////////////1
         float S2;
         S2=Serial2.read();
         Serial.println("S2");
         Serial.println(S2);
         #endif/////////////////////////////////////////2
         PincData=(incData/1023)*5*1000;
           float ana = analogRead(Apin);
           float Pana=ana/1023*5;
           float rx_;
           String rxs;
           float miso_;
           rx_=Serial3.read();
           //rxs=Serial3.read();
           miso_=digitalRead(di);
           incData=Serial1.read();
           delay(50);
         #if defined debug//////////////////////////////1
             Serial.println("PoutVolts");
             Serial.println(PoutVolts);
             Serial.println("dig");
             Serial.println(dig);
             Serial.println("ana");
             Serial.println(ana);
             Serial.println("ana BIN");
             Serial.println(ana,BIN);
             Serial.println("Pana");
             Serial.println(Pana);
             //Serial.println("Pana BIN");
             //Serial.println(Pana,BIN);
             Serial.println("incData DEC");
             Serial.println(incData,DEC);
             Serial.println("incData BIN");
             Serial.println(incData,BIN);
             Serial.println("pincData DEC");
             Serial.println(PincData,DEC);
            //Serial.println("pincData BIN");
            //Serial.println(PincData,BIN);
             Serial.println("pincData");
             Serial.println(PincData);            
         //incData=map(incData,-1023,1023,-225,255);
        // send data only when you receive data:
        #endif///////////////////////////////////////////2
        #if defined delayy///////////////////////////////1
        delay(delayTime);
        #endif///////////////////////////////////////////2
        #if defined outPut///////////////////////////////1
        //Serial.println(ana);
        Serial.println("Pana,DEC");//if used '' out put 17731
                Serial.println(Pana,DEC);
       // Serial.println(PincData,DEC);
        //Serial.println(dig);
        #endif///////////////////////////////////////////2
        #if defined rx///////////////////////////////////1
        Serial.println(rx_,DEC);
        Serial.println(rx_);
        #endif///////////////////////////////////////////
       #if defined debugS3///////////////////////////////1
       Serial.println("rx_,DEC");
       String Rx_;
       //Rx_=const char(255);//char(192.0000000000)//+char(198.00);
       char rX_= char(rx_);
       //Rx_=floatToString(rx_);
       //Rx_=String(rx_);
       //Serial.println(Rx_);
       Serial.println(rX_);
       Serial.println(rx_);
       //Serial.println(rx_,DEC);
       if (s3){
        Serial.println(rx_,DEC);
        Serial.println(rx_);
        //Pana=0;
       }
        #endif///////////////////////////////////////////2
        #if defined miso/////////////////////////////////1
       // Serial.println("miso_,DEC");
        Serial.println(miso_,DEC);
        //Pana=0;
        #endif///////////////////////////////////////////2
        #if defined digital//////////////////////////////1
        Serial.println("dig,DEC");
        Serial.println(dig,DEC);
        Serial.println(dig);
        //Pana=0;
        #endif///////////////////////////////////////////2

        if (Serial.available() > 0) {
                // read the incoming byte:
                 input = Serial.read();
        if (input == '.' ) {
            Serial2.flush(); Serial2.end();
           }else{
                  if (input=='p'){//end communication with serial monitor
                    Serial.end();
                    Serial1.end();
                  }else{
                    if (input == 'o') {//not gonna work
                      Serial.begin(9600);
                      Serial1.begin(sensor);
                    }                      
                }//sec else bef input o
        }//first else
                }//if avalible
                #if defined SDcard/////////////////////////1
                File dataFile = SD.open("datalog.txt", FILE_WRITE);
                if (dataFile) {
                  
                dataFile.println(Pana,DEC);
                dataFile.close();            
              }  
              // if the file isn't open, pop up an error:
              else {
                Serial.println("error opening datalog.txt");              
              } 
               #endif//////////////////////////////////////2
               int input3 ;
              if (Serial3.available() > 0) {
                // read the incoming byte:
                 input3 = Serial3.read();
       
                  if (input3=='p'){//end communication with serial monitor
                    Serial.end();
                    Serial1.end();
                  }
              }
              #if defined act
             float humd = myHumidity.readHumidity();
           float temp = myHumidity.readTemperature();
           
           }
           #endif
}//loop
