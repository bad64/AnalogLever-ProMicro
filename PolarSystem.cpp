#include "Analog.h"
#define PI 3.141592

PolarSystem::PolarSystem()
{
}

void PolarSystem::convertTo(Axis x, Axis y)
{
  // Converts two axes into a set of polar coordinates

  _r = sqrt( pow(x.zeroed(), 2) + pow(y.zeroed(), 2) );
  _theta = atan2(y.zeroed(), x.zeroed());
  _degrees = (_theta + PI) * (180 / (1 * PI));
}

void PolarSystem::convertTo(int16_t x, int16_t y)
{
  // Converts two signed integers into a set of polar coordinates

  _r = sqrt( pow(x, 2) + pow(y, 2) );
  _theta = atan2(y, x);
  _degrees = (_theta + PI) * (180 / (1 * PI));
}

void PolarSystem::convertTo(CartesianSystem c)
{
  // Converts a cartesian system into a set of polar coordinates

  _r = sqrt( pow(c.x().zeroed(), 2) + pow(c.y().zeroed(), 2) );
  _theta = atan2(c.y().zeroed(), c.x().zeroed());
  _degrees = (_theta + PI) * (180 / (1 * PI));
}

uint16_t PolarSystem::r()
{
  // Returns the radius associated with the cartesian coords used
  // to create the polar coordinates set

  return _r;
}

double PolarSystem::theta()
{
  // Returns the angle in radians

  return _theta;
}

double PolarSystem::asDegrees()
{
  // Returns the angle in degrees

  return _degrees;
}
