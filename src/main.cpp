
// I, Frank Kufer, student number 000805328, certify that this material is my
// original work. No other person's work has been used without due
// acknowledgement and I have not made my work available to anyone else.
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 

//Sensor address
DeviceAddress  TempAddress; 
int numberOfDevices;
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;    
//switch one for installed sensor  
int count = 0;
//switch two for uninstalled sensor
int count2 =0;
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  
} 
 
void loop() { 
  float fTemp; 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 

  // set variable 
  String DeviceAddress;
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 


//set the status of temp 
  String status;

 if (DS18B20.getAddress(TempAddress, 0)) {
    if(fTemp<10){
      status = "Cold!";
    }

    if(fTemp>=10.0 && fTemp<=15.0){
      status = "Cool";
    }
    if(fTemp>15.0 && fTemp<=25.0){
      status = "Perfect";
    }
    if(fTemp>25.0 && fTemp<=30.0){
      status = "Warm";
    }
    if(fTemp>30.0 && fTemp<=35.0){
      status = "Hot";
    }
    if(fTemp>35.0){
      status = "Too Hot!";
    }

    // Build device address
    for(byte a: TempAddress)
    {
       DeviceAddress += String(a,HEX);
    }
 
    // switch to only print address once
    if(count==0){
      Serial.println("\n\nTemperature Application");
      Serial.println("Found DS18B20 sensor with address: " + String(DeviceAddress)); 
      count+=1;
      
    }
    // if the sensor is connected then switchback the count2 to 0 so it shows no sensor installed again
    count2=0;

    // prit the temp and its status
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius. Or "+ String(status)); 

 }

// switch to only print sensor is disconncted
else{
  if(count2==0){
   Serial.println("\n\nNo DS18B20 temperature sensors are installed"); 
   count2+=1;
  }
   
}
 
  // wait 2s (2000ms) before doing this again 
  delay(5000); 
} 