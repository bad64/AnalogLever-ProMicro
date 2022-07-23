#ifndef ANALOGLEVER_H
#define ANALOGLEVER_H

#include <Arduino.h>
#include <stdint.h>
#include <math.h>

#pragma message "AnalogLever library v0.0.1"

/****************************************************
 * General analog header to include in your project *
*****************************************************/

// Lever selection compile-time defines
#define LEVER_JLM
//#define LEVER_U360

class Axis
{
  // Defines a 1-dimensional axis

  private:
    uint8_t pin;
    int16_t _value;
    int16_t previousvalue;
    int16_t _speed;
    int16_t _acceleration;
    int16_t _center;
    int16_t _minimum;
    int16_t _maximum;
    int16_t _range;
    int16_t _offset;
    uint8_t numberOfSamples;
    uint16_t* sampleArray;
  public:
    Axis();
    Axis(uint8_t npin, uint8_t _numberOfSamples, int16_t offset);
    int16_t getRaw();
    int16_t getAveraged();
    int16_t value();
    int16_t speed();
    int16_t acceleration();
    int16_t center();
    int16_t minimum();
    int16_t maximum();
    int16_t range();
    int16_t zeroed();
};
class CartesianSystem
{
  // Defines a cartesian (x;y based) coordinates system

  private:
    Axis _x;
    Axis _y;
  public:
    CartesianSystem();
    CartesianSystem(uint8_t xpin, uint8_t ypin, uint8_t numberOfSamples, int16_t offsetX, int16_t offsetY);
    Axis x();
    Axis y();
};

class PolarSystem
{
  // Defines a polar coordinates system

  private:
    uint16_t _r;
    double _theta;
    double _degrees;
  public:
    PolarSystem();
    void convertTo(Axis x, Axis y);
    void convertTo(int16_t x, int16_t y);
    void convertTo(CartesianSystem c);
    uint16_t r();
    double theta();
    double asDegrees();
};

class Coordinates
{
  // Aggregation of the previous two coordinates systems

  private:
    PolarSystem _polar;
    CartesianSystem _raw;
    int16_t _x;
    int16_t _y;
    uint8_t _deadzone;
    uint8_t _reverseDeadZone;
  public:
    Coordinates();
    Coordinates(uint8_t xpin, uint8_t ypin, uint8_t numberOfSamples, uint8_t deadzonePercent, uint8_t reverseDeadzonePercent, int16_t offsetX, int16_t offsetY);
    PolarSystem polar();
    CartesianSystem raw();
    void get();
    int16_t x();
    int16_t y();
    uint8_t deadzone();
};

#endif
