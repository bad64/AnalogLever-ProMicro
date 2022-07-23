#include "AnalogLever-ProMicro/Analog.h"

Coordinates::Coordinates()
{
}

Coordinates::Coordinates(uint8_t xpin, uint8_t ypin, uint8_t numberOfSamples, uint8_t deadzonePercent, int16_t offsetX, int16_t offsetY )
{
  _raw = CartesianSystem(xpin, ypin, numberOfSamples, offsetX, offsetY);
  _deadzone = deadzonePercent;
}

PolarSystem Coordinates::polar()
{
  // Returns the polar coordinates system as an object
  // This, however, does not initialize said system ! You need to call a convertTo() method

  return _polar;
}

CartesianSystem Coordinates::raw()
{
  // Returns the cartesian system as an object

  return _raw;
}

void Coordinates::get()
{
  // Reads coordinates for both systems and stores it to be accessed in the main program

  static int16_t rbuf, xbuf, ybuf;

  // Constrain to legal values
  xbuf = map(_raw.x().value(), _raw.x().minimum(), _raw.x().maximum(), 17, 237); 
  ybuf = map(_raw.y().value(), _raw.y().minimum(), _raw.y().maximum(), 237, 17);

  // Convert to polar
  _polar.convertTo(xbuf - 127, ybuf - 127);	// Zero-based values otherwise they're defined on [0;1023]
  						// which won't work for polar coordinates

  // Check zones
  if (_polar.r() < _deadzone)
  {
    xbuf = 0;
    ybuf = 0;
    rbuf = 0;
  }
  else if (_polar.r() > 100)
  {
    rbuf = 130;
  }
  else
  {
    rbuf = _polar.r();
  }

  // Update values
  _x = 127 + rbuf * cos(_polar.theta());
  _y = 127 + rbuf * sin(_polar.theta());

  // Boundary checking, values cannot wrap around an uint8_t
  if (_x < 0) _x = 0;
  else if (_x > 255) _x = 255;

  if (_y < 0) _y = 0;
  else if (_y > 255) _y = 255;
}

int16_t Coordinates::x()
{
  return _x;
}

int16_t Coordinates::y()
{
  return _y;
}

uint8_t Coordinates::deadzone()
{
  return _deadzone;
}
