#include <dht.h>
dht DHT;
#define DHT11_PIN 5
#include <SD.h>
#include <Time.h>  
#include <Wire.h>  
#include <DS1307RTC.h> 

//#define settime //dont enable this unless you want to reset time. if you want 
//to reset the time you need to run the code with settime once then before you 
//open serial monitor you need to run the code without the settime otherwise you 
//will reset the time every time when you open the serial monitor or run the code with settime 

//#define debug //to use this you may also need to definge digital and others 
//#define rx
//#define debugS3   
//#define miso
//#define sec3s
#define outPut
#define SDcard
//#define SDtime
//#define digital
//#define atc
//#define powerControl 
//#define s2
#define delayy
//String incData;   // for incoming serial data
int delayTime=30000; //60000 is not 1 min 1000=2s
int led = 13;
long sensor=19200;
long testSerial=57600;
const int chipSelect = 53;
int Apin=0;
int NOpin=1; 
int COpin=2; 
int NO2pin=3; 
int SO2pin=5; 
int OXpin=4; 
int NO22pin=6;
int Tempin=7;
int Tpin=8;
int powerPin=7;
int dp=22;
int di=50; 
int doo=51;
void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        Serial.println("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  pinMode(led, OUTPUT);    
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");     
      //if (Serial.available()) {
             #if defined settime ///////////////////////1
                  time_t t =  1451909340   ;//www.convert-unix-time.com 
              //time_t t = processSyncMessage();
              if (t != 0) {
                Serial.println("t != 0");
                RTC.set(t);   // set the RTC and the system time to the received value
                setTime(t);          
              }
            //} 
            #endif //////////////////////////////////////2
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
  }else{
  Serial.println("card initialized.");
  }
           Serial.println();
           Serial.print("Time");
           Serial.print("                 ");
           Serial.print("NO");
           Serial.print("      ");
           Serial.print("CO");
           Serial.print("      ");
           Serial.print("NO2");
           Serial.print("      ");
           Serial.print("T");
           Serial.print("      ");
           Serial.print("h"); 
           Serial.print("   ");
           Serial.print("ht(c)"); 
           Serial.print("   ");
           Serial.print("COt");
           Serial.print("    ");
           Serial.print("NOt");
           Serial.print("   ");
           Serial.print("Tt"); 
           Serial.print("    ");
           Serial.print("Tt5t");
           Serial.print("    ");
           Serial.print("NOv");
           Serial.print("   ");
           Serial.print("COv");
           Serial.print("   ");

           #if defined SDcard/////////////////////////1
        File dataFile = SD.open("datalog.txt", FILE_WRITE);
        if (dataFile) {
          digitalWrite(led, HIGH);
           dataFile.println();
           dataFile.print("Time");
           dataFile.print("                 ");
           dataFile.print("NO");
           dataFile.print("      ");
           dataFile.print("CO");
           dataFile.print("      ");
           dataFile.print("NO2");
           #if defined sec3s
           dataFile.print("     ");
           dataFile.print("SO2");
           dataFile.print("     ");
           dataFile.print("OX");
           dataFile.print("      ");
           dataFile.print("NO22");
           #endif
           dataFile.print("      ");
           dataFile.print("T");  
           dataFile.print("      ");
           dataFile.print("h"); 
           dataFile.print("    ");
           dataFile.print("ht(c)"); 
                


              dataFile.close();        
              }  
              // if the file isn't open, pop up an error:
              else {
                Serial.print("  error opening datalog.txt");              
              } 
               #endif//////////////////////////////////////2
}//set up

void loop() {
         float incData; 
         float tData;
         int input;
         float PincData;
         PincData=(incData/1023)*5*1000;
         float ana=analogRead(Apin);
           float NO = analogRead(NOpin);//if ANO error expected unqualified id before xx constant
           float CO = analogRead(COpin);
           float NO2 = analogRead(NO2pin);
           float Tem=analogRead(Tempin);
           float NOv=NO*(5.0/1023.0);
           float COv=CO*(5.0/1023.0);
           float NO2t=NO2*(5.0/1023.0);
           float COt=4E-05*(((long)CO)*CO) + 0.0002*CO + 1.436;
           float NOt= 1155.9*log(NO) - 4911.5;
        #if defined delayy///////////////////////////////1
        delay(delayTime);
        #endif///////////////////////////////////////////2
        #if defined outPut///////////////////////////////1
        DHT.read11(DHT11_PIN);
        Serial.println();
        digitalClockDisplay();  
         Serial.print("  ");
         Serial.print(NO);
         Serial.print("  ");
         Serial.print(CO);
         Serial.print("  ");;
         Serial.print(NO2);
         Serial.print("  ");
         Serial.print(Tem);
         Serial.print("  ");
         Serial.print(DHT.humidity, 1);
         Serial.print("  ");
         Serial.print(DHT.temperature, 1);
         Serial.print(NOt);
         Serial.print("  ");
         Serial.print(COt);
         Serial.print("  ");
         Serial.print(3.6983*Tem - 224.42); 
         Serial.print("  ");
         Serial.print(3.6983*(Tem*(5.0/1023.0))-224.42);
         Serial.print("  ");
         Serial.print(NOv);
         Serial.print("  ");
         Serial.print(COv);
           
        
        #endif///////////////////////////////////////////2
        if (Serial.available() > 0) {
                // read the incoming byte:
                 input = Serial.read();
        if (input == '.' ) {
           // Serial2.flush(); Serial2.end();
           }else{
                  if (input=='p'){//end communication with serial monitor
                    Serial.end();
                    Serial1.end();
                  }
                }//first else
           }//if avalible
                #if defined SDcard/////////////////////////1
                File dataFile = SD.open("datalog.txt", FILE_WRITE);
                if (dataFile) {
           #if defined delayy
          delay(delayTime);
          #endif
            dataFile.println();
          //digitalClockDisplaySD();  
            dataFile.print(hour());
            dataFile.print(":");
            if(minute() < 10)
            dataFile.print('0');
            dataFile.print(minute());
            
            dataFile.print(":");
            if(second() < 10)
            dataFile.print('0');
            dataFile.print(second());
            //printDigitsSD(minute());
           // printDigitsSD(second());
            dataFile.print(" ");
            dataFile.print(month());
            dataFile.print("/");        
            dataFile.print(day());
            dataFile.print("/");
            dataFile.print(year()); 
          dataFile.print("  ");
          dataFile.print(NO);
          dataFile.print("  ");
          dataFile.print(CO);
          dataFile.print("  ");
          dataFile.print(NO2);
          dataFile.print("  ");
        #if defined sec3s
          dataFile.print(SO2);
          dataFile.print("  ");
          dataFile.print(OX);
          dataFile.print("  ");
          dataFile.print(NO22);
         #endif
          dataFile.print("  ");
          dataFile.print(Tem);
          dataFile.print("  ");
          dataFile.print(DHT.humidity, 1);
          dataFile.print("  ");
          dataFile.print(DHT.temperature, 1);    
          
              dataFile.close();        
              }  
              // if the file isn't open, pop up an error:
              else {
                Serial.print("  error opening datalog.txt");              
              } 
               #endif//////////////////////////////////////2
}//loop
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(month()); 
  Serial.print("/");
  Serial.print(day());
  Serial.print("/");
  Serial.print(year()); 
  //Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
#if defined SDtime
void digitalClockDisplaySD(){
  // digital clock display of the time
  dataFile.print(hour());
  printDigitsSD(minute());
  printDigitsSD(second());
  dataFile.print(" ");
  dataFile.print(day());
  dataFile.print("/");
  dataFile.print(month());
  dataFile.print("/");
  dataFile.print(year()); 
  //Serial.println(); 
}

void printDigitsSD(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  dataFile.print(":");
  if(digits < 10)
    dataFile.print('0');
  dataFile.print(digits);
}
#endif
/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     Serial.println("pctime");
     Serial.println(pctime);
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}



