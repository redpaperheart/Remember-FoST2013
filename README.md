FutureOfStorytelling
====================

Typographic installation for The Future of Storytelling conference

Tests
-----
* Cinder test using the asdf block
* Several arduino tests with the bluetooth Mindwave reader, stepper motors that we ended up not using and a simple rotary encoder built with the QRD1114 Phototransistor
* Processing app to read the serial input from arduino, graph it and implement the installation logic.

Final
-----
Arduino app that automatically connects to the Mindwave reader via bluetooth, parses the input and outputs it to the servo motor with a certain logic.

It uses the following components:
* [Bluetooth modem BlueSmirf Silver](https://www.sparkfun.com/products/10269)
* [Servo - Hitec HS-805BB (Giant Scale)](https://www.sparkfun.com/products/11881)
* Arduino UNO
* Switch with 5.6k pulldown resistor
* LED with 220ohm resistor
* Potentiometer

Resources
---------
* http://developer.neurosky.com/docs/doku.php?id=mindwave_mobile_and_arduino
* http://www.whizzosoftware.com/forums/blog/1/entry-48-bluesmirf-silver-bluetooth-modem-and-mac-os-x/
* http://bildr.org/2012/11/big-easy-driver-arduino/
