#include <Wire.h>
#include <Servo.h>

#define SOUND
#define SERVO
#define SENS_SCD30

#define LOOPTIME 30000
#define CO2LIMIT 600

unsigned int CO2;
static const int servoPin = 5;

Servo servo1;

#ifdef SENS_SCD30
#include "SCD30.h"
#endif

#ifdef SOUND
#include "DFPlayer.h"
#endif


void alarm() {
#ifdef SERVO
  servo1.write(0);
  delay(2000);
#endif

#ifdef SOUND
  for (int i = 0; i < 3; i++) {
    playFile(1);
    delay(500);
  }
#endif

#ifdef SERVO
  servo1.write(180);
  delay(2000);
#endif

#ifdef SOUND
  playFile(6);  // I'll be back
#endif

}

void setup()
{
  Serial.begin(115200);
  Serial.println("Start init");
  Wire.begin();
#ifdef SOUND
  DFPlayerInit();
#endif

#ifdef SENS_SCD30
  SCD30init();
#endif

#ifdef SERVO
  servo1.attach(servoPin);
  servo1.write(180);
#endif
  Serial.println("End init");
}

void loop()
{
  // read sensor


#ifdef SENS_SCD30
  CO2 = SCD30read();
#endif

  if (CO2 > CO2LIMIT) {
    alarm();
  }

  delay(LOOPTIME);
}
