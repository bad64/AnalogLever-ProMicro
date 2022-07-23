#include "AnalogLever-ProMicro/Analog.h"

Axis::Axis()
{
}

Axis::Axis(uint8_t npin, uint8_t _numberOfSamples, int16_t offset)
{
  pin = npin;
  numberOfSamples = _numberOfSamples;
  sampleArray = (uint16_t)calloc(numberOfSamples, sizeof(uint16_t));

  _center = 512;

  #if defined(LEVER_JLM)
    // Empirical values; will need to be adjusted on a case by case basis
    minimum = center - 275;
    maximum = center + 275;
  #endif
  
  #if defined(LEVER_U360)
    // Ditto
    minimum = center - 360;
    maximum = center + 360;
  #endif
  
  _range = _maximum - _minimum;
  _offset = offset;
}

int16_t Axis::getRaw()
{
  return analogRead(pin) + _offset;
}

int16_t Axis::getAveraged()
{
  static uint8_t counter;
  counter = 0;

  while (counter < numberOfSamples)
  {
    sampleArray[counter] = getRaw();
    counter++;
  }

  static uint16_t averageBuf;
  averageBuf = 0;
  for (int i = 0; i < numberOfSamples; i++)
  {
    averageBuf += sampleArray[i];
  }

  return averageBuf / numberOfSamples;
}

int16_t Axis::value()
{
  previousvalue = _value;

  _value = getAveraged();

  if ((previousvalue == 127) && (speed() > 0)) _value = 127;
  
  return _value;
}

int16_t Axis::speed()
{
  return abs(value() - previousvalue);
}

int16_t Axis::acceleration()
{
  return 0; // TODO
}

int16_t Axis::center()
{
  return _center;
}

int16_t Axis::minimum()
{
  return _minimum;
}

int16_t Axis::maximum()
{
  return _maximum;
}

int16_t Axis::zeroed()
{
  return value() - _center;
}
