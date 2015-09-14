// This #include statement was automatically added by the Particle IDE.
#include "EmonLib/EmonLib.h"

// This #include statement was automatically added by the Particle IDE.
// #include "EmonLib.h"

// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3
#include <string.h>
// #include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
char publishString[40];
void setup()

{  
//   Serial.begin(9600);
  
  emon1.current(0, 111.1);             // Current: input pin, calibration.
}

void loop()
{
  double Irms = emon1.calcIrms(1480)*230.0;  // Calculate Irms only
  sendWatts(Irms);
//   Serial.print(Irms*230.0);         // Apparent power
//   Serial.print(" ");
//   Serial.println(Irms);             // Irms
    // double dd = 5000;
    //   sprintf(publishString,"%f : Reading %f",Irms,dd);

        // Spark.publish("Uptime",publishString);
        delay(3000);
}



void sendWatts(double wattreading)
{
    String val = doubleToString(wattreading,0);
    // "watts=" +
    /*request.hostname = "yourhost.com";*/
    /*request.port = 80;*/
    /*request.path = "/php/insertConsumption.php";*/
    /*request.body = val ;*/
    /*http.post(request, response, headers);*/
    Particle.publish("Readings",val);
    

}


String doubleToString(double input,int decimalPlaces){
    if(decimalPlaces!=0){
    String string = String((int)(input*pow(10,decimalPlaces)));
    if(abs(input)<1){
    if(input>0)
    string = "0"+string;
    else if(input<0)
    string = string.substring(0,1)+"0"+string.substring(1);
    }

    return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);

    }
    else {
    return String((int)input);
    }

}