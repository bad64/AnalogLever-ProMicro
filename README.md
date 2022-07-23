# So you want an analog lever

This library supports both the Sanwa JLM and the Ultimarc Ultrastik 360. Do note however that the U360 requires special firmware only available by mailing the support team at Ultimarc: for legal reasons I am not allowed to redistribute it.

# Installation

`git clone` this repo wherever your OS stores Arduino libraries.

# How does analog

Firstly, this code will only work for an Arduino Pro Micro. A RP2040 port is in the works.

Plug your lever outputs into analog inputs. For my personal peace of mind I run them first through a pair of op-amps, two per axis, in a voltage follower configuration to stabilize the readings, but on a Pro Micro you don't need it.

Instantiate a `Coordinate` class:
```
coords = Coordinates(xpin, ypin, numberOfSamples, deadzone, offsetX, offsetY);
```

To read your coordinates, in your main loop, call `coords.get()`. Your x/y pair becomes available through `coords.x()` and `coords.y()`. You can then feed them to your communications library of choice !

# Polar coordinates and you

The library exposes a set of polar coordinates that are mostly used to compute circular deadzones and analog-to-digital conversions through trigonometry.

# TODO

* Solve the snapback issues
* Port to RP2040
