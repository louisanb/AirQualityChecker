# AirQualityChecker
![arduino_air](https://user-images.githubusercontent.com/8673420/28799850-0c564d74-75ff-11e7-97fa-aac9a30a4775.jpg)
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
        Serial2.begin(te
