/*
** Data manager Class
*/
#include "DataManager.h"

DataManager::DataManager()
{
    _sequentialReadings[2] = {False, False};
    _firstReadingMillistamp = 0;
    
}



// *************************************************************
//   ProcessMomentary(pointer to swmom_ struct)
//   Processes the specified switch state of momentary buttons
//   Read the state of the switch to get results
//   - state 0, switch not pressed
//   - state 2, switch pressed and debounced (short press)
//   - state 4, switch pressed and held for PUSH_LONG_LEVEL1 (eg 3 seconds, 5 seconds)
//   - state 6, switch pressed and held for 2x PUSH_LONG_LEVEL1
// *************************************************************
void DataManager::ProcessSensor(float reading)
{
  if (reading> tresh)
  { // switch pressed
    switch (_state)
    {
    case 0: /* RESET*/
      if(ul_CurrentMillis - _millis < DELTAT; //currentmillis sta nel main, vediamo se è visibile o se va passata
      AnySwitch->state = 1;
      break;
    case 1: /* one reading */
      if (ul_CurrentMillis - _millis > DELTAT)
      {
        AnySwitch->state = 2;  //RESET
        break;
      }
    case 2: /* DEBOUNCED, read valid */
      break;
    case 3: /* For LONG press  _not in this code_*/
      if (ul_CurrentMillis - AnySwitch->millis > PUSH_LONG_LEVEL1)
      {
        AnySwitch->state = 4;
        break;
      }
    case 4: /* LONG PRESS, read valid */
      break;
    case 5: /* For LONG * 2 press  _not in this code_*/
      if (ul_CurrentMillis - AnySwitch->millis > (PUSH_LONG_LEVEL1 * 2))
      {
        AnySwitch->state = 6;
        break;
      }
    case 6: /* LONG PRESS * 2, read  */
      break;
    case 7: /* LONG PRESS * 2, hold  */
      break;
    } // end switch
  }
  else
  { // button went high, reset the state machine
    AnySwitch->state = 0;
  }
}


void DataManager::ValidateReading(float reading)
{
   
    if (reading > TRESHOLD)
    {
        if (_sequentialReading[0] == False)
        {
            _sequentialReading[0] = True;
            _firstReadingMillistamp = millis();
        }
        else
        {
            if (_sequentialReading[1] == False)
            {
                _sequentialReading[1] = True;
            }
        }
       CHECK && (millis()-_firstReadingMillistamp<DELTAT) 
    }
    _millisstamp = millis();
    if (ul_CurrentMillis - AnySwitch->millis > PUSH_LONG_LEVEL1)
}
float DataManager::calibrate()
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
