/*
** Driver for  MPX5 family of pressure sensors.
*/
#include "MPX5.h"

MPX5::MPX5(byte devType, byte pin)
{
  _devType = devType;
  _pin = pin;

  analogReference(DEFAULT);
  
}

MPX5::MPX5(byte devType, byte pin, byte refType)
{
  _devType = devType;
  _pin = pin;

  switch (refType)
  {
  case DEFAULT:
    _aRefVolts = 5.0;
    break;
  case EXTERNAL:
    /*
    ** Maybe this should be an error since this form does not allow you
    ** to specify the voltage. On the other hand, perhaps we should assume
    ** that 3.3 V would be logical...
    */
    _aRefVolts = 3.3;
    break;
  case INTERNAL:
    _aRefVolts = 1.1;
    break;
  }
  analogReference(refType);
}

MPX5::MPX5(byte devType, byte pin, byte refType, float aRefVolts)
{
  _devType = devType;
  _pin = pin;

  switch (refType)
  {
  case DEFAULT:
    _aRefVolts = 5.0;
    break;
  case INTERNAL:
    _aRefVolts = 1.1;
    break;
  case EXTERNAL:
    _aRefVolts = aRefVolts;
    break;
  }
  analogReference(refType);
}

/*
** Manually set the device offset. Should it return anything? Previous value of the offset,
** or if called with no value, should it return the offset?
*/

float MPX5::calibrate()
{
  //Assuming reading is zero!
  //Average offset in 10 reading
  for (int i = 0; i < 10; i++)
  {
    _Voffset += (analogRead(_pin) * _aRefVolts) / A2D_FULL_SCALE;
  }
  return _Voffset = _Voffset / 10;
}

float MPX5::read()
{
  return convert(analogRead(_pin));
}
/*
float MPX5::pointAverage(byte samples, int msDelay)
{
  long readings = 0;
  float average;

  for (byte i = 0; i < samples; i++) {
    readings += analogRead(_pin);
    delay(msDelay);
  }
  average = readings / samples;

  return convert(average);
}

float MPX5::rollingAverage(byte samples)
{
  static int readings[20];	      // XXX - for a max of 20.
  static byte cur = 0;
  static byte allValid = 0;
  float average = 0;

  readings[cur++ % samples] = analogRead(_pin);

  //DEBUG10("readings[] = ", readings[0], ", " , readings[1], ", " , readings[2], ", "  , readings[3], ", "  , readings[4]);

  if (allValid) {
    for (byte i = 0; i < samples; i++) {
      average += readings[i];
    }
    average /= samples;
  } else {
    for (byte i = 0; i < cur; i++) {
      average += readings[i];
    }
    average /= cur;
    if (cur == samples) {
      allValid = 1;
    }
  }
  return convert(average);
}

/*
** Return a symetric error value for the current operating condition of the sensor.
*/

/*
** Private functions.
*/

float MPX5::convert(float reading)
{
  float transferConstant;
  float Vout = (reading * _aRefVolts) / A2D_FULL_SCALE;

  switch (_devType)
  {
  case MPX5010:
    transferConstant = 0.0900000;
    break;
  case MPX5100:
    transferConstant = 0.0090000;
    break;
  case MPX5700:
    transferConstant = 0.0012858;
    break;
  }

  float pressure = (Vout - _Voffset) / (transferConstant * supplyVoltage());

  return pressure;
}
