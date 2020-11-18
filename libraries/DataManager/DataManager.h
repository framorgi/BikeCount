#ifndef DataManager_h
#define DataManager_h

#include <Arduino.h>

#ifndef TRESHOLD
#define TRESHOLD 5.0  
#endif // //kPa


/

class DataManager {

 public:
  DataManager(byte devType, byte pin);

  void DumpFromSDToSerial();
  void ValidateReading(float reading);

 private:
 
  unsigned long millis;
  uint8_t state;
  unsigned long _firstReadingMillistamp;
  bool _sequentialReadings[2];

  void StorageInSD();
};

#endif // MPX5_h