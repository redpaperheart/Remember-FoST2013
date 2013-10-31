Remember - Future of Storytelling 2013
====================

[“Remember”](http://redpaperheart.com/work/remember) is a typographic installation inspired by wooden push toys, that allows you to move physical letters with your mind.
Created by [Red Paper Heart] as part of the Story Arcade at the [Future of Storytelling](http://futureofstorytelling.org/) conference, Oct 3rd, 2013 - New York City

MindwaveToServo
---------------
Arduino app that connects to the Mindwave reader via bluetooth, parses the input and outputs it to a servo motor with a certain logic. When it's not receiving good or any data from the brainwave reader it automatically defaults to manual control via a potentiometer.

It uses the following components:

* [Mindwave Mobile](http://www.neurosky.com/products/mindwavemobile.aspx) headset
* [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno)
* [Bluetooth modem BlueSmirf Silver](https://www.sparkfun.com/products/10269)
* [Servo - Hitec HS-805BB (Giant Scale)](https://www.sparkfun.com/products/11881)
* LED with 220ohm pull down resistor
* Slide or knob potentiometer
* External power supply with variable voltage

Wired the following way:

![Remember schematics](https://raw.github.com/redpaperheart/Remember-FoST2013/master/MindwaveToServo.png?login=araid&token=03d888aa298b6797310de40911cadade)

The Arduino code to parse the Mindwave data is based on the following [sample from Neurosky](http://developer.neurosky.com/docs/doku.php?id=mindwave_mobile_and_arduino), with some small modifications to make it non-blocking.

That sample includes a tutorial on how to pair the BlueSmirf with the Mindwave headset. Another good resource on setting up the Bluetooth module can be found [here](http://www.whizzosoftware.com/forums/blog/1/entry-48-bluesmirf-silver-bluetooth-modem-and-mac-os-x/)

For a detailed view of our process and experiments, feel free to check the dev branch of this repository.
