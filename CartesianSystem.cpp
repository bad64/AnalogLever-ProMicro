#include "Analog.h"

CartesianSystem::CartesianSystem()
{
}

CartesianSystem::CartesianSystem(uint8_t xpin, uint8_t ypin, uint8_t numberOfSamples, int16_t offsetX, int16_t offsetY)
{
  /*
   * xpin: Analog pin to read for the X axis
   * ypin: Analog pin to read for the Y axis
   * numberOfSamples: Number of sampling loops to perform when reading from analog pins
   * offsetX: Offset to apply to X-axis readings (think of it as error correction)
   * offsetY: Offset to apply to Y-axis readings
   */

  _x = Axis(xpin, numberOfSamples, offsetX);
  _y = Axis(ypin, numberOfSamples, offsetY);
}

Axis CartesianSystem::x()
{
  // Returns the X axis as an object

  return _x;
}

Axis CartesianSystem::y()
{
  // Returns the Y axis as an object

  return _y;
}
