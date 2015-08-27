unsigned long lastTime = 0UL;
char publishString[40];
  int state = 0;
   int LED = D1;
      int PR = A0;
      int val = 0;

void setup() {
   pinMode(LED, OUTPUT);
    // pinMode(PR, A);

}

void loop() {
    unsigned long now = millis();
    //Every 15 seconds publish uptime
    if (now-lastTime>1500UL) {
        lastTime = now;
        // now is in milliseconds
        unsigned nowSec = now/1000UL;
        unsigned sec = nowSec%60;
        unsigned min = (nowSec%3600)/60;
        unsigned hours = (nowSec%86400)/3600;
        
        
        val = analogRead(PR);
                sprintf(publishString,"%d: Reading",val);

        Spark.publish("Uptime",publishString);
        if(state == 0){
        digitalWrite(LED, HIGH);
        state = 1;
        }
        else
        {
        digitalWrite(LED, LOW);
        state = 0;
        }
    }
}

