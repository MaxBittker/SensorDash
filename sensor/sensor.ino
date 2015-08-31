// This #include statement was automatically added by the Spark IDE.

/*#include "HttpClient/HttpClient.h"*/
#include "application.h"
#include "EmonLib.h"
#include <string.h>
/*
HttpClient http;
http_request_t request;
http_response_t response;
http_header_t headers[] = {

      { "Content-type", "application/x-www-form-urlencoded" },
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};*/

EnergyMonitor emon1;                   // Create an instance
/*TCPClient client;*/
const int voltage = 220;
double average = 0.0; // interval at which to do something (millisecond)
double sum = 0.0; // interval at which to do something (milliseconds)
int count = 0; // interval at which to do something (milliseconds)

static unsigned long secondInterval = 1000;
static unsigned long minuteInterval = 57000;
static unsigned long prevMinute = 0;
static unsigned long prevSecond = 0;
unsigned long now;

void setup()
{
  Serial.begin(9600);
  emon1.current(0, 103.1);
}



void loop()

{
   unsigned long currentMillis = millis();
    if ((unsigned long)(currentMillis - prevSecond) < secondInterval){
    return;
        }
    else{

        double Irms = emon1.calcIrms(1480);  // Calculate Irms only
        //double watts = (Irms*voltage) - 16;  // Calculate Irms only
        double watts = (Irms*1000) ;  // Calculate Irms only
        sum = sum + watts;
        count = count + 1;
        if ((unsigned long)(currentMillis - prevMinute) < minuteInterval){
        return;
        }
        else{
            average = sum/count;
            sendWatts(average);
            average = 0.0;
            sum = 0.0;
            count = 0;
            prevMinute = currentMillis;
        }
        prevSecond = currentMillis;
        }
}

void sendWatts(double wattreading){
    String val = "watts=" + doubleToString(wattreading,2);
    /*request.hostname = "yourhost.com";*/
    /*request.port = 80;*/
    /*request.path = "/php/insertConsumption.php";*/
    /*request.body = val ;*/
    /*http.post(request, response, headers);*/
    Spark.publish("Uptime",String);

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
