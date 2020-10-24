#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30
SCD30 airSensor;


bool SCD30init() {
  bool working;
  //   if (airSensor.begin(Wire, false) == false) if you do not want autocalibration.
  if (airSensor.begin() == false) {
    working = false;
  } else {
    working = true;
    airSensor.setMeasurementInterval(4); //Change number of seconds between measurements: 2 to 1800 (30 minutes)

    airSensor.setAltitudeCompensation(350); //Set altitude of the sensor in m

    // airSensor.setAmbientPressure(835); //Current ambient pressure in mBar: 700 to 1200

    float offset = airSensor.getTemperatureOffset();
    Serial.print("Current temp offset: ");
    Serial.print(offset, 2);
    Serial.println("C");

    //airSensor.setTemperatureOffset(5); //Optionally we can set temperature offset to 5°C
  }
}


int SCD30read() {
  int _CO2;
  float _humidity;
  float _temperature;
  float _temperatureOffset;
  while (!airSensor.dataAvailable()) {
    Serial.print(".");
  }
  _CO2 = airSensor.getCO2();
  Serial.print("co2(ppm):");
  Serial.print(_CO2);

  Serial.print(" temp(C):");
  Serial.print(airSensor.getTemperature(), 1);

  Serial.print(" humidity(%):");
  Serial.print(airSensor.getHumidity(), 1);

  Serial.println();

  return (_CO2);
}
